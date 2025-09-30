//================================================
//
// 球敵 [enemysphere.h]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "enemy.h"

// 球体の敵クラスを定義
class CEnemySphere : public CEnemy
{
public:
	// コンストラクタ・デストラクタ
	CEnemySphere();
	~CEnemySphere();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEnemySphere* Create(D3DXVECTOR3 Pos);
private:
};