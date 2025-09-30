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
#include <fstream>
#include "score.h"
#include "ranking.h"

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
	// �X�R�A�̃��[�h
	int nScore = LoadScore();

	// 2D�|���S���̐���
	CObject2D::Create(300.0f,100.0f,D3DXVECTOR3(640.0f,200.0f,0.0f))->SetTextureID("clear.png");

	// �X�R�A�̐���
	CScore::Create(D3DXVECTOR3(640.0f,400.0f,0.0f), D3DXVECTOR2(300.0f, 100.0f), nScore);

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

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// �V�������[�h�̐ݒ�
			pFade->SetFade(make_unique<CRanking>());
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
// �X�R�A�̃��[�h
//===================================================
int CResultWin::LoadScore(void)
{
	// �t�@�C�����J��
	fstream file("data/TXT/result_score.txt");
	string line, input;

	string filepath;	// �t�@�C���p�X

	int nScore = 0;

	// null����Ȃ�������
	if (file.is_open())
	{
		file >> nScore;

		file.close();
		file.clear();
	}
	else
	{
		MessageBox(NULL, "�G���[", "LoadScore", MB_OK);
		return 0;
	}


	return nScore;
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
	// 2D�|���S���̐���
	CObject2D::Create(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, CENTER_POS_2D)->SetTextureID("game over.png");

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

	if ((pKeyboard != nullptr && pJoypad != nullptr) && pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
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
