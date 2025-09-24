//===================================================
//
// ビルボードを描画するクラス [billboard.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// 多重インクルード防止
//***************************************************
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//***************************************************
// インクルードファイル
//***************************************************
#include"object.h"

//***************************************************
// ビルボードクラスの定義
//***************************************************
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 7);
	virtual ~CObjectBillboard();

	static CObjectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pTextureName);

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	/**
	* @brief ワールドマトリックスの設定処理
	* @param 回転行列
	* @param 位置行列
	*/
	void SetMatrix(const D3DXMATRIX mtxRot, const D3DXMATRIX mtxTrans);

	/**
	* @brief 描画の部分だけの処理
	* SetUpDrawの次に呼ぶ
	*/
	void SetUpDraw(void);

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR2 GetSize(void) const { return m_Size; }
	
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR2 size) { m_Size = size; }

	void SetColor(const D3DXCOLOR col);
	void SetTextureID(const char* pTextureName);
	void UpdateVertexPos(const D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// 頂点へのポインタ
	D3DXVECTOR3 m_pos;						// 位置のクラスのポインタ
	D3DXVECTOR2 m_Size;						// 大きさ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	int m_nTextureIdx;						// テクスチャのインデックス
};
#endif