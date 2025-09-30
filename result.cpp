//===================================================
//
// ���U���g�V�[�� [result.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
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

using namespace Const; // ���O���Const���g�p
using namespace std; // ���O���std���g�p

//===================================================
// �R���X�g���N�^
//===================================================
CResultWin::CResultWin() : CScene(MODE_RESULT)
{
}

//===================================================
// �f�X�g���N�^
//===================================================
CResultWin::~CResultWin()
{
}

//===================================================
// ����������
//===================================================
HRESULT CResultWin::Init(void)
{
	CObject2D::Create(50.0f, 50.0f, CENTER_POS_2D)->SetTextureID("result.png");

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CResultWin::Uninit(void)
{
}

//===================================================
// �X�V����
//===================================================
void CResultWin::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoypad* pJoypad = CManager::GetInputJoypad();

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_F9) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// �V�������[�h�̐ݒ�
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// �`�揈��
//===================================================
void CResultWin::Draw(void)
{
}

//===================================================
// �R���X�g���N�^
//===================================================
CResultLose::CResultLose() : CScene(MODE_RESULT)
{

}

//===================================================
// �f�X�g���N�^
//===================================================
CResultLose::~CResultLose()
{
}

//===================================================
// ����������
//===================================================
HRESULT CResultLose::Init(void)
{
	return S_OK;
}

//===================================================
// �I������
//===================================================
void CResultLose::Uninit(void)
{
}

//===================================================
// �X�V����
//===================================================
void CResultLose::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoypad* pJoypad = CManager::GetInputJoypad();

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_F9) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// �V�������[�h�̐ݒ�
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// �`�揈��
//===================================================
void CResultLose::Draw(void)
{
}
