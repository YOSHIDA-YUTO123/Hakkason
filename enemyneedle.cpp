//================================================
//
// 棘敵 [enemyneedle.cpp]
// Author: KENSAKU HATORI
//
//================================================

// インクルード
#include "enemyneedle.h"
#include "player.h"
#include "game.h"
#include "manager.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "enemymanager.h"

//================================================
// コンストラクタ
//================================================
CEnemyNeedle::CEnemyNeedle()
{
}

//================================================
// デストラクタ
//================================================
CEnemyNeedle::~CEnemyNeedle()
{
}

//================================================
// 初期化処理
//================================================
HRESULT CEnemyNeedle::Init(void)
{
	// 初期化処理
	CEnemy::Init();

	// 正常終了
	return S_OK;
}

//================================================
// 終了処理
//================================================
void CEnemyNeedle::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//================================================
// 更新処理
//================================================
void CEnemyNeedle::Update(void)
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
	pVec *= 3.0f;

	// 設定
	SetMove(pVec);
	pVec.y = 0.0f;

	// 更新処理
	CEnemy::Update();
}

//================================================
// 描画処理
//================================================
void CEnemyNeedle::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//================================================
// 生成
//================================================
CEnemyNeedle* CEnemyNeedle::Create(D3DXVECTOR3 Pos)
{
	// メモリ確保するためのインスタンスを宣言
	CEnemyNeedle* Instance = nullptr;

	// 3Dオブジェクトの生成
	Instance = new CEnemyNeedle;

	// インスタンスが生成できなかったら
	if (Instance == nullptr) return nullptr;

	// 初期化処理
	Instance->Init();
	Instance->SetPosition(Pos);

	// モデルを読み込む
	Instance->LoadModel("enemy_purple.x");

	// インスタンスを返す
	return Instance;
}