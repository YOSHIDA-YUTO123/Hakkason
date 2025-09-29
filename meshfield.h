//================================================
//
// メッシュフィールド [meshfield.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//************************************************
// インクルードファイル
//************************************************
#include "object.h"
#include <string>

//************************************************
// メッシュフィールドクラスの定義
//************************************************
class CMeshField : public CObject
{
public:
	CMeshField(int nPriority = 2);
	~CMeshField();

	static CMeshField* Create(const D3DXVECTOR3 pos,const int nSegH,const int nSegV,const D3DXVECTOR2 Size, const D3DXVECTOR3 rot = Const::VEC3_NULL);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetTextureID(const char* pTexturePath);
	bool Collision(const D3DXVECTOR3 pos, float* pOutHeight); // 地面との当たり判定

	void UpdateNor(void); // 法線の再設定
	
	// ゲッター
	D3DXVECTOR3 GetNor(void) const { return m_Nor; }
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffer;	// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR2 m_Size;						// 大きさ
	D3DXVECTOR3 m_Nor;						// 法線
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	std::string m_TexturePath;				// テクスチャのパス
	int m_nSegH, m_nSegV;					// 横の分割数、縦の分割数
	int m_nNumVtx;							// 頂点の数
	int m_nNumPolygon;						// ポリゴンの数
	int m_nNumIdx;							// インデックス数
};

#endif