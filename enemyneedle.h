//===================================================
//
// 棘敵 [enemyneedle.h]
// Author:YUTO YOSHIDA
//
//===================================================

#ifndef _ENEMYNEEDLE_H_
#define _ENEMYNEEDLE_H_

// インクルード
#include "enemy.h"

// 棘敵クラスを派生
class CEnemyNeedle : public CEnemy
{
public:
	// コンストラクタ・デストラクタ
	CEnemyNeedle();
	~CEnemyNeedle();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemyNeedle* Create(D3DXVECTOR3 Pos);
private:
};
#endif // !_ENEMYNEEDLE_H_