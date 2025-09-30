//****************************************************************
//
// �`���[�g���A���̏���[tutorial.h]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "tutorial.h"
#include "object2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//***************************************
// �R���X�g���N�^
//***************************************
CTutorial::CTutorial() : CScene(MODE_TUTORIAL)
{
}

//***************************************
// �f�X�g���N�^
//***************************************
CTutorial::~CTutorial()
{
}

//***************************************
// ����������
//***************************************
HRESULT CTutorial::Init(void)
{
	CObject2D* LocalTutorial = CObject2D::Create(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, { SCREEN_WIDTH * 0.5f ,SCREEN_HEIGHT * 0.5f ,0.0f });
	LocalTutorial->SetTextureID("ttutorial.png");

	CManager::GetSound()->Play(CSound::SOUND_LABEL_TUTORIALBGM);

	return S_OK;
}

//***************************************
// �X�V����
//***************************************
void CTutorial::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_START) == true || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) == true)
	{
		// �t�F�[�h�̎擾
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
			// �V�[���̑J��
			pFade->SetFade(std::make_unique<CGame>());
		}
	}
}

//***************************************
// �I������
//***************************************
void CTutorial::Uninit(void)
{
}

//***************************************
// �`�揈��
//***************************************
void CTutorial::Draw(void)
{
}