//===================================================
//
// 敵管理 [enemymanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "enemy.h"

// 前方宣言
class CColliderSphere;

class CEnemyManager
{
public:
	// デストラクタ
	~CEnemyManager();

	// 静的メンバ関数
	// ゲッター
	static std::vector<CEnemy*>& GetpvBullet(void) { return m_pvEnemy; }
	// セッター
	// 連結解除
	static void Erase(CEnemy* Instance);
	// 生成
	static void PushBackBullet(const D3DXVECTOR3 Pos, int Type);

	static void CollisionBullet(void);
private:
	// コンストラクタ
	CEnemyManager() {};
	// 静的メンバ変数
	static std::vector<CEnemy*> m_pvEnemy;	// バレットの可変長配列
};
#endif // !_ENEMYMANAGER_H_