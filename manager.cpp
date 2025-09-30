//===================================================
//
// �}�l�[�W���[ [manager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "manager.h"
#include "renderer.h"
#include "object3D.h"
#include <ctime>
#include "Collision.h"
#include "sound.h"
#include "input.h"
#include "texmanager.h"
#include "modelManager.h"
#include "light.h"
#include "scene.h"
#include "object.h"
#include "fade.h"
#include "pause.h"
#include "CharacterManager.h"
#include "slow.h"
#include "camera.h"
#include "title.h"
#include "MeshCircle.h"
#include "particle3d.h"
#include "effect3d.h"

using namespace Const;			// ���O���Const���g�p����
using namespace std;			// ���O���std���g�p����

//***************************************************
// �ÓI�����o�ϐ��̐錾
//***************************************************
unique_ptr<CRenderer> CManager::m_pRenderer = nullptr;				// �����_���[�ւ̃|�C���^
unique_ptr<CInputKeyboard> CManager::m_pInputKeyboard = nullptr;	// �L�[�{�[�h�ւ̃|�C���^
unique_ptr<CInputJoypad> CManager::m_pInputJoypad = nullptr;		// �p�b�h�ւ̃|�C���^
unique_ptr<CInputMouse> CManager::m_pInputMouse = nullptr;			// �}�E�X�ւ̃|�C���^
unique_ptr<CSound> CManager::m_pSound = nullptr;					// �T�E���h�̃|�C���^
unique_ptr<CLight> CManager::m_pLight = nullptr;					// ���C�g�N���X�ւ̃|�C���^
unique_ptr<CScene> CManager::m_pScene = nullptr;					// �V�[���N���X�ւ̃|�C���^
unique_ptr<CSlow> CManager::m_pSlow = nullptr;						// �X���[���[�V�����N���X�ւ̃|�C���^
unique_ptr<CFade> CManager::m_pFade = nullptr;						// �t�F�[�h�N���X�ւ̃|�C���^
unique_ptr<CCamera> CManager::m_pCamera = nullptr;					// �J�����N���X�ւ̃|�C���^

int CManager::m_nFrameCounter = 0;									// �t���[���̃J�E���^�[
bool CManager::m_bShowDebug = true;									// �f�o�b�O�\�������邩���Ȃ���

//===================================================
// �R���X�g���N�^
//===================================================
CManager::CManager()
{
	m_fps = 0;
}
//===================================================
// �f�X�g���N�^
//===================================================
CManager::~CManager()
{
}

//===================================================
// ����������
//===================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow)
{
	// �����̎�̐ݒ�
	srand(static_cast<unsigned int>(time(nullptr)));

	// �����_���[�𐶐�
	m_pRenderer = make_unique<CRenderer>();

	// �T�E���h�̏���������
	m_pSound = make_unique<CSound>();

	// �L�[�{�[�h�𐶐�
	m_pInputKeyboard = make_unique<CInputKeyboard>();

	// �p�b�h�𐶐�
	m_pInputJoypad = make_unique<CInputJoypad>();

	// �}�E�X�𐶐�
	m_pInputMouse = make_unique<CInputMouse>();

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow))) return E_FAIL;

	// �T�E���h�̏���������
	if (FAILED(m_pSound->Init(hWnd))) return E_FAIL;

	// �L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd))) return E_FAIL;

	// �p�b�h�̏���������
	if (FAILED(m_pInputJoypad->Init())) return E_FAIL;

	// �}�E�X�̏���������
	if (FAILED(m_pInputMouse->Init(hWnd))) return E_FAIL;

	// �L�����N�^�[�}�l�[�W���[�̐���
	CCharacterManager::Create();

	// ���ׂẴe�N�X�`���̓ǂݍ��ݏ���
	CLoadTexture::Load("texture_list.txt");

	// ���ׂẴ��f���̃��[�h����
	CModelManager::Load("model_list.txt");

	// �J�����̐���
	m_pCamera = make_unique<CCamera>();
	m_pCamera->Init();
	m_pCamera->SetCamera(D3DXVECTOR3(0.0f, 250.0f, -350.0f), VEC3_NULL, D3DXVECTOR3(D3DX_PI * 0.65f, 0.0f, 0.0f));

	// ���C�g�̐���
	m_pLight = make_unique<CLight>();
	m_pLight->Init();

	// �t�F�[�h�̐���
	m_pFade.reset(CFade::Create());
	SetMode(make_unique<CTitle>());

	// �X���[�̐���
	m_pSlow = make_unique<CSlow>();
#ifdef _DEBUG

#else
	// �J�[�\�����\���ɂ���
	ShowCursor(false);
