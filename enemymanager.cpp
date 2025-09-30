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
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "game.h"
#include "player.h"
#include "debugproc.h"

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

//===================================================
// 当たり判定
//===================================================
void CEnemyManager::CollisionBullet(void)
{
	// オブジェクトのリストから選択されているオブジェクトを探す
	for (auto Enemeys = m_pvEnemy.begin(); Enemeys != m_pvEnemy.end(); Enemeys++)
	{
		// 弾の可変長配列にアクセス
		for (auto Bullets = CBulletManager::GetpvBullet().begin(); Bullets != CBulletManager::GetpvBullet().end(); Bullets++)
		{
			// 敵と弾の球の当たり判定を作る
			CColliderSphere EnemyCollider = CColliderSphere::CreateCollider((*Enemeys)->GetPosition(), 10.0f);
			CColliderSphere BulletCollider = CColliderSphere::CreateCollider((*Bullets)->GetPosition(), 10.0f);

			// 当たったら
			if (CCollisionSphere::Collision(&EnemyCollider, &BulletCollider) == true)
			{
				(*Enemeys)->SetDamage(1);

				// 弾の連結を解除
				CBulletManager::Erase((*Bullets));

				// 処理を切り上げる
				return;
			}
		}
	}
}

//===================================================
// プレイヤーとの当たり判定
//===================================================
void CEnemyManager::CollisionPlayer(void)
{
	// プレイヤーの取得
	CPlayer* pPlayer = CGame::GetPlayer();

	// 取得できなかったら処理しない
	if (pPlayer == nullptr) return;

	// オブジェクトのリストから選択されているオブジェクトを探す
	for (auto Enemeys = m_pvEnemy.begin(); Enemeys != m_pvEnemy.end(); Enemeys++)
	{
		// プレイヤーの位置
		D3DXVECTOR3 playerPos = pPlayer->GetPosition();
		D3DXVECTOR3 playerHead = D3DXVECTOR3(playerPos.x, playerPos.y + 200.0f, playerPos.z);

		// 敵と弾の球の当たり判定を作る
		CColliderSphere EnemyCollider = CColliderSphere::CreateCollider((*Enemeys)->GetPosition(), 10.0f);
		CColliderSphere playerCollider = CColliderSphere::CreateCollider(playerPos,50.0f);

		// 当たり判定
		if (CCollisionSphere::Collision(&playerCollider, &EnemyCollider))
		{
			// 敵に当たった
			CDebugProc::Print("プレイヤーと敵衝突\n");

			// プレイヤーに当たった
			pPlayer->Hit(1);

			return;
		}
	}
}
