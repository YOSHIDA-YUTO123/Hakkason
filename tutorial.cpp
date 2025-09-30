//****************************************************************
//
// �`���[�g���A���̏���[tutorial.h]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "tutorial.h"
#include "object2D.h"

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

	return S_OK;
}

//***************************************
// �X�V����
//***************************************
void CTutorial::Update(void)
{
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