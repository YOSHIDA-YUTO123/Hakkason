//================================================
//
// 敵 [enemy.h]
// Author: KENSAKU HATORI
//
//================================================

// 二重インクルード防止
#ifndef _ENEMY_H_
#define _ENEMY_H_

// インクルード
#include "objectX.h"
#include <string>

// 敵の基底クラスを定義
class CEnemy : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CEnemy();
	~CEnemy();

	// メンバ関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// セッター
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	// ゲッター
	D3DXVECTOR3 GetMove(void) { return m_Move; }
private:
	D3DXVECTOR3 m_Move;	// 移動量
};
#endif // !_ENEMY_H_