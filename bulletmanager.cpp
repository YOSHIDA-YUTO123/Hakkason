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
void CBulletManager::Erase(CBullet* Instance)
{
	// オブジェクトのリストから選択されているオブジェクトを探す
	for (auto Bullets = m_pvBullet.begin(); Bullets != m_pvBullet.end(); Bullets++)
	{
		// あったら
		if ((*Bullets) == Instance)
		{
			// 終了処理
			(*Bullets)->Uninit();

			// リストの連結を解除
			Bullets = m_pvBullet.erase(Bullets);

			// 削除した後にリストにオブジェクトが存在しなかったら処理を切り上げる
			if (Bullets == m_pvBullet.end()) break;
		}
	}
}

//=================================================
// 弾を生成
//=================================================
void CBulletManager::PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// 配列に連結
	m_pvBullet.push_back(CBullet::Create(Pos, Rot, Dir, Speed));
}