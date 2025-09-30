//================================================
//
// �G [enemy.cpp]
// Author: KENSAKU HATORI
//
//================================================

#include "enemy.h"
#include "enemymanager.h"
#include "shadow.h"

// �萔�錾
constexpr int MAX_LIFE = 1; // �̗�
constexpr float SHADOW_WIDTH = 10.0f;  // �e�̉���
constexpr float SHADOW_HEIGHT = 10.0f; // �e�̏c��
constexpr float SHADOW_MAX_HEIGHT = 250.0f; // �e��������ő�̍���
constexpr float SHADOW_A_LEVEL = 0.8f; // �e�̉e�̍ő�̃A���t�@�l

//================================================
// �R���X�g���N�^
//================================================
CEnemy::CEnemy()
{
	m_nLife = MAX_LIFE;
}

//================================================
// �f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{
}

//================================================
// ����������
//================================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	// �e�̐���
	m_pShadow = CShadow::Create(pos, SHADOW_WIDTH, SHADOW_HEIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f));

	return E_NOTIMPL;
}

//================================================
// �I������
//================================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();
}

//================================================
// �X�V����
//================================================
void CEnemy::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 myPos = GetPosition();

	// �ʒu�����炷
	myPos += m_Move;

	// �ʒu��ݒ�
	SetPosition(myPos);

	// �e�Ƃ̓����蔻��
	CEnemyManager::CollisionBullet();

	// �X�V
	CObjectX::Update();

	if (m_pShadow != nullptr)
	{
		m_pShadow->Update(D3DXVECTOR3(myPos.x, 0.0f, myPos.z), D3DXVECTOR3(myPos.x, 0.0f, myPos.z), SHADOW_WIDTH, SHADOW_HEIGHT, SHADOW_MAX_HEIGHT, SHADOW_A_LEVEL);
	}

	// ���񂾂�j��
	if (m_nLife <= 0)
	{
		// ���������X�g����O��
		CEnemyManager::Erase(this);

		if (m_pShadow != nullptr)
		{
			m_pShadow->Uninit();
		}
	}
}

//================================================
// �`�揈��
//================================================
void CEnemy::Draw(void)
{
	if (m_pShadow != nullptr)
	{
		m_pShadow->Draw();
	}

	CObjectX::Draw();
}