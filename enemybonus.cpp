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
#include "effect3d.h"
#include "particle3d.h"

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

	m_nTimer++;

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

	// 火の情報を設定
	CParticle3D::DefoultEffectInfo FireInfo;
	FireInfo.Bece.Col = { 1.0f,0.89f,0.0f,1.0f };
	FireInfo.Bece.fMaxSpeed = 1.0f;
	FireInfo.Bece.fMinSpeed = 1.0f;
	FireInfo.Bece.MaxDir = { 0.1f,0.5f,0.1f };
	FireInfo.Bece.MinDir = { -0.1f,0.5f,-0.1f };
	FireInfo.Bece.nLife = 1;
	FireInfo.Bece.nMaxLife = 30;
	FireInfo.Bece.nMinLife = 30;
	FireInfo.Bece.nNumEffect = 1;
	FireInfo.Bece.Pos = { GetPosition().x,GetPosition().y ,GetPosition().z };
	FireInfo.MaxRadius = 3.8f;
	FireInfo.MinRadius = 2.8f;
	FireInfo.Bece.bLoop = false;
	FireInfo.Bece.nCoolDown = 2;
	FireInfo.Bece.Gravity = 0.03f;
	FireInfo.Bece.FilePath = CEffect3D::Config::Sphere;
	FireInfo.Bece.nPriority = 5;

	// 生成
	CParticle3D::Create(FireInfo);

	// 更新処理
	CEnemy::Update();

	if (m_nTimer > 300)
	{
		CEnemyManager::Erase(this);
	}
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