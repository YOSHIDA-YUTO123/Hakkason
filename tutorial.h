//****************************************************************
//
// チュートリアルの処理[tutorial.h]
// Author Kensaku Hatori
//
//****************************************************************

// 二重インクルード防止
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// インクルード
#include "scene.h"

// 前方宣言
class CPlayer;
class CMapEditer;
class CPauseManager;

// チュートリアルクラスを定義
class CTutorial : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CTutorial();
	~CTutorial();

	// オーバーライドされたメンバ関数
	HRESULT Init(void)	override;
	void Update(void)	override;
	void Uninit(void)	override;
	void Draw(void)		override;
private:
};
#endif // !_TUTORIAL_H_