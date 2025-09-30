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
#include "motion.h"
#include "debugproc.h"
#include "renderer.h"
#include "math.h"
#include "bulletmanager.h"

//*************************************************
// 名前空間
//*************************************************
using namespace Const; // 名前空間Constの使用
using namespace math;  // 名前空間mathの使用

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
	D3DXMatrixIdentity(&m_ShotMtx);

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
	CCharacter3D::SetCharacter(10, 1.5f, SHADOW_SCAL, PLAYER_SIZE);

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

	// キーボードの取得
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// モーションの取得
	CMotion* pMotion = CCharacter3D::GetMotion();

	// モーションが取得できなかったら処理しない
	if (pMotion == nullptr) return;

	// ロードに失敗していたら処理しない
	if (!pMotion->IsLoad()) return;
	
	// モーションの種類の取得
	int nMotionType = pMotion->GetBlendType();

	// キーボードの移動
	if (MoveKeyboard(pKeyboard, pCamera))
	{
		// 移動モーションにする
		pMotion->SetMotion(MOTIONTYPE_MOVE, true, 10);
	}
	else if(nMotionType == MOTIONTYPE_MOVE)
	{
		// ニュートラルモーションにする
		pMotion->SetMotion(MOTIONTYPE_NEUTRAL, true, 10);
	}

	// 移動量の減衰
	m_move.x += (0.0f - m_move.x) * INERTIA;
	m_move.z += (0.0f - m_move.z) * INERTIA;

	// 移動量の更新
	pos += m_move;

	// 角度の取得
	float fRotY = CCharacter3D::GetRotation().y;

	if (pKeyboard->GetRepeat(DIK_RETURN,30))
	{
		// 発射地点の取得
		D3DXVECTOR3 shotGunPos = GetPositionFromMatrix(m_ShotMtx);

		// 弾の発射
		CBulletManager::PushBackBullet(shotGunPos, VEC3_NULL,
			D3DXVECTOR3(sinf(fRotY + D3DX_PI), 0.0f, cosf(fRotY + D3DX_PI)), 10.0f);

		pMotion->SetMotion(MOTIONTYPE_ACTION, true, 10);
	}
	// モーションの更新処理
	CCharacter3D::UpdateMotion();

	// 更新処理
	CCharacter3D::Update();

	// 位置の設定
	CCharacter3D::SetPosition(pos);

	if (pCamera != nullptr)
	{
		// カメラの追従
		pCamera->SetTracking(pos, pos, 0.1f);
	}

#ifdef _DEBUG

	// デバッグ情報
	Debug(pKeyboard);
#endif // _DEBUG

}

//=================================================
// 描画処理
//=================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter3D::Draw();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_ShotMtx);

	// 親の位置、向きの設定
	D3DXVECTOR3 ParentRot = CCharacter3D::GetModelRot(MODEL_SHOTGUN);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, ParentRot.y, ParentRot.x, ParentRot.z);
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxRot);

	// 大きさの取得
	D3DXVECTOR3 ParentSize = CCharacter3D::GetModelSize(MODEL_SHOTGUN);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, ParentSize.x * 0.5f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxTrans);

	// 親のマトリックスの取得
	mtxParent = CCharacter3D::GetParent(MODEL_SHOTGUN);

	// 親のワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_ShotMtx);
}

//=================================================
// デバッグ情報
//=================================================
void CPlayer::Debug(CInputKeyboard* pKeyboard)
{
#ifdef _DEBUG

	D3DXVECTOR3 pos = CCharacter3D::GetPosition();

	CDebugProc::Print("********************************************\n");
	CDebugProc::Print("              プレイヤー情報\n");
	CDebugProc::Print("********************************************\n");
	CDebugProc::Print("プレイヤーの位置 = [ %.2f ] [ %.2f ] [ %.2f ]\n", pos.x, pos.y, pos.z);

	if (pKeyboard->GetTrigger(DIK_TAB))
	{

	}
#endif // _DEBUG

}

//=================================================
// キーボードの移動
//=================================================
bool CPlayer::MoveKeyboard(CInputKeyboard* pKeyboard, CCamera* pCamera)
{
	bool bMove = false;

	// 取得できなかったら処理しない
	if (pCamera == nullptr) return false;

	// 移動速度の取得
	float fSpeed = CCharacter3D::GetSpeed();

	// 現在の目的の角度の取得
	float fDestRotY = CCharacter3D::GetRotDest().y;

	// カメラの向き
	D3DXVECTOR3 cameraRot = pCamera->GetRotaition();

	// ジョイパッドの取得
	CInputJoypad* pJoyPad = CManager::GetInputJoypad();

	if (pJoyPad->GetJoyStickL())
	{
		return false;
	}

	if (pKeyboard->GetPress(DIK_A))
	{
		//プレイヤーの移動(上)
		if (pKeyboard->GetPress(DIK_W) == true)
		{
			m_move.x += sinf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;
			m_move.z += cosf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;

			// 目的の角度の設定
			fDestRotY = cameraRot.y + D3DX_PI * 0.75f;

			bMove = true;
		}
		//プレイヤーの移動(下)
		else if (pKeyboard->GetPress(DIK_S))
		{
			m_move.x += sinf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;
			m_move.z += cosf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;

			// 目的の角度の設定
			fDestRotY = cameraRot.y + D3DX_PI * 0.25f;

			bMove = true;
		}
		// プレイヤーの移動(左)
		else
		{
			m_move.z += sinf(cameraRot.y) * fSpeed;
			m_move.x -= cosf(cameraRot.y) * fSpeed;

			// 目的の角度の設定
			fDestRotY = cameraRot.y + D3DX_PI * 0.5f;

			bMove = true;
		}
	}
	//プレイヤーの移動(右)
	else if (pKeyboard->GetPress(DIK_D))
	{
		//プレイヤーの移動(上)
		if (pKeyboard->GetPress(DIK_W))
		{
			m_move.x += sinf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;
			m_move.z += cosf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;

			// 目的の角度の設定
			fDestRotY = cameraRot.y - D3DX_PI * 0.75f;

			bMove = true;
		}
		//プレイヤーの移動(下)
		else if (pKeyboard->GetPress(DIK_S))
		{
			m_move.x += sinf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;
			m_move.z += cosf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;

			// 目的の角度の設定
			fDestRotY = cameraRot.y - D3DX_PI * 0.25f;

			bMove = true;
		}
		// プレイヤーの移動(右)
		else
		{
			m_move.z -= sinf(cameraRot.y) * fSpeed;
			m_move.x += cosf(cameraRot.y) * fSpeed;

			fDestRotY = cameraRot.y - D3DX_PI * 0.5f;

			bMove = true;
		}
	}
	//プレイヤーの移動(上)
	else if (pKeyboard->GetPress(DIK_W) == true)
	{
		m_move.x += sinf(cameraRot.y) * fSpeed;
		m_move.z += cosf(cameraRot.y) * fSpeed;

		fDestRotY = cameraRot.y + D3DX_PI;

		bMove = true;
	}
	//プレイヤーの移動(下)
	else if (pKeyboard->GetPress(DIK_S) == true)
	{
		m_move.x -= sinf(cameraRot.y) * fSpeed;
		m_move.z -= cosf(cameraRot.y) * fSpeed;

		fDestRotY = cameraRot.y;

		bMove = true;
	}

	// 目的の角度の設定
	CCharacter3D::SetRotDest(D3DXVECTOR3(0.0f, fDestRotY, 0.0f));

	return bMove;
}
