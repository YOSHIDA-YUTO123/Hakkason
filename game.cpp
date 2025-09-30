//===================================================
//
// ゲームシーン [game.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "game.h"
#include "objectX.h"
#include "manager.h"
#include "input.h"
#include "result.h"
#include "fade.h"
#include "debugproc.h"
#include "pause.h"
#include "light.h"
#include "LoadManager.h"
#include "Object3DAnim.h"
#include "sound.h"
#include "Object2DAnimMT.h"
#include "billboardAnim.h"
#include "meshfield.h"
#include "player.h"
#include "enemysphere.h"
#include "enemyneedle.h"
#include "DualUnitTimer.h"
#include "mapmanager.h"
#include "enemybonus.h"
#include "enemyshot.h"
#include "dome.h"
#include "math.h"
#include "enemymanager.h"
#include "pause.h"
#include "sound.h"
#include "Gage.h"

using namespace Const; // 名前空間Constを使用
using namespace std; // 名前空間stdを使用

//***************************************************
// 静的メンバ変数宣言
//***************************************************
CGame::STATE CGame::m_state = STATE_NORMAL;	// ゲームの状態
CPlayer* CGame::m_pPlayer = NULL;			// プレイヤー
CDualUnitTimer* CGame::m_pTimer = NULL;		// タイマー
int CGame::m_nScore = NULL;					// スコア

//===================================================
// コンストラクタ
//===================================================
CGame::CGame() : CScene(MODE_GAME)
{
	m_nCounterState = NULL;
}

//===================================================
// デストラクタ
//===================================================
CGame::~CGame()
{
	m_nScore = NULL;
}

//===================================================
// 初期化処理
//===================================================
HRESULT CGame::Init(void)
{
	// ライトの取得
	CLight* pLight = CManager::GetLight();
	pLight->Init();

	// ライトの設定処理
	pLight->SetDirectional(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -0.56f, 0.74f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	pLight->SetDirectional(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -0.56f, -0.74f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	// ドームの生成
	CMeshDome::Create(VEC3_NULL, 10, 10, 5500.0f, 1500.0f);

	// ドームの生成
	CMeshDome::Create(VEC3_NULL, 10, 10, 5500.0f, -1500.0f);


	CMeshField::Create(VEC3_NULL, 5, 5, { 4000.0f,4000.0f });

	// ポーズマネージャーの生成
	CPauseManager::Create();

	// 分と秒のタイマーの生成
	m_pTimer = CDualUnitTimer::Create(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 50.0f, 0.0f), D3DXVECTOR2(50.0f, 25.0f), 60);

	// インスタンスを取得->読み込み
	CMapManager::Instance()->Load("data\\TXT\\Stage000.json");

	CManager::GetSound()->Play(CSound::SOUND_LABEL_GAMEBGM);

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(VEC3_NULL, NULL);

	CHpGage::Create(D3DXVECTOR3(20.0f, 80.0f, 0.0f), D3DXVECTOR2(200.0f, 20.0f), D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f), D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f), m_pPlayer->GetLife(), true);

	CEnemyManager::Reset();

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		int Type = rand() % 4;
		float Angle = math::Randf(D3DX_PI * 2, 0.1f);
		D3DXVECTOR3 SetPos = m_pPlayer->GetPosition();
		SetPos.x += sinf(Angle) * 300.0f;
		SetPos.y += 50.0f;
		SetPos.z += cosf(Angle) * 300.0f;
		CEnemyManager::PushBackBullet(SetPos, Type);
	}

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CGame::Uninit(void)
{
	// ポーズのマネージャーの取得
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	if (pPauseManager != nullptr)
	{
		pPauseManager->Uninit();
	}
	// 状態のリセット
	m_state = STATE_NORMAL;
}

//===================================================
// 更新処理
//===================================================
void CGame::Update(void)
{
	// フェードの取得
	CFade* pFade = CManager::GetFade();

	int nPlayerLife = m_pPlayer->GetLife();

	if (nPlayerLife <= 0 || m_pTimer->GetTimer() <= 0)
	{
		m_state = STATE_END;
	}

	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_END:
		m_nCounterState++;

		if (m_nCounterState >= 60)
		{
			if (nPlayerLife <= 0)
			{
				pFade->SetFade(make_unique<CResultLose>());
			}
			else if (m_pTimer->GetTime() <= 0)
			{
				pFade->SetFade(make_unique<CResultWin>());
			}
		}
		break;
	default:
		break;
	}

	// ポーズのマネージャーの取得
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	CPauseManager::GetInstance()->SelectMenu();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_P))
	{
		if (pPauseManager != nullptr)
		{
			pPauseManager->EnablePause();
		}
	}

	static int ntimer = 0;
	if (CPauseManager::GetPause() == false)
	{
		ntimer = Wrap(ntimer + 1, 0, 600);
	}

	if ((ntimer % 600) == 0 && ntimer != 0)
	{
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			int Type = rand() % 4;
			float Angle = math::Randf(D3DX_PI * 2, 0.1f);
			D3DXVECTOR3 SetPos = m_pPlayer->GetPosition();
			SetPos.x += sinf(Angle) * 300.0f;
			SetPos.y += 50.0f;
			SetPos.z += cosf(Angle) * 300.0f;
			CEnemyManager::PushBackBullet(SetPos, Type);
		}
	}
#ifdef _DEBUG


	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_F9))
	{
		if (pFade != nullptr)
		{
			// シーンの遷移
			pFade->SetFade(make_unique<CResultWin>());
		}
	}

	if (pKeyboard->GetTrigger(DIK_2))
	{
		CEnemySphere::Create(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
	}
	if (pKeyboard->GetTrigger(DIK_3))
	{
		CEnemyNeedle::Create(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
	}
#endif // _DEBUG
}

//===================================================
// 描画処理
//===================================================
void CGame::Draw(void)
{
}

//===================================================
// スコアのセーブ
//===================================================
void CGame::SaveScore(void)
{
	// ファイルを開く
	ofstream file("data/TXT/result_score.txt");

	if (file.is_open())
	{

	}
	else
	{
		file.clear();
		MessageBox(NULL, "エラー", "SaveScore()", MB_OK);
		return;
	}
}
