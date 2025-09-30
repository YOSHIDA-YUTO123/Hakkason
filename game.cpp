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

using namespace Const; // 名前空間Constを使用
using namespace std; // 名前空間stdを使用

//***************************************************
// 静的メンバ変数宣言
//***************************************************
CGame::STATE CGame::m_state = STATE_NORMAL;					   // ゲームの状態

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

	CObject2D::Create(50.0f, 50.0f, CENTER_POS_2D)->SetTextureID("game.png");

	CMeshField::Create(VEC3_NULL, 5, 5, { 3000.0f,3000.0f });

	// ポーズマネージャーの生成
	CPauseManager::Create();

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

	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_END:
		m_nCounterState++;

		if (m_nCounterState <= 0)
		{

		}
		break;
	default:
		break;
	}

	// ポーズのマネージャーの取得
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_P))
	{
		if (pPauseManager != nullptr)
		{
			pPauseManager->EnablePause();
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
#endif // _DEBUG
}

//===================================================
// 描画処理
//===================================================
void CGame::Draw(void)
{
}
