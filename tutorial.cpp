//****************************************************************
//
// チュートリアルの処理[tutorial.h]
// Author Kensaku Hatori
//
//****************************************************************

// インクルード
#include "tutorial.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//***************************************
// コンストラクタ
//***************************************
CTutorial::CTutorial() : CScene(MODE_TUTORIAL)
{
}

//***************************************
// デストラクタ
//***************************************
CTutorial::~CTutorial()
{
}

//***************************************
// 初期化処理
//***************************************
HRESULT CTutorial::Init(void)
{
	CObject2D* LocalTutorial = CObject2D::Create(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, { SCREEN_WIDTH * 0.5f ,SCREEN_HEIGHT * 0.5f ,0.0f });
	LocalTutorial->SetTextureID("ttutorial.png");

	CManager::GetSound()->Play(CSound::SOUND_LABEL_TUTORIALBGM);

	return S_OK;
}

//***************************************
// 更新処理
//***************************************
void CTutorial::Update(void)
{
	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_START) == true || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) == true)
	{
		// フェードの取得
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
			// シーンの遷移
			pFade->SetFade(std::make_unique<CGame>());
		}
	}
}

//***************************************
// 終了処理
//***************************************
void CTutorial::Uninit(void)
{
}

//***************************************
// 描画処理
//***************************************
void CTutorial::Draw(void)
{
}