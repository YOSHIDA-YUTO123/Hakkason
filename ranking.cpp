//===================================================
//
// ランキングシーン [ranking.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "ranking.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "title.h"
#include "meshfield.h"
#include "objectX.h"
#include "RankingScore.h"
#include "light.h"
#include "RankingManager.h"
#include "sound.h"

using namespace std;	// 名前空間stdの使用
using namespace Const;	// 名前空間Constの使用

//===================================================
// コンストラクタ
//===================================================
CRanking::CRanking() : CScene(MODE_RANKING)
{
}

//===================================================
// デストラクタ
//===================================================
CRanking::~CRanking()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CRanking::Init(void)
{
	// 音の取得
	CSound* pSound = CManager::GetSound();

	if (pSound != nullptr)
	{
		//// 音の再生
		//pSound->Play(CSound::SOUND_LABEL_BGM_RANKING,0.3f);
	}

	// 生成処理
	CRankingManager::Create();

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CRanking::Uninit(void)
{
	
}

//===================================================
// 更新処理
//===================================================
void CRanking::Update(void)
{
	// キーボードの取得
	auto pKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	auto pJoypad = CManager::GetInputJoypad();

	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		// フェードの取得
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// シーンの遷移
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// 描画処理
//===================================================
void CRanking::Draw(void)
{
}
