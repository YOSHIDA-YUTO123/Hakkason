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

	// メッシュフィールドの生成
	CMeshField::Create(VEC3_NULL, 10, 10, D3DXVECTOR2(500.0f, 500.0f));

	// スコアの表示
	CScore::Create(D3DXVECTOR3(1000.0f,100.0f,0.0f), D3DXVECTOR2(50.0f, 50.0f), 4649);

	// 普通のタイマーの生成
	CNormalTimer::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), 60);

	// 分と秒のタイマーの生成
	CDualUnitTimer::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), 5);

	CPlayer::Create(VEC3_NULL, 0.0f);

	m_pTitleManager = CTitleManager::CreateSingleton();

	//// メッシュシリンダーの生成
	//CMeshCylinder::Create(VEC3_NULL, -500.0f, 500.0f, 10, 10);

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
