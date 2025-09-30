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
void CBulletManager::PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// �z��ɘA��
	m_pvBullet.push_back(CBullet::Create(Pos, Rot, Dir, Speed));
}