//================================================
//
// プレイヤークラス [player.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*************************************************
// インクルードファイル
//*************************************************
#include "character3D.h"

//*************************************************
// 前方宣言
//*************************************************
class CInputKeyboard;
class CMotion;
class CInputJoypad;
class CCamera;

//*************************************************
// プレイヤークラスの定義
//*************************************************
class CPlayer : public CCharacter3D
{
public:

	// プレイヤーのモデル
	typedef enum
	{
		MODEL_BODY = 0, // 胸
		MODEL_HEAD,		// 頭
		MODEL_ARMR,		// 右腕
		MODEL_HANDR,	// 右手
		MODEL_ARML,		// 左腕
		MODEL_HANDL,	// 左手
		MODEL_LEGR,		// 右太もも
		MODEL_FOOTR,	// 右足
		MODEL_LEGL,		// 左太もも
		MODEL_FOOTL,	// 左足
		MODEL_SHOTGUN,	// 銃
		MODEL_MAX
	}MODEL;
	// モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, // ニュートラル
		MOTIONTYPE_MOVE,		// 移動
		MOTIONTYPE_ACTION,		// 攻撃
		MOTIONTYPE_JUMP,		// ジャンプ
		MOTIONTYPE_LANDING,		// 着地モーション
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	CPlayer();
	~CPlayer();

	static CPlayer* Create(const D3DXVECTOR3 pos, const float fAngle);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	void Debug(CInputKeyboard* pKeyboard);
	bool MoveKeyboard(CInputKeyboard* pKeyboard, CCamera* pCamera);
	bool MoveJoyPad(CInputJoypad* pJoypad, CCamera* pCamera);
	void UpdateShotBullet(CMotion* pMotion, CInputKeyboard* pKeyboard, CInputJoypad* pJoypad, const float fAngleY);

	D3DXVECTOR3 m_move;		// 移動量
	D3DXMATRIX m_ShotMtx;	// 発射地点のマトリックス
	int m_nCoolDown;		// 発射のクールダウン
};

#endif