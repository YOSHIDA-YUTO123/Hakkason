//****************************************************************
//
// �^�C�g���}�l�W���[�̏���[titlemanager.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "titlemanager.h"
#include "manager.h"
#include "math_T.h"
#include "sound.h"
#include "input.h"

// �K��l��ݒ�
const D3DXVECTOR3 CTitleManager::Config::Menu::Bace = { 650.0f,500.0f,0.0f };
const D3DXVECTOR3 CTitleManager::Config::Logo::Apper = { 650.0f,0.0f,0.0f };
const D3DXVECTOR3 CTitleManager::Config::Logo::Dest = { 650.0f,200.0f,0.0f };
const D3DXVECTOR2 CTitleManager::Config::Logo::Size = { 450.0f,200.0f };

// �V���O���g����錾
CTitleManager* CTitleManager::m_Singleton = NULL;

//***************************************
// �f�X�g���N�^
//***************************************
CTitleManager::~CTitleManager()
{
}

//***************************************
// ����������
//***************************************
HRESULT CTitleManager::Init(void)
{
	// �I��ł����j���[
	m_SelectMenu = CTitleMenu::START;
	// ���j���[����C�ɐ���
	for (int nCount = 0; nCount < CTitleMenu::MAX; nCount++)
	{
		CTitleMenu* pTitleMenu = CTitleMenu::Create(D3DXVECTOR3(CTitleManager::Config::Menu::Bace.x, CTitleManager::Config::Menu::Bace.y + CTitleManager::Config::Menu::OffSet * nCount, 0.0f), (CTitleMenu::Menu)nCount);
		m_apTitleMenu.push_back(pTitleMenu);
	}
	//w ���S�𐶐�
	m_TitleLogo = CTitleLogo::Create(CTitleManager::Config::Logo::Apper, Const::VEC3_NULL, CTitleManager::Config::Logo::Size, CTitleManager::Config::Logo::FilePath);
	return S_OK;
}

//***************************************
// �I������
//***************************************
void CTitleManager::Uninit(void)
{
	// �V���O���g���̏I������
	if (m_Singleton != NULL)
	{
		m_apTitleMenu.clear();
		m_Singleton = NULL;
	}
	// �������g�̔j��
	Release();
}

//***************************************
// �X�V����
//***************************************
void CTitleManager::Update(void)
{
	// ���j���[��I��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) == true || CManager::GetInputMouse()->GetMouseWeel() < 0 ||
		CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_UP) == true)
	{
		m_SelectMenu = (CTitleMenu::Menu)Wrap(m_SelectMenu - 1, 0, (int)CTitleMenu::MAX - 1);
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true || CManager::GetInputMouse()->GetMouseWeel() > 0 ||
		CManager::GetInputJoypad()->GetTrigger(CInputJoypad::JOYKEY_DOWN) == true)
	{
		m_SelectMenu = (CTitleMenu::Menu)Wrap(m_SelectMenu + 1, 0, (int)CTitleMenu::MAX - 1);
	}
}

//***************************************
// �V���O���g���𐶐�
//***************************************
CTitleManager* CTitleManager::CreateSingleton(void)
{
	// �V���O���g������������Ă�����
	if (m_Singleton != NULL) return m_Singleton;
	// �������m��
	m_Singleton = new CTitleManager;
	// ����������
	m_Singleton->Init();
	// �Ԃ�
	return m_Singleton;
}