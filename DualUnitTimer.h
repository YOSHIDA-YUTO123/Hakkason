//================================================
//
// 分と秒を扱うタイマーのクラスの処理 [DualUnitTimer.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _DUALUNITTER_H_
#define _DUALUNITTER_H_

//*************************************************
// インクルードファイル
//*************************************************
#include "timer.h"

//*************************************************
// 分と秒のタイマーのクラスの定義
//*************************************************
class CDualUnitTimer : public CTimer
{
public:
	CDualUnitTimer();
	~CDualUnitTimer();

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="位置"></param>
	/// <param name="大きさ"></param>
	/// <param name="時間"></param>
	/// <returns>自分のインスタンス</returns>
	static CDualUnitTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	int GetTimer(void) const { return m_nCurrentTime; }
private:
	CTimer* m_pMinute; // タイマークラスへのポインタ(分)
	int m_nCurrentTime;// 現在の時間
	int m_nCounter;	   // カウンター
};

#endif
