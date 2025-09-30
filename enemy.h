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
	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};