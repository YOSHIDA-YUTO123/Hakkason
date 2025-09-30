//===================================================
//
// ゲームシーン [game.h]
// Author:YUTO YOSHIDA
//
//===================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _GAME_H_
#define _GAME_H_

//***************************************************
// インクルードファイル
//***************************************************
#include"main.h"
#include "scene.h"
#include<memory>
#include<string>

//***************************************************
// 前方宣言
//***************************************************
class CMeshField;
class CPlayer;
class CMeshCylinder;
class CPauseManager;
class CGameCamera;
class CLoadManager;
class CEnemy;
class CPlayer;
class CDualUnitTimer;

//***************************************************
// ゲームクラスの定義
//***************************************************
class CGame : public CScene
{
public:

	// ゲームの状態
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_ENEMY_DEATH,
		STATE_END,
		STATE_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	static void SetState(const STATE state) { m_state = state; }
	// ゲッター
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static STATE GetState(void) { return m_state; }
private:
	static CPlayer* m_pPlayer;			// プレイヤーのインスタンス
	static CDualUnitTimer* m_pTimer;	// タイマーのインスタンス
	static STATE m_state;				// ゲームの状態
	int m_nScore;				// スコア
	int m_nCounterState;				// 状態カウンター
};

#endif

