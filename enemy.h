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
#include <memory>

// 前方宣言
class CShadow;

// 敵の基底クラスを定義
class CEnemy : public CObjectX
{
public:

	typedef enum
	{
		TYPE_ONE = 0,
		TYPE_TWO,
		TYPE_THREE,
		TYPE_FOUR,
		TYPE_MAX
	}TYPE;

	// コンストラクタ・デストラクタ
	CEnemy();
	CEnemy(const TYPE type);
	~CEnemy();

	// メンバ関数
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetDamage(const int nDamage) { m_nLife -= nDamage; }

	// セッター
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }

	// ゲッター
	D3DXVECTOR3 GetMove(void) { return m_Move; }
private:
	std::unique_ptr<CShadow> m_pShadow; // 影のクラスへのポインタ
	D3DXVECTOR3 m_Move;	// 移動量
	TYPE m_type;		// 種類
	int m_nLife;		// 体力
};
#endif // !_ENEMY_H_