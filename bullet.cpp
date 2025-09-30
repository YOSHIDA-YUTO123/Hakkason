//================================================
//
// �e [bullet.cpp]
// Author: KENSAKU HATORI
//
//================================================

// �C���N���[�h
#include "bullet.h"
#include "bulletmanager.h"
#include "shadow.h"

// �萔�錾
constexpr float SHADOW_WIDTH = 10.0f;  // �e�̉���
constexpr float SHADOW_HEIGHT = 10.0f; // �e�̏c��
constexpr float SHADOW_MAX_HEIGHT = 250.0f; // �e��������ő�̍���
constexpr float SHADOW_A_LEVEL = 0.8f; // �e�̉e�̍ő�̃A���t�@�l

//================================================
// �R���X�g���N�^
//================================================
CBullet::CBullet()
{
	m_pShadow = nullptr;
	m_nLife = NULL;
}

//================================================
// �f�X�g���N�^
//================================================
CBullet::~CBullet()
{
}

//================================================
// ����������
//================================================
HRESULT CBullet::Init(void)
{
	// ����������
	CObjectX::Init();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	// �e�̐���
	m_pShadow = CShadow::Create(pos, SHADOW_WIDTH, SHADOW_HEIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f));

	// ����I��
	return S_OK;
}

//================================================
// �X�V����
//================================================
void CBullet::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 myPos = GetPosition();

	// �ʒu�����炷
	myPos += m_Move;

	// �ݒ�
	SetPosition(myPos);

	// �X�V����
	CObjectX::Update();

	if (m_pShadow != nullptr)
	{
		m_pShadow->Update(D3DXVECTOR3(myPos.x, 0.0f, myPos.z), D3DXVECTOR3(myPos.x, 0.0f, myPos.z), SHADOW_WIDTH, SHADOW_HEIGHT, SHADOW_MAX_HEIGHT, SHADOW_A_LEVEL);
	}
	m_nLife--;

	// �������s������j��
	if (m_nLife <= 0)
	{
		// �����̔j��
		CBulletManager::Erase(this);

		if(m_pShadow != nullptr)
		{
			// �e�̔j��
			m_pShadow->Uninit();
		}
	}
}

//================================================
// �I������
//================================================
void CBullet::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//================================================
// �`�揈��
//================================================
void CBullet::Draw(void)
{
	if (m_pShadow != nullptr)
	{
		// �`��
		m_pShadow->Draw();
	}
	// �`�揈��
	CObjectX::Draw();
}

//================================================
// ��������
//================================================
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed, const int nLife)
{
	// �������m�ۂ��邽�߂̃C���X�^���X��錾
	CBullet* Instance = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	Instance = new CBullet;

	// �C���X�^���X�������ł��Ȃ�������
	if (Instance == nullptr) return nullptr;

	Instance->SetPosition(Pos);
	Instance->SetRotation(Rot);

	// ����������
	Instance->Init();
	Instance->m_Move = Dir * Speed;
	Instance->m_nLife = nLife;

	// ���f����ǂݍ���
	Instance->LoadModel("shotgun_ammo.x");

	// �C���X�^���X��Ԃ�
	return Instance;
}