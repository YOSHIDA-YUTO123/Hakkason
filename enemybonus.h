//===================================================
//
// ボーナス敵 [enemybonus.h]
// Author:YUTO YOSHIDA
//
//===================================================

// 二重インクルード
#ifndef _ENEMYBONUS_H_
#define _ENEMYBONUS_H_

// インクルード
#include "enemy.h"

// 棘敵クラスを派生
class CEnemyBonus : public CEnemy
{
public:
	// コンストラクタ・デストラクタ
	CEnemyBonus();
	~CEnemyBonus();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemyBonus* Create(D3DXVECTOR3 Pos);
private:
	int m_nTimer;	// 生存時間
};
#endif // !_ENEMYNEEDLE_H_