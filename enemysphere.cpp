//================================================
//
// 球敵 [enemysphere.cpp]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "player.h"
#include "game.h"
#include "manager.h"
#include "enemysphere.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "enemymanager.h"

//================================================
// コンストラクタ
//================================================
CEnemySphere::CEnemySphere() : CEnemy(TYPE_ONE)
{
}

//================================================
// デストラクタ
//================================================
CEnemySphere::~CEnemySphere()
{
}

//================================================
// 初期化処理
//================================================
HRESULT CEnemySphere::Init(void)
{
	// 初期化処理
	CEnemy::Init();

	// 正常終了
	return S_OK;
}

//================================================
// 終了処理
//================================================
void CEnemySphere::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//================================================
// 更新処理
//================================================
void CEnemySphere::Update(void)
{
	// シーンがゲーム以外なら早期リターン
	if (CManager::GetMode() != CScene::MODE_GAME) return;
	// プレイヤーが生成されていなかったら早期リターン
	if (CGame::GetPlayer() == NULL) return;

	// プレイヤーまでのベクトルを引く
	D3DXVECTOR3 pVec = CGame::GetPlayer()->GetModelPos(1) - GetPosition();

	// 正規化
	D3DXVec3Normalize(&pVec, &pVec);

	// スピードをかける
	pVec *= 2.0f;
	pVec.y = 0.0f;

	// 設定
	SetMove(pVec);

	// 更新処理
	CEnemy::Update();
}

//================================================
// 描画処理
//================================================
void CEnemySphere::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//================================================
// 生成
//================================================
CEnemySphere* CEnemySphere::Create(D3DXVECTOR3 Pos)
{
	// メモリ確保するためのインスタンスを宣言
	CEnemySphere* Instance = nullptr;

	// 3Dオブジェクトの生成
	Instance = new CEnemySphere;

	// インスタンスが生成できなかったら
	if (Instance == nullptr) return nullptr;

	// 初期化処理
	Instance->Init();
	Instance->SetPosition(Pos);

	// モデルを読み込む
	Instance->LoadModel("enemy_blue.x");

	// インスタンスを返す
	return Instance;
}