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
class CCamera;

//*************************************************
// プレイヤークラスの定義
//*************************************************
class CPlayer : public CCharacter3D
{
public:

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

	D3DXVECTOR3 m_move; // 移動量
};

#endif