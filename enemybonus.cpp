//===================================================
//
// ボーナス敵 [enemybonus.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// インクルード
#include "enemybonus.h"
#include "player.h"
#include "game.h"
#include "manager.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "enemymanager.h"

//===================================================
// コンストラクタ
//===================================================
CEnemyBonus::CEnemyBonus() : CEnemy(TYPE_ONE)
{
}

//===================================================
// デストラクタ
//===================================================
CEnemyBonus::~CEnemyBonus()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CEnemyBonus::Init(void)
{
	// 初期化処理
	CEnemy::Init();

	// 正常終了
	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CEnemyBonus::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//===================================================
// 更新処理
//===================================================
void CEnemyBonus::Update(void)
{
	// シーンがゲーム以外なら早期リターン
	if (CManager::GetMode() != CScene::MODE_GAME) return;

	// プレイヤーが生成されていなかったら早期リターン
	if (CGame::GetPlayer() == NULL) return;

	// プレイヤーまでのベクトルを引く
	D3DXVECTOR3 pVec = CGame::GetPlayer()->GetModelPos(1) - GetPosition();

	float Speed = 2.0f;

	if (D3DXVec3Length(&pVec) < 300.0f)
	{
		Speed = 0.0f;
	}
	if (D3DXVec3Length(&pVec) > 0.0f)
	{
		Speed = -2.0f;
	}

	// 正規化
	D3DXVec3Normalize(&pVec, &pVec);

	// スピードをかける
	pVec *= Speed;
	pVec.y = 0.0f;

	// 設定
	SetMove(pVec);

	// 更新処理
	CEnemy::Update();
}

//===================================================
// 描画処理
//===================================================
void CEnemyBonus::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//===================================================
// 生成
//===================================================
CEnemyBonus* CEnemyBonus::Create(D3DXVECTOR3 Pos)
{
	// メモリ確保するためのインスタンスを宣言
	CEnemyBonus* Instance = nullptr;

	// 3Dオブジェクトの生成
	Instance = new CEnemyBonus;

	// インスタンスが生成できなかったら
	if (Instance == nullptr) return nullptr;

	// 初期化処理
	Instance->Init();
	Instance->SetPosition(Pos);

	// モデルを読み込む
	Instance->LoadModel("enemy_score.x");

	// インスタンスを返す
	return Instance;
}