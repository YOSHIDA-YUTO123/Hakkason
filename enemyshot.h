//===================================================
//
// 打ってくる敵 [enemyshot.h]
// Author:YUTO YOSHIDA
//
//===================================================

// 二重インクルード
#ifndef _ENEMYSHOT_H_
#define _ENEMYSHOT_H_

// インクルード
#include "enemy.h"

// 棘敵クラスを派生
class CEnemyShot : public CEnemy
{
public:
	// コンストラクタ・デストラクタ
	CEnemyShot();
	~CEnemyShot();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemyShot* Create(D3DXVECTOR3 Pos);
private:
};
#endif // !_ENEMYNEEDLE_H_