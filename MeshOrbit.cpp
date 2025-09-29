//================================================
//
// 軌跡の描画 [MeshOrbit.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// インクルードファイル
//************************************************
#include "MeshOrbit.h"
#include "manager.h"
#include "renderer.h"
#include "texmanager.h"
using namespace std;

using namespace Const;							// 名前空間Constを使用する

//================================================
// コンストラクタ
//================================================
CMeshOrbit::CMeshOrbit()
{
	m_col = WHITE;
	m_Bottom = VEC3_NULL;
	m_Top = VEC3_NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumIdx = NULL;
	m_nNumPolygon = NULL;
	m_nNumVtx = NULL;
	m_nSegH = 1;
	m_pos = VEC3_NULL;
	m_pIdxBuffer = nullptr;
	m_pVtxBuffer = nullptr;
}

//================================================
// デストラクタ
//================================================
CMeshOrbit::~CMeshOrbit()
{
}

//================================================
// 軌跡の生成
//================================================
CMeshOrbit* CMeshOrbit::Create(const D3DXVECTOR3 Top, const D3DXVECTOR3 Bottom, const int nSegH,const D3DXCOLOR col)
{
	// 軌跡を生成
	CMeshOrbit* pOrbit = new CMeshOrbit;

	// 縦の分割数
	const int nSegV = 1;

	// 頂点の総数
	pOrbit->m_nNumVtx = (nSegH + 1) * (nSegV + 1);

	// インデックスの総数
	pOrbit->m_nNumIdx = pOrbit->m_nNumVtx;

	pOrbit->m_Bottom = Bottom;
	pOrbit->m_Top = Top;
	pOrbit->m_nSegH = nSegH;
	pOrbit->m_col = col;

	// ポリゴンの総数
	pOrbit->m_nNumPolygon = pOrbit->m_nNumVtx - 2;

	// 生成に失敗した
	if (FAILED(pOrbit->Init()))
	{
		pOrbit->Uninit();

		pOrbit = nullptr;

		return nullptr;
	}

	return pOrbit;
}

//================================================
// 初期化処理
//================================================
HRESULT CMeshOrbit::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	//インデックスバッファの生成
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	// テクスチャ座(横)
	float fPosTexH = 1.0f / m_nSegH;

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	WORD* pIdx = nullptr;

	//インデックスバッファのロック
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	// 頂点数分回す
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		// アルファ値の設定
		float fAlv = m_col.a * (1.0f - (float)nCnt / m_nNumVtx);

		// 頂点の設定(いったん一か所に集める)
		pVtx[nCnt].pos = m_Top;

		// 法線、色、テクスチャの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, fAlv);
		pVtx[nCnt].tex = D3DXVECTOR2(fPosTexH * nCnt, 1.0f);

		// インデックスバッファの設定
		pIdx[nCnt] = (WORD)nCnt;
	}

	// 四個前から始める
	for (int nCnt = m_nNumVtx - 4; nCnt >= 0; nCnt -= 2)
	{
		// 前の頂点座標を入れる
		D3DXVECTOR3 OldVtx0 = pVtx[nCnt].pos;
		D3DXVECTOR3 OldVtx1 = pVtx[nCnt + 1].pos;

		pVtx[nCnt + 2].pos = OldVtx0;
		pVtx[nCnt + 3].pos = OldVtx1;
	}

	// 新しい頂点を追加（先頭に入れる）
	pVtx[0].pos = m_Bottom;
	pVtx[1].pos = m_Top;

	//インデックスバッファのアンロック
	m_pIdxBuffer->Unlock();

	// 頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CMeshOrbit::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuffer != nullptr)
	{
		m_pIdxBuffer->Release();
		m_pIdxBuffer = nullptr;
	}

	// 自分自身の破棄
	CObject::Release();
}

//================================================
// 更新処理
//================================================
void CMeshOrbit::Update(void)
{
	int nSegV = 1;			// 縦の分割数

	// 頂点の総数
	int nNumVtx = (m_nSegH + 1) * (nSegV + 1);

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 四個前から始める
	for (int nCnt = nNumVtx - 4; nCnt >= 0; nCnt -= 2)
	{
		// 前の頂点座標を入れる
		D3DXVECTOR3 OldVtx0 = pVtx[nCnt].pos;
		D3DXVECTOR3 OldVtx1 = pVtx[nCnt + 1].pos;

		pVtx[nCnt + 2].pos = OldVtx0;
		pVtx[nCnt + 3].pos = OldVtx1;
	}

	// 新しい頂点を追加
	pVtx[0].pos = m_Bottom;
	pVtx[1].pos = m_Top;

	// 頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}

//================================================
// 描画処理
//================================================
void CMeshOrbit::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カリングをオンにする
	pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

	// aブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuffer);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CLoadTexture::GetTex(m_TexturePath));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVtx, 0, m_nNumPolygon);

	// aブレンディングをもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// カリングをオフにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//================================================
// 位置の設定処理
//================================================
void CMeshOrbit::SetPosition(const D3DXVECTOR3 Top, const D3DXVECTOR3 Bottom)
{
	m_Top = Top;
	m_Bottom = Bottom;
}

//================================================
// テクスチャのIDの設定
//================================================
void CMeshOrbit::SetTextureID(const char* pTexturePath)
{
	// 省略用パス
	string filePath = "data/TEXTURE/";

	// 文字列の連結
	filePath += pTexturePath;

	m_TexturePath = filePath;
}
