//===================================================
//
// バレット管理 [bulletmanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// インクルード
#include "bulletmanager.h"

std::vector<CBullet*> CBulletManager::m_pvBullet;

//=================================================
// デストラクタ
//=================================================
CBulletManager::~CBulletManager()
{
}

//=================================================
// 弾を生成
//=================================================
void CBulletManager::PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// 配列に連結
	m_pvBullet.push_back(CBullet::Create(Pos, Rot, Dir, Speed));
}