#endif // _DEBUG

	// ���ʂ�Ԃ�
	return S_OK;
}
//===================================================
// �I������
//===================================================
void CManager::Uninit(void)
{
	// ���ׂẴT�E���h�̒�~
	m_pSound->StopSound();

	// ���f���̔j��
	CModelManager::UnRegistModel();

	// �e�N�X�`���̔j��
	CLoadTexture::UnRegistTex();

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		// �I������
		m_pCamera->Uninit();
	}

	// ���C�g�̔j��
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		m_pLight = nullptr;
	}

	// �T�E���h�̔j��
	if (m_pSound != nullptr)
	{
		// �L�[�{�[�h�̏I������
		m_pSound->Uninit();
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
	}

	// �p�b�h�̔j��
	if (m_pInputJoypad != nullptr)
	{
		// �p�b�h�̏I������
		m_pInputJoypad->Uninit();
	}

	// �p�b�h�̔j��
	if (m_pInputMouse != nullptr)
	{
		// �}�E�X�̏I������
		m_pInputMouse->Uninit();
	}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		// �I�u�W�F�N�g�̏I������
		m_pRenderer->Uninit();
	}

	// �V�[���̔j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
	}

	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
	}
}
//===================================================
// �X�V����
//===================================================
void CManager::Update(void)
{
	// �t���[���̃J�E���^�[�𑝂₷
	m_nFrameCounter++;

	// 1�t���[���o�߂�����
	if (m_nFrameCounter > FRAME)
	{
		// �J�E���^�[�����Z�b�g
		m_nFrameCounter = 0;
	}

	if (m_pScene != nullptr)
	{
		// �V�[���̍X�V����
		m_pScene->Update();
	}

	if (m_pFade != nullptr)
	{
		// �t�F�[�h�̍X�V����
		m_pFade->Update();
	}
	

	if (m_pRenderer != nullptr)
	{
		// �X�V����
		m_pRenderer->Update();
	}
	

	if (m_pInputKeyboard != nullptr)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoypad != nullptr)
	{
		// �p�b�h�̍X�V����
		m_pInputJoypad->Update();
	}

	if (m_pInputMouse != nullptr)
	{
		// �}�E�X�̍X�V����
		m_pInputMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		// �J�����̍X�V����
		m_pCamera->Update();
	}

	if (m_pLight != nullptr)
	{	// ���C�g�̍X�V����
		m_pLight->Update();
	}

	if (m_pSlow != nullptr)
	{
		m_pSlow->Update();
	}

#ifdef _DEBUG

	if (m_pInputKeyboard->GetTrigger(DIK_5))
	{
		CMeshCircle::Create(VEC3_NULL, D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f), 0.0f, 50.0f)
			->SetParam(0.0f,5.0f,120);
	}
	if (m_pInputKeyboard->GetTrigger(DIK_F2))
	{
		m_bShowDebug = m_bShowDebug ? false : true;
	}
	if (m_pInputKeyboard->GetTrigger(DIK_6))
	{
		// �΂̏���ݒ�
		CParticle3D::DefoultEffectInfo FireInfo;
		FireInfo.Bece.Col = { 1.0f, 0.3f, 0.1f, 1.0f };
		FireInfo.Bece.fMaxSpeed = 1.0f;
		FireInfo.Bece.fMinSpeed = 1.0f;
		FireInfo.Bece.MaxDir = { 0.1f,0.5f,0.1f };
		FireInfo.Bece.MinDir = { -0.1f,0.5f,-0.1f };
		FireInfo.Bece.nLife = 1;
		FireInfo.Bece.nMaxLife = 30;
		FireInfo.Bece.nMinLife = 30;
		FireInfo.Bece.nNumEffect = 5;
		FireInfo.Bece.Pos = Const::VEC3_NULL;
		FireInfo.MaxRadius = 15.0f;
		FireInfo.MinRadius = 15.0f;
		FireInfo.Bece.bLoop = true;
		FireInfo.Bece.nCoolDown = 2;
		FireInfo.Bece.Gravity = 0.0f;
		FireInfo.Bece.FilePath = CEffect3D::Config::Smoke;
		FireInfo.Bece.nPriority = 5;

		// ����
		CParticle3D::Create(FireInfo);
	}

	// ���C���[�t���[���̏��
	static bool bWireFrame = false;

	if (m_pInputKeyboard->GetTrigger(DIK_F6))
	{
		bWireFrame = bWireFrame ? false : true;
	}

	if (bWireFrame == true)
	{
		m_pRenderer->onWireFrame();
	}
	else
	{
		m_pRenderer->offWireFrame();
	}

#endif // _DEBUG
}
//===================================================
// �`�揈��
//===================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		// �`�揈��
		m_pRenderer->Draw(m_fps);
	}
}

//===================================================
// �t���[���̃J�E���^�[
//===================================================
int CManager::GetFrameCounter(void)
{
	// ���݂̃t���[���̎擾
	return m_nFrameCounter;
}

//===================================================
// �V�[���̐ݒ菈��
//===================================================
void CManager::SetMode(unique_ptr<CScene> pNewScene)
{
	// ���̃V�[���̔j��
	if (m_pScene != nullptr)
	{
		// �I������
		m_pScene->Uninit();
		m_pScene.reset();
		m_pScene = nullptr;

		// ���ׂẴI�u�W�F�N�g�̔j��
		CObject::ReleaseAll();
	}
	
	// ��������j���ł��Ă���Ȃ�
	if (m_pScene == nullptr)
	{
		// �V�����V�[����ݒ�
		m_pScene = std::move(pNewScene);

		// �V�[���̏���������
		m_pScene->Init();
	}
}

//===================================================
// �V�[���̕`��
//===================================================
void CManager::DrawScene(void)
{
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}
