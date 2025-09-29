//================================================
//
// メッシュシリンダーの描画 [MeshCylinder.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// 多重インクルード防止
//*************************************************
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//************************************************
// インクルードファイル
//************************************************
#include "object.h"
#include <string>

//************************************************
// メッシュシリンダーのクラスの定義
//************************************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(const int nPriority = 2);
	~CMeshCylinder();

	static CMeshCylinder* Create(const D3DXVECTOR3 pos, const float fRadius, const float fHeight, const int nSegH, const int nSegV);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetTextureID(const char* pTexturePath);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffer;	// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	std::string m_TexturePath;				// テクスチャのパス
	float m_fRadius;						// 半径
	float m_fHeight;						// 高さ
	int m_nSegH, m_nSegV;					// 横の分割数、縦の分割数
	int m_nNumVtx;							// 頂点の数
	int m_nNumPolygon;						// ポリゴンの数
	int m_nNumIdx;							// インデックス数
};

#endif
