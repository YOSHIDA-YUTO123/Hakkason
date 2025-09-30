//===================================================
//
// �{�[�i�X�G [enemybonus.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// �C���N���[�h
#include "enemybonus.h"
#include "player.h"
#include "game.h"
#include "manager.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"

//===================================================
// �R���X�g���N�^
//===================================================
CEnemyBonus::CEnemyBonus()
{
}

//===================================================
// �f�X�g���N�^
//===================================================
CEnemyBonus::~CEnemyBonus()
{
}

//===================================================
// ����������
//===================================================
HRESULT CEnemyBonus::Init(void)
{
	// ����������
	CEnemy::Init();

	// ����I��
	return S_OK;
}

//===================================================
// �I������
//===================================================
void CEnemyBonus::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//===================================================
// �X�V����
//===================================================
void CEnemyBonus::Update(void)
{
	// �V�[�����Q�[���ȊO�Ȃ瑁�����^�[��
	if (CManager::GetMode() != CScene::MODE_GAME) return;
	// �v���C���[����������Ă��Ȃ������瑁�����^�[��
	if (CGame::GetPlayer() == NULL) return;

	// �e�̉ϒ��z��ɃA�N�Z�X
	for (auto Bullets = CBulletManager::GetpvBullet().begin(); Bullets != CBulletManager::GetpvBullet().end(); Bullets++)
	{
		// �G�ƒe�̋��̓����蔻������
		CColliderSphere EnemyCollider = CColliderSphere::CreateCollider(GetPosition(), 10.0f);
		CColliderSphere BulletCollider = CColliderSphere::CreateCollider((*Bullets)->GetPosition(), 10.0f);

		// ����������
		if (CCollisionSphere::Collision(&EnemyCollider, &BulletCollider) == true)
		{
			// �������g��j��
			Uninit();

			// �e�̘A��������
			CBulletManager::Erase((*Bullets));

			// ������؂�グ��
			return;
		}
	}

	// �v���C���[�܂ł̃x�N�g��������
	D3DXVECTOR3 pVec = CGame::GetPlayer()->GetModelPos(1) - GetPosition();

	// ���K��
	D3DXVec3Normalize(&pVec, &pVec);

	// �X�s�[�h��������
	pVec *= 2.0f;

	// �ݒ�
	SetMove(pVec);

	// �X�V����
	CEnemy::Update();
}

//===================================================
// �`�揈��
//===================================================
void CEnemyBonus::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//===================================================
// ����
//===================================================
CEnemyBonus* CEnemyBonus::Create(D3DXVECTOR3 Pos)
{
	// �������m�ۂ��邽�߂̃C���X�^���X��錾
	CEnemyBonus* Instance = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	Instance = new CEnemyBonus;

	// �C���X�^���X�������ł��Ȃ�������
	if (Instance == nullptr) return nullptr;

	// ����������
	Instance->Init();
	Instance->SetPosition(Pos);

	// ���f����ǂݍ���
	Instance->LoadModel("enemy_score.x");

	// �C���X�^���X��Ԃ�
	return Instance;
}