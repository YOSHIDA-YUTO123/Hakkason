//===================================================
//
// バレット管理 [bulletmanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

// 二重インクルード防止
#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

// インクルード
#include "object.h"
#include "bullet.h"
#include <vector>

// 弾を一括管理するクラスを定義
class CBulletManager
{
public:
	// デストラクタ
	~CBulletManager();

	// 静的メンバ関数
	// ゲッター
	static std::vector<CBullet*>& GetpvBullet(void) { return m_pvBullet; }
	// セッター
	// 生成
	static void PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed);
protected:
private:
	// コンストラクタ
	CBulletManager() {};
	// 静的メンバ変数
	static std::vector<CBullet*> m_pvBullet;	// バレットの可変長配列
};
#endif // !_BULLETMANAGER_H_