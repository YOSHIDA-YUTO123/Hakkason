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

	static CDualUnitTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	CTimer* m_pMinute; // タイマークラスへのポインタ(分)
	int m_nCounter;					       // カウンター
};

#endif
