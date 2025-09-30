//===================================================
//
// リザルトシーン [result.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "result.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "objectX.h"
#include "game.h"
#include "light.h"
#include "sound.h"
#include "title.h"
#include "object2D.h"

using namespace Const; // 名前空間Constを使用
using namespace std; // 名前空間stdを使用

//===================================================
// コンストラクタ
//===================================================
CResultWin::CResultWin() : CScene(MODE_RESULT)
{
}

//===================================================
// デストラクタ
//===================================================
CResultWin::~CResultWin()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CResultWin::Init(void)
{
	CObject2D::Create(50.0f, 50.0f, CENTER_POS_2D)->SetTextureID("result.png");

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CResultWin::Uninit(void)
{
}

//===================================================
// 更新処理
//===================================================
void CResultWin::Update(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoypad* pJoypad = CManager::GetInputJoypad();

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_F9) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// 新しいモードの設定
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// 描画処理
//===================================================
void CResultWin::Draw(void)
{
}

//===================================================
// コンストラクタ
//===================================================
CResultLose::CResultLose() : CScene(MODE_RESULT)
{

}

//===================================================
// デストラクタ
//===================================================
CResultLose::~CResultLose()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CResultLose::Init(void)
{
	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CResultLose::Uninit(void)
{
}

//===================================================
// 更新処理
//===================================================
void CResultLose::Update(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoypad* pJoypad = CManager::GetInputJoypad();

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_F9) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// 新しいモードの設定
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// 描画処理
//===================================================
void CResultLose::Draw(void)
{
}
