//===================================================
//
// �o���b�g�Ǘ� [bulletmanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// �C���N���[�h
#include "bulletmanager.h"

std::vector<CBullet*> CBulletManager::m_pvBullet;

//=================================================
// �f�X�g���N�^
//=================================================
CBulletManager::~CBulletManager()
{
}

//=================================================
// �e�𐶐�
//=================================================
void CBulletManager::Erase(CBullet* Instance)
{
	// �I�u�W�F�N�g�̃��X�g����I������Ă���I�u�W�F�N�g��T��
	for (auto Bullets = m_pvBullet.begin(); Bullets != m_pvBullet.end(); Bullets++)
	{
		// ��������
		if ((*Bullets) == Instance)
		{
			// �I������
			(*Bullets)->Uninit();

			// ���X�g�̘A��������
			Bullets = m_pvBullet.erase(Bullets);

			// �폜������Ƀ��X�g�ɃI�u�W�F�N�g�����݂��Ȃ������珈����؂�グ��
			if (Bullets == m_pvBullet.end()) break;
		}
	}
}

//=================================================
// �e�𐶐�
//=================================================
void CBulletManager::PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// �z��ɘA��
	m_pvBullet.push_back(CBullet::Create(Pos, Rot, Dir, Speed));
}