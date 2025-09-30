//===================================================
//
// �^�C�g���V�[�� [title.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "title.h"
#include "object2D.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "meshfield.h"
#include "light.h"
#include "MeshCylinder.h"
#include "MeshCircle.h"
#include "score.h"
#include "NormalTimer.h"
#include "DualUnitTimer.h"
#include "player.h"
#include "titlemanager.h"
#include "mapmanager.h"
#include "dome.h"

using namespace Const;	// ���O���Const�̎g�p
using namespace std;	// ���O���std�̎g�p

CTitleManager* CTitle::m_pTitleManager = NULL;

//===================================================
// �R���X�g���N�^
//===================================================
CTitle::CTitle() : CScene(MODE_TITLE)
{

}

//===================================================
// �f�X�g���N�^
//===================================================
CTitle::~CTitle()
{
}

//===================================================
// ����������
//===================================================
HRESULT CTitle::Init(void)
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

	// �C���X�^���X���擾->�ǂݍ���
	CMapManager::Instance()->Load("data\\TXT\\Stage000.json");

	// �v���C���[����
	CPlayer::Create(VEC3_NULL, NULL);

	CPlayer::Create(VEC3_NULL, 0.0f);

	m_pTitleManager = CTitleManager::CreateSingleton();

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CTitle::Uninit(void)
{
}

//===================================================
// �X�V����
//===================================================
void CTitle::Update(void)
{
#ifdef _DEBUG

	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_F9))
	{
		// �t�F�[�h�̎擾
		CFade* pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			// �V�[���̑J��
			pFade->SetFade(make_unique<CGame>());
		}
	}
#endif // _DEBUG

}

//===================================================
// �`�揈��
//===================================================
void CTitle::Draw(void)
{
}
