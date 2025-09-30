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
#include "enemymanager.h"
#include "pause.h"
#include "sound.h"
#include "Gage.h"

using namespace Const; // ���O���Const���g�p
using namespace std; // ���O���std���g�p

//***************************************************
// �ÓI�����o�ϐ��錾
//***************************************************
CGame::STATE CGame::m_state = STATE_NORMAL;	// �Q�[���̏��
CPlayer* CGame::m_pPlayer = NULL;			// �v���C���[
CDualUnitTimer* CGame::m_pTimer = NULL;		// �^�C�}�[
int CGame::m_nScore = NULL;					// �X�R�A

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
	m_nScore = NULL;
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
	CMapManager::Instance()->Load("data\\TXT\\Stage000.json");

	CManager::GetSound()->Play(CSound::SOUND_LABEL_GAMEBGM);

	// �v���C���[����
	m_pPlayer = CPlayer::Create(VEC3_NULL, NULL);

	CHpGage::Create(D3DXVECTOR3(20.0f, 80.0f, 0.0f), D3DXVECTOR2(200.0f, 20.0f), D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f), D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f), m_pPlayer->GetLife(), true);

	CEnemyManager::Reset();

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		int Type = rand() % 4;
		float Angle = math::Randf(D3DX_PI * 2, 0.1f);
		D3DXVECTOR3 SetPos = m_pPlayer->GetPosition();
		SetPos.x += sinf(Angle) * 300.0f;
		SetPos.y += 50.0f;
		SetPos.z += cosf(Angle) * 300.0f;
		CEnemyManager::PushBackBullet(SetPos, Type);
	}

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

	int nPlayerLife = m_pPlayer->GetLife();

	if (nPlayerLife <= 0 || m_pTimer->GetTimer() <= 0)
	{
		m_state = STATE_END;
	}

	switch (m_state)
	{
	case STATE_NORMAL:
		break;
	case STATE_END:
		m_nCounterState++;

		if (m_nCounterState >= 60)
		{
			if (nPlayerLife <= 0)
			{
				pFade->SetFade(make_unique<CResultLose>());
			}
			else if (m_pTimer->GetTime() <= 0)
			{
				pFade->SetFade(make_unique<CResultWin>());
			}
		}
		break;
	default:
		break;
	}

	// �|�[�Y�̃}�l�[�W���[�̎擾
	CPauseManager* pPauseManager = CPauseManager::GetInstance();

	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	CPauseManager::GetInstance()->SelectMenu();

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
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			int Type = rand() % 4;
			float Angle = math::Randf(D3DX_PI * 2, 0.1f);
			D3DXVECTOR3 SetPos = m_pPlayer->GetPosition();
			SetPos.x += sinf(Angle) * 300.0f;
			SetPos.y += 50.0f;
			SetPos.z += cosf(Angle) * 300.0f;
			CEnemyManager::PushBackBullet(SetPos, Type);
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

//===================================================
// �X�R�A�̃Z�[�u
//===================================================
void CGame::SaveScore(void)
{
	// �t�@�C�����J��
	ofstream file("data/TXT/result_score.txt");

	if (file.is_open())
	{

	}
	else
	{
		file.clear();
		MessageBox(NULL, "�G���[", "SaveScore()", MB_OK);
		return;
	}
}
