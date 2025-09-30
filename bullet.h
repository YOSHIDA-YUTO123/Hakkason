//================================================
//
// 弾 [bullet.h]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "objectX.h"

// 弾のクラスを定義
class CBullet : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CBullet();
	~CBullet();

	// メンバ関数
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	// 静的メンバ関数
	static CBullet* Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed);
private:
	D3DXVECTOR3 m_Move;		// 移動量
};