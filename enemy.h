//================================================
//
// 敵 [enemy.h]
// Author: KENSAKU HATORI
//
//================================================

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
private:
};