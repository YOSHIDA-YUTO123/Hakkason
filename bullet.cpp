//================================================
//
// 弾 [bullet.cpp]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "bullet.h"

//================================================
// コンストラクタ
//================================================
CBullet::CBullet()
{
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
	// 描画処理
	CObjectX::Draw();
}

//================================================
// 生成処理
//================================================
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// メモリ確保するためのインスタンスを宣言
	CBullet* Instance = nullptr;

	// 3Dオブジェクトの生成
	Instance = new CBullet;

	// インスタンスが生成できなかったら
	if (Instance == nullptr) return nullptr;

	// 初期化処理
	Instance->Init();
	Instance->SetPosition(Pos);
	Instance->SetRotation(Rot);
	Instance->m_Move = Dir * Speed;

	// モデルを読み込む
	Instance->LoadModel("Test.x");

	// インスタンスを返す
	return Instance;
}