//===================================================
//
// タイトルシーン [title.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "title.h"
#include "object2D.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "meshfield.h"
#include "light.h"
#include "MeshCylinder.h"
#include "MeshCircle.h"
#include "score.h"
#include "NormalTimer.h"
#include "DualUnitTimer.h"
#include "player.h"
#include "titlemanager.h"
#include "mapmanager.h"
#include "dome.h"

using namespace Const;	// 名前空間Constの使用
using namespace std;	// 名前空間stdの使用

CTitleManager* CTitle::m_pTitleManager = NULL;

//===================================================
// コンストラクタ
//===================================================
CTitle::CTitle() : CScene(MODE_TITLE)
{

}

//===================================================
// デストラクタ
//===================================================
CTitle::~CTitle()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CTitle::Init(void)
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

	// インスタンスを取得->読み込み
	CMapManager::Instance()->Load("data\\TXT\\Stage000.json");

	// プレイヤー生成
	CPlayer::Create(VEC3_NULL, NULL);

	CPlayer::Create(VEC3_NULL, 0.0f);

	m_pTitleManager = CTitleManager::CreateSingleton();

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CTitle::Uninit(void)
{
}

//===================================================
// 更新処理
//===================================================
void CTitle::Update(void)
{
#ifdef _DEBUG

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_F9))
	{
		// フェードの取得
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// シーンの遷移
			pFade->SetFade(make_unique<CGame>());
		}
	}
#endif // _DEBUG

}

//===================================================
// 描画処理
//===================================================
void CTitle::Draw(void)
{
}
