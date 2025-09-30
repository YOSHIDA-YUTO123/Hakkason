//===================================================
//
// 敵管理 [enemymanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// インクルード
#include "enemymanager.h"
#include "enemybonus.h"
#include "enemyneedle.h"
#include "enemyshot.h"
#include "enemysphere.h"

// 静的メンバ変数
std::vector<CEnemy*> CEnemyManager::m_pvEnemy;

//===================================================
// コンストラクタ
//===================================================
CEnemyManager::~CEnemyManager()
{
}

//===================================================
// 連結解除
//===================================================
void CEnemyManager::Erase(CEnemy* Instance)
{
	// オブジェクトのリストから選択されているオブジェクトを探す
	for (auto Enemeys = m_pvEnemy.begin(); Enemeys != m_pvEnemy.end(); Enemeys++)
	{
		// あったら
		if ((*Enemeys) == Instance)
		{
			// 終了処理
			(*Enemeys)->Uninit();

			// リストの連結を解除
			Enemeys = m_pvEnemy.erase(Enemeys);

			// 削除した後にリストにオブジェクトが存在しなかったら処理を切り上げる
			if (Enemeys == m_pvEnemy.end()) break;
		}
	}
}

//===================================================
// 連結
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
	// 配列に連結
	m_pvEnemy.push_back(LocalEnemy);
}