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

	if (pKeyboard->GetTrigger(DIK_1))
	{
		CBullet::Create(VEC3_NULL, D3DXVECTOR3(0.0f, fRotY, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2.0f);
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
