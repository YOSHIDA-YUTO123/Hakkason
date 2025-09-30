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
#include <fstream>
#include "score.h"
#include "ranking.h"

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
	// スコアのロード
	int nScore = LoadScore();

	// 2Dポリゴンの生成
	CObject2D::Create(300.0f,100.0f,D3DXVECTOR3(640.0f,200.0f,0.0f))->SetTextureID("clear.png");

	// スコアの生成
	CScore::Create(D3DXVECTOR3(640.0f,400.0f,0.0f), D3DXVECTOR2(300.0f, 100.0f), nScore);

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

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// 新しいモードの設定
			pFade->SetFade(make_unique<CRanking>());
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
// スコアのロード
//===================================================
int CResultWin::LoadScore(void)
{
	// ファイルを開く
	fstream file("data/TXT/result_score.txt");
	string line, input;

	string filepath;	// ファイルパス

	int nScore = 0;

	// nullじゃなかったら
	if (file.is_open())
	{
		file >> nScore;

		file.close();
		file.clear();
	}
	else
	{
		MessageBox(NULL, "エラー", "LoadScore", MB_OK);
		return 0;
	}


	return nScore;
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
	// 2Dポリゴンの生成
	CObject2D::Create(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, CENTER_POS_2D)->SetTextureID("game over.png");

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

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
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
