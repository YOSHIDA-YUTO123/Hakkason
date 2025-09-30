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
#include "player.h"
#include "enemysphere.h"
#include "enemyneedle.h"
#include "DualUnitTimer.h"
#include "mapmanager.h"
#include "enemybonus.h"
#include "enemyshot.h"
#include "dome.h"
#include "math.h"

using namespace Const; // ���O���Const���g�p
using namespace std; // ���O���std���g�p

//***************************************************
// �ÓI�����o�ϐ��錾
//***************************************************
CGame::STATE CGame::m_state = STATE_NORMAL;					   // �Q�[���̏��
CPlayer* CGame::m_pPlayer = NULL;
CDualUnitTimer* CGame::m_pTimer = NULL;

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

	// �h�[���̐���
	CMeshDome::Create(VEC3_NULL, 10, 10, 5500.0f, 1500.0f);

	// �h�[���̐���
	CMeshDome::Create(VEC3_NULL, 10, 10, 5500.0f, -1500.0f);


	CMeshField::Create(VEC3_NULL, 5, 5, { 4000.0f,4000.0f });

	// �|�[�Y�}�l�[�W���[�̐���
	CPauseManager::Create();

	// ���ƕb�̃^�C�}�[�̐���
	m_pTimer = CDualUnitTimer::Create(D3DXVECTOR3(SCREEN_WIDTH - 50.0f, 50.0f, 0.0f), D3DXVECTOR2(50.0f, 25.0f), 60);

	// �C���X�^���X���擾->�ǂݍ���
	CMapManager::Instance()->Load("data\\TXT\\StageInfo.json");

	// �v���C���[����
	m_pPlayer = CPlayer::Create(VEC3_NULL, NULL);

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

	static int ntimer = 0;
	if (CPauseManager::GetPause() == false)
	{
		ntimer = Wrap(ntimer + 1, 0, 600);
	}

	if ((ntimer % 600) == 0 && ntimer != 0)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			int Type = rand() % 4;
			float Angle = math::Randf(D3DX_PI * 2, 0.1f);
			D3DXVECTOR3 SetPos = m_pPlayer->GetPosition();
			SetPos.x += sinf(Angle) * 300.0f;
			SetPos.z += cosf(Angle) * 300.0f;
			switch (Type)
			{
			case 0:
				CEnemySphere::Create(SetPos);
				break;
			case 1:
				CEnemyNeedle::Create(SetPos);
				break;
			case 2:
				CEnemyBonus::Create(SetPos);
				break;
			case 3:
				CEnemyShot::Create(SetPos);
				break;
			default:
				break;
			}
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

	if (pKeyboard->GetTrigger(DIK_2))
	{
		CEnemySphere::Create(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
	}
	if (pKeyboard->GetTrigger(DIK_3))
	{
		CEnemyNeedle::Create(D3DXVECTOR3(0.0f, 50.0f, 200.0f));
	}
#endif // _DEBUG
}

//===================================================
// �`�揈��
//===================================================
void CGame::Draw(void)
{
}
