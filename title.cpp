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

	// ���b�V���t�B�[���h�̐���
	CMeshField::Create(VEC3_NULL, 10, 10, D3DXVECTOR2(500.0f, 500.0f));

	// �X�R�A�̕\��
	CScore::Create(D3DXVECTOR3(1000.0f,100.0f,0.0f), D3DXVECTOR2(50.0f, 50.0f), 4649);

	// ���ʂ̃^�C�}�[�̐���
	CNormalTimer::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), 60);

	// ���ƕb�̃^�C�}�[�̐���
	CDualUnitTimer::Create(D3DXVECTOR3(640.0f, 500.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), 5);

	CPlayer::Create(VEC3_NULL, 0.0f);

	m_pTitleManager = CTitleManager::CreateSingleton();

	//// ���b�V���V�����_�[�̐���
	//CMeshCylinder::Create(VEC3_NULL, -500.0f, 500.0f, 10, 10);

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
