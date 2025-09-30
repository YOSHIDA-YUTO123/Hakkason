//===================================================
//
// �G�Ǘ� [enemymanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// �C���N���[�h
#include "enemymanager.h"
#include "enemybonus.h"
#include "enemyneedle.h"
#include "enemyshot.h"
#include "enemysphere.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"

// �ÓI�����o�ϐ�
std::vector<CEnemy*> CEnemyManager::m_pvEnemy;

//===================================================
// �R���X�g���N�^
//===================================================
CEnemyManager::~CEnemyManager()
{
}

//===================================================
// �A������
//===================================================
void CEnemyManager::Erase(CEnemy* Instance)
{
	// �I�u�W�F�N�g�̃��X�g����I������Ă���I�u�W�F�N�g��T��
	for (auto Enemeys = m_pvEnemy.begin(); Enemeys != m_pvEnemy.end(); Enemeys++)
	{
		// ��������
		if ((*Enemeys) == Instance)
		{
			// �I������
			(*Enemeys)->Uninit();

			// ���X�g�̘A��������
			Enemeys = m_pvEnemy.erase(Enemeys);

			// �폜������Ƀ��X�g�ɃI�u�W�F�N�g�����݂��Ȃ������珈����؂�グ��
			if (Enemeys == m_pvEnemy.end()) break;
		}
	}
}

//===================================================
// �A��
//===================================================
void CEnemyManager::PushBackBullet(const D3DXVECTOR3 Pos, int Type)
{
	CEnemy* LocalEnemy = NULL;

	switch (Type)
	{
	case 0:
		LocalEnemy = CEnemySphere::Create(Pos);
		break;
	case 1:
		LocalEnemy = CEnemyNeedle::Create(Pos);
		break;
	case 2:
		LocalEnemy = CEnemyBonus::Create(Pos);
		break;
	case 3:
		LocalEnemy = CEnemyShot::Create(Pos);
		break;
	default:
		break;
	}
	// �z��ɘA��
	m_pvEnemy.push_back(LocalEnemy);
}

//===================================================
// �����蔻��
//===================================================
void CEnemyManager::CollisionBullet(void)
{
	// �I�u�W�F�N�g�̃��X�g����I������Ă���I�u�W�F�N�g��T��
	for (auto Enemeys = m_pvEnemy.begin(); Enemeys != m_pvEnemy.end(); Enemeys++)
	{
		// �e�̉ϒ��z��ɃA�N�Z�X
		for (auto Bullets = CBulletManager::GetpvBullet().begin(); Bullets != CBulletManager::GetpvBullet().end(); Bullets++)
		{
			// �G�ƒe�̋��̓����蔻������
			CColliderSphere EnemyCollider = CColliderSphere::CreateCollider((*Enemeys)->GetPosition(), 10.0f);
			CColliderSphere BulletCollider = CColliderSphere::CreateCollider((*Bullets)->GetPosition(), 10.0f);

			// ����������
			if (CCollisionSphere::Collision(&EnemyCollider, &BulletCollider) == true)
			{
				(*Enemeys)->SetDamage(1);

				// �e�̘A��������
				CBulletManager::Erase((*Bullets));

				// ������؂�グ��
				return;
			}
		}
	}
}
