//================================================
//
// プレイヤークラス [player.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// インクルードファイル
//*************************************************
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "bullet.h"

//*************************************************
// 名前空間
//*************************************************
using namespace Const; // 名前空間Constの使用

//*************************************************
// 定数宣言
//*************************************************
const D3DXVECTOR3 SHADOW_SCAL = { 1.0f,1.0f,1.0f };		// 影のモデルの拡大率
const D3DXVECTOR3 PLAYER_SIZE = { 10.0f,100.0f,10.0f };	// プレイヤーの大きさ
constexpr float INERTIA = 0.25f;						// 移動慣性

//=================================================
// コンストラクタ
//=================================================
CPlayer::CPlayer()
{
	m_move = VEC3_NULL;
}

//=================================================
// デストラクタ
//=================================================
CPlayer::~CPlayer()
{
}

//=================================================
// 生成処理
//=================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const float fAngle)
{
	CPlayer* pPlayer = new CPlayer;

	pPlayer->SetPosition(pos);
	pPlayer->SetRotation(D3DXVECTOR3(0.0f, fAngle, 0.0f));

	// 初期化処理
	if (FAILED(pPlayer->Init()))
	{
		pPlayer->Uninit();
		pPlayer = nullptr;
		return nullptr;
	}

	return pPlayer;
}

//=================================================
// 初期化処理
//=================================================
HRESULT CPlayer::Init(void)
{
	// 初期化処理
	if (FAILED(CCharacter3D::Init()))
	{
		return E_FAIL;
	}

	// キャラクターの設定
	CCharacter3D::SetCharacter(10, 5.0f, SHADOW_SCAL, PLAYER_SIZE);

	// モーションの読み込み
	CCharacter3D::LoadMotion("player.txt", MOTIONTYPE_MAX);

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CPlayer::Uninit(void)
{
	// 終了処理
	CCharacter3D::Uninit();
}

//=================================================
// 更新処理
//=================================================
void CPlayer::Update(void)
{
	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	// 位置の取得
	D3DXVECTOR3 pos = CCharacter3D::GetPosition();

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * INERTIA;
	m_move.z += (0.0f - m_move.z) * INERTIA;

	// 移動量の更新
	pos += m_move;

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// 角度の取得
	float fRotY = CCharacter3D::GetRotation().y;

	// モーションの更新処理
	CCharacter3D::UpdateMotion();

	// 更新処理
	CCharacter3D::Update();


	if (pCamera != nullptr)
	{
		// カメラの追従
		pCamera->SetTracking(pos, pos, 0.1f);
	}

	if (pKeyboard->GetTrigger(DIK_1))
	{
		CBullet::Create(VEC3_NULL, D3DXVECTOR3(0.0f, fRotY, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2.0f);
	}
}

//=================================================
// 描画処理
//=================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter3D::Draw();
}
