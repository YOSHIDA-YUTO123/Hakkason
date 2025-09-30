//****************************************************************
//
// �^�C�g�����j���[�̏���[titlemenu.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "titlemenu.h"
#include "titlemanager.h"
#include "texmanager.h"
#include "manager.h"
#include "math_T.h"
#include "input.h"
#include "fade.h"
#include "tutorial.h"
#include "pause.h"

// �K��l��ݒ�
const D3DXCOLOR CTitleMenu::Config::DefoultColor = { 1.0f,1.0f,1.0f,1.0f };
const D3DXCOLOR CTitleMenu::Config::SelectColor = { 0.0f,0.0f,1.0f,1.0f };

//***************************************
// ���N���X�̏���
//***************************************
//***************************************
// �R���X�g���N�^
//***************************************
CTitleMenu::CTitleMenu() : CObject2D(5)
{
}

//***************************************
// �f�X�g���N�^
//***************************************
CTitleMenu::~CTitleMenu()
{
}

//***************************************
// ����������
//***************************************
HRESULT CTitleMenu::Init(void)
{
	CObject2D::Init();
	return S_OK;
}

//***************************************
// �I������
//***************************************
void CTitleMenu::Uninit(void)
{
	CObject2D::Uninit();
}

//***************************************
// �X�V����
//***************************************
void CTitleMenu::Update(void)
{
	CObject2D::Update();
}

//***************************************
// �`�揈��
//***************************************
void CTitleMenu::Draw(void)
{
	CObject2D::Draw();
}

//***************************************
// ����
//***************************************
CTitleMenu* CTitleMenu::Create(D3DXVECTOR3 Pos, Menu Menu)
{
	// ��ނ��ő吔�ȏゾ������
	if (Menu >= CTitleMenu::MAX) return NULL;

	// �|�C���^�𐶐�
	CTitleMenu* pMenu = NULL;

	// ��ނ𔻕�
	switch (Menu)
	{
	case CTitleMenu::START:
		// �������m��
		pMenu = new CStart;
		break;
	case CTitleMenu::EXIT:
		// �������m��
		pMenu = new CExit;
		break;
	}

	// �e�폈��
	pMenu->Init();
	pMenu->SetPosition(Pos);
	pMenu->SetSize({ CTitleManager::Config::Menu::Width,CTitleManager::Config::Menu::Height });
	// �Ԃ�
	return pMenu;
}


//***************************************
// �h���N���X�̏���(Start)
//***************************************
//***************************************
// �R���X�g���N�^
//***************************************
CStart::CStart()
{
}

//***************************************
// �f�X�g���N�^
//***************************************
CStart::~CStart()
{
}

//***************************************
// ����������
//***************************************
HRESULT CStart::Init(void)
{
	CTitleMenu::Init();
	CTitleMenu::SetTextureID(Config::FilePath);
	return S_OK;
}

//***************************************
// �I������
//***************************************
void CStart::Uninit(void)
{
	CTitleMenu::Uninit();
}

//***************************************
// �X�V����
//***************************************
void CStart::Update(void)
{
	// �����̑傫��
	D3DXVECTOR2 Apper = { CTitleManager::Config::Menu::Width,CTitleManager::Config::Menu::Height };
	// �ڕW�̑傫��
	D3DXVECTOR2 Dest = { CTitleManager::Config::Menu::DestWidth,CTitleManager::Config::Menu::DestHeight };

	// ���I��ł���̂��X�^�[�g���j���[��������
	if (CTitleManager::GetSingleton()->GetSelectMenu() == START)
	{
		// �A�j���[�V�����J�E���^�[��i�߂�
		if (m_nAnimCounter < CTitleManager::Config::Menu::Frame)
		{
			m_nAnimCounter++;
		}
		// �ݒ肷��傫���̕ϐ�
		D3DXVECTOR2 Size = {};
		// ���̃A�j���[�V�����̐i�s�������v�Z
		float Ratio = EaseInOutSine((float)m_nAnimCounter / CTitleManager::Config::Menu::Frame);
		// �ŏI�I�ȑ傫�����珉���̑傫������̍���
		D3DXVECTOR2 Diff = { Dest.x - Apper.x,Dest.y - Apper.y };
		// ���̑傫�����v�Z
		Size = Apper + Diff * Ratio;

		CObject2D::SetSize(Size);
		CTitleMenu::SetColor(CTitleMenu::Config::SelectColor);

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputMouse()->OnMouseTriggerDown(0) == true ||
			CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) == true || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_START) == true)
		{
			if (CTitleManager::GetLower() == false)
			{
				CTitleManager::GetSingleton()->GetTitleLogo()->Lower();
			}
			else
			{
				CManager::GetFade()->SetFade(std::make_unique<CTutorial>());
				CPauseManager::GetInstance()->EnablePause(false);
			}
		}
	}
	else
	{
		m_nAnimCounter = 0;
		CObject2D::SetSize(Apper);
		CTitleMenu::SetColor(CTitleMenu::Config::DefoultColor);
	}
	CTitleMenu::Update();
}

//***************************************
// �`�揈��
//***************************************
void CStart::Draw(void)
{
	CTitleMenu::Draw();
}


//***************************************
// �h���N���X�̏���(Exit)
//***************************************
//***************************************
// �R���X�g���N�^
//***************************************
CExit::CExit()
{
}

//***************************************
// �f�X�g���N�^
//***************************************
CExit::~CExit()
{
}

//***************************************
// ����������
//***************************************
HRESULT CExit::Init(void)
{
	CTitleMenu::Init();
	CTitleMenu::SetTextureID(Config::FilePath);
	return S_OK;
}

//***************************************
// �I������
//***************************************
void CExit::Uninit(void)
{
	CTitleMenu::Uninit();
}

//***************************************
// �X�V����
//***************************************
void CExit::Update(void)
{
	// �����̑傫��
	D3DXVECTOR2 Apper = { CTitleManager::Config::Menu::Width,CTitleManager::Config::Menu::Height };
	// �ڕW�̑傫��
	D3DXVECTOR2 Dest = { CTitleManager::Config::Menu::DestWidth,CTitleManager::Config::Menu::DestHeight };

	// ���I��ł���̂�Exit���j���[��������
	if (CTitleManager::GetSingleton()->GetSelectMenu() == EXIT)
	{
		// �A�j���[�V�����J�E���^�[��i�߂�
		if (m_nAnimCounter < CTitleManager::Config::Menu::Frame)
		{
			m_nAnimCounter++;
		}
		// �ݒ肷��傫���̕ϐ�
		D3DXVECTOR2 Size = {};
		// ���̃A�j���[�V�����̐i�s�������v�Z
		float Ratio = EaseInOutSine((float)m_nAnimCounter / CTitleManager::Config::Menu::Frame);
		// �ŏI�I�ȑ傫�����珉���̑傫������̍���
		D3DXVECTOR2 Diff = { Dest.x - Apper.x,Dest.y - Apper.y };
		// ���̑傫�����v�Z
		Size = Apper + Diff * Ratio;

		CObject2D::SetSize(Size);
		CTitleMenu::SetColor(CTitleMenu::Config::SelectColor);

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true || CManager::GetInputMouse()->OnMouseTriggerDown(0) == true ||
			CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) == true || CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_START) == true)
		{
			if (CTitleManager::GetLower() == false)
			{
				CTitleManager::GetSingleton()->GetTitleLogo()->Lower();
			}
			else
			{
				PostQuitMessage(0);
			}
		}
	}
	else
	{
		m_nAnimCounter = 0;
		CObject2D::SetSize(Apper);
		CTitleMenu::SetColor(CTitleMenu::Config::DefoultColor);
	}
	CTitleMenu::Update();
}

//***************************************
// �`�揈��
//***************************************
void CExit::Draw(void)
{
	CTitleMenu::Draw();
}