//===================================================
//
// �Q�[���V�[�� [game.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
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

using namespace Const; // ���O���Const���g�p
using namespace std; // ���O���std���g�p

//***************************************************
// �ÓI�����o�ϐ��錾
//***************************************************
CGame::STATE CGame::m_state = STATE_NORMAL;					   // �Q�[���̏��

//===================================================
// �R���X�g���N�^
//===================================================
CGame::CGame() : CScene(MODE_GAME)
{
	m_nCounterState = NULL;
}

//===================================================
// �f�X�g���N�^
//===================================================
CGame::~CGame()
{

}

//===================================================
// ����������
//===================================================
HRESULT CGame::Init(void)
{
	// ���C�g�̎擾
	CLight* pLight = CManager::GetLight();
	pLight->Init();

	// ���C�g�̐ݒ菈��
	pLight->SetDirectional(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -0.56f, 0.74f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	pLight->SetDirectional(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -0.56f, -0.74f), D3DXVECTOR3(0.0f, 100.0f, 0.0f));

	CObject2D::Create(50.0f, 50.0f, CENTER_POS_2D)->SetTextureID("game.png");

	CMeshField::Create(VEC3_NULL, 5, 5, { 3000.0f,3000.0f });

	// �|�[�Y�}�l�[�W���[�̐���
	CPauseManager::Create();

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CGame::Uninit(void)
{
	// �|�[�Y�̃}�l�[�W���[�̎擾
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	if (pPauseManager != nullptr)
	{
		pPauseManager->Uninit();
	}
	// ��Ԃ̃��Z�b�g
	m_state = STATE_NORMAL;
}

//===================================================
// �X�V����
//===================================================
void CGame::Update(void)
{
	// �t�F�[�h�̎擾
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

	// �|�[�Y�̃}�l�[�W���[�̎擾
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	// �L�[�{�[�h�̎擾
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
			// �V�[���̑J��
			pFade->SetFade(make_unique<CResultWin>());
		}
	}
#endif // _DEBUG
}

//===================================================
// �`�揈��
//===================================================
void CGame::Draw(void)
{
}
