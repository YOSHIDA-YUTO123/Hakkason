//================================================
//
// 弾 [bullet.cpp]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "bullet.h"
#include "bulletmanager.h"
#include "shadow.h"

// 定数宣言
constexpr float SHADOW_WIDTH = 10.0f;  // 影の横幅
constexpr float SHADOW_HEIGHT = 10.0f; // 影の縦幅
constexpr float SHADOW_MAX_HEIGHT = 250.0f; // 影が見える最大の高さ
constexpr float SHADOW_A_LEVEL = 0.8f; // 影の影の最大のアルファ値

//================================================
// コンストラクタ
//================================================
CBullet::CBullet()
{
	m_pShadow = nullptr;
	m_nLife = NULL;
}

//================================================
// デストラクタ
//================================================
CBullet::~CBullet()
{
}

//================================================
// 初期化処理
//================================================
HRESULT CBullet::Init(void)
{
	// 初期化処理
	CObjectX::Init();

	// 位置の取得
	D3DXVECTOR3 pos = CObjectX::GetPosition();

	// 影の生成
	m_pShadow = CShadow::Create(pos, SHADOW_WIDTH, SHADOW_HEIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f));

	// 正常終了
	return S_OK;
}

//================================================
// 更新処理
//================================================
void CBullet::Update(void)
{
	// 位置を取得
	D3DXVECTOR3 myPos = GetPosition();

	// 位置をずらす
	myPos += m_Move;

	// 設定
	SetPosition(myPos);

	// 更新処理
	CObjectX::Update();

	if (m_pShadow != nullptr)
	{
		m_pShadow->Update(D3DXVECTOR3(myPos.x, 0.0f, myPos.z), D3DXVECTOR3(myPos.x, 0.0f, myPos.z), SHADOW_WIDTH, SHADOW_HEIGHT, SHADOW_MAX_HEIGHT, SHADOW_A_LEVEL);
	}
	m_nLife--;

	// 寿命が尽きたら破棄
	if (m_nLife <= 0)
	{
		// 自分の破棄
		CBulletManager::Erase(this);

		if(m_pShadow != nullptr)
		{
			// 影の破棄
			m_pShadow->Uninit();
		}
	}
}

//================================================
// 終了処理
//================================================
void CBullet::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//================================================
// 描画処理
//================================================
void CBullet::Draw(void)
{
	if (m_pShadow != nullptr)
	{
		// 描画
		m_pShadow->Draw();
	}
	// 描画処理
	CObjectX::Draw();
}

//================================================
// 生成処理
//================================================
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed, const int nLife)
{
	// メモリ確保するためのインスタンスを宣言
	CBullet* Instance = nullptr;

	// 3Dオブジェクトの生成
	Instance = new CBullet;

	// インスタンスが生成できなかったら
	if (Instance == nullptr) return nullptr;

	Instance->SetPosition(Pos);
	Instance->SetRotation(Rot);

	// 初期化処理
	Instance->Init();
	Instance->m_Move = Dir * Speed;
	Instance->m_nLife = nLife;

	// モデルを読み込む
	Instance->LoadModel("shotgun_ammo.x");

	// インスタンスを返す
	return Instance;
}