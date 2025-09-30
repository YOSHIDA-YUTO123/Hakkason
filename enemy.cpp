//================================================
//
// 敵 [enemy.cpp]
// Author: KENSAKU HATORI
//
//================================================

#include "enemy.h"
#include "enemymanager.h"
#include "shadow.h"

// 定数宣言
constexpr int MAX_LIFE = 1; // 体力
constexpr float SHADOW_WIDTH = 10.0f;  // 影の横幅
constexpr float SHADOW_HEIGHT = 10.0f; // 影の縦幅
constexpr float SHADOW_MAX_HEIGHT = 250.0f; // 影が見える最大の高さ
constexpr float SHADOW_A_LEVEL = 0.8f; // 影の影の最大のアルファ値

//================================================
// コンストラクタ
//================================================
CEnemy::CEnemy()
{
	m_nLife = MAX_LIFE;
}

//================================================
// デストラクタ
//================================================
CEnemy::~CEnemy()
{
}

//================================================
// 初期化処理
//================================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// 位置の取得
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	// 影の生成
	m_pShadow = CShadow::Create(pos, SHADOW_WIDTH, SHADOW_HEIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f));

	return E_NOTIMPL;
}

//================================================
// 終了処理
//================================================
void CEnemy::Uninit(void)
{
	CObjectX::Uninit();
}

//================================================
// 更新処理
//================================================
void CEnemy::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 myPos = GetPosition();

	// 位置をずらす
	myPos += m_Move;

	// 位置を設定
	SetPosition(myPos);

	// 弾との当たり判定
	CEnemyManager::CollisionBullet();

	// 更新
	CObjectX::Update();

	if (m_pShadow != nullptr)
	{
		m_pShadow->Update(D3DXVECTOR3(myPos.x, 0.0f, myPos.z), D3DXVECTOR3(myPos.x, 0.0f, myPos.z), SHADOW_WIDTH, SHADOW_HEIGHT, SHADOW_MAX_HEIGHT, SHADOW_A_LEVEL);
	}

	// 死んだら破棄
	if (m_nLife <= 0)
	{
		// 自分をリストから外す
		CEnemyManager::Erase(this);

		if (m_pShadow != nullptr)
		{
			m_pShadow->Uninit();
		}
	}
}

//================================================
// 描画処理
//================================================
void CEnemy::Draw(void)
{
	if (m_pShadow != nullptr)
	{
		m_pShadow->Draw();
	}

	CObjectX::Draw();
}