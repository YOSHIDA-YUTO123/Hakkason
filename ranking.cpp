//===================================================
//
// �����L���O�V�[�� [ranking.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
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

using namespace std;	// ���O���std�̎g�p
using namespace Const;	// ���O���Const�̎g�p

//===================================================
// �R���X�g���N�^
//===================================================
CRanking::CRanking() : CScene(MODE_RANKING)
{
}

//===================================================
// �f�X�g���N�^
//===================================================
CRanking::~CRanking()
{
}

//===================================================
// ����������
//===================================================
HRESULT CRanking::Init(void)
{
	// ���̎擾
	CSound* pSound = CManager::GetSound();

	if (pSound != nullptr)
	{
		//// ���̍Đ�
		//pSound->Play(CSound::SOUND_LABEL_BGM_RANKING,0.3f);
	}

	// ��������
	CRankingManager::Create();

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CRanking::Uninit(void)
{
	
}

//===================================================
// �X�V����
//===================================================
void CRanking::Update(void)
{
	// �L�[�{�[�h�̎擾
	auto pKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	auto pJoypad = CManager::GetInputJoypad();

	if (pKeyboard->GetTrigger(DIK_RETURN) || pJoypad->GetTrigger(pJoypad->JOYKEY_A))
	{
		// �t�F�[�h�̎擾
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// �V�[���̑J��
			pFade->SetFade(make_unique<CTitle>());
		}
	}
}

//===================================================
// �`�揈��
//===================================================
void CRanking::Draw(void)
{
}
