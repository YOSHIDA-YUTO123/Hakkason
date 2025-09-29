//================================================
//
// メッシュシリンダーの描画 [MeshCylinder.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// インクルードファイル
//************************************************
#include "MeshCylinder.h"
#include "manager.h"
#include "renderer.h"
#include "texmanager.h"
using namespace std;

using namespace Const; // 名前空間Constの使用

//================================================
// コンストラクタ
//================================================
CMeshCylinder::CMeshCylinder(const int nPriority) : CObject(nPriority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pIdxBuffer = nullptr;
	m_pVtxBuffer = nullptr;
	m_fHeight = NULL;
	m_fRadius = NULL;
	m_nNumIdx = NULL;
	m_nNumPolygon = NULL;
	m_nNumVtx = NULL;
	m_nSegH = 1;
	m_nSegV = 1;
	m_rot = VEC3_NULL;
	m_pos = VEC3_NULL;
}

//================================================
// デストラクタ
//================================================
CMeshCylinder::~CMeshCylinder()
{
}

//================================================
// シリンダーの生成処理
//================================================
CMeshCylinder* CMeshCylinder::Create(const D3DXVECTOR3 pos, const float fRadius, const float fHeight, const int nSegH, const int nSegV)
{
	// メッシュフィールドを生成
	CMeshCylinder* pCylinder = new CMeshCylinder;

	if (pCylinder == nullptr) return nullptr;

	// 頂点数の設定
	pCylinder->m_nNumVtx = (nSegH + 1) * (nSegV + 1);

	// ポリゴン数の設定
	pCylinder->m_nNumPolygon = ((nSegH * nSegV) * 2) + (4 * (nSegV - 1));

	// インデックス数の設定
	pCylinder->m_nNumIdx = pCylinder->m_nNumPolygon + 2;

	pCylinder->m_pos = pos;
	pCylinder->m_fRadius = fRadius;
	pCylinder->m_fHeight = fHeight;
	pCylinder->m_nSegH = nSegH;
	pCylinder->m_nSegV = nSegV;

	// 初期化処理
	if (FAILED(pCylinder->Init()))
	{
		pCylinder->Uninit();

		// nullにする
		pCylinder = nullptr;

		return nullptr;
	}

	return pCylinder;
}

//================================================
// 初期化処理
//================================================
HRESULT CMeshCylinder::Init(void)
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

	int nCntVtx = 0;

	float fTexPosX = 1.0f / m_nSegH;
	float fTexPosY = 1.0f / m_nSegV;

	D3DXVECTOR3 posWk;

	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV <= m_nSegV; nCntV++)
	{
		for (int nCntH = 0; nCntH <= m_nSegH; nCntH++)
		{
			// 角度の割合を求める
			float fAngle = (D3DX_PI * 2.0f) / m_nSegH * nCntH;

			// 位置の設定
			posWk.x = sinf(fAngle) * m_fRadius;
			posWk.y = m_fHeight - (m_fHeight / m_nSegV * nCntV);
			posWk.z = cosf(fAngle) * m_fRadius;

			// 位置の設定
			pVtx[nCntVtx].pos = posWk;

			D3DXVECTOR3 nor = pVtx[nCntVtx].pos - m_pos;
			D3DXVec3Normalize(&nor, &nor);

			// 法線ベクトルの設定
			pVtx[nCntVtx].nor = nor;
		
			//頂点カラーの設定
			pVtx[nCntVtx].col = WHITE;

			//テクスチャ座標の設定
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexPosX * nCntH, fTexPosY * nCntV);

			nCntVtx++;
		}
	}

	// 頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

	int IndxNum = m_nSegH + 1;//X

	int IdxCnt = 0;//配列

	int Num = 0;//

	WORD* pIdx = nullptr;

	//インデックスバッファのロック
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < m_nSegV; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= m_nSegH; IndxCount2++, IndxNum++, Num++)
		{
			// インデックスバッファの設定
			pIdx[IdxCnt] = static_cast<WORD>(IndxNum);
			pIdx[IdxCnt + 1] = static_cast<WORD>(Num);
			IdxCnt += 2;
		}

		// NOTE:最後の行じゃなかったら
		if (IndxCount1 < m_nSegV - 1)
		{
			pIdx[IdxCnt] = static_cast<WORD>(Num - 1);
			pIdx[IdxCnt + 1] = static_cast<WORD>(IndxNum);
			IdxCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuffer->Unlock();

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CMeshCylinder::Uninit(void)
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
void CMeshCylinder::Update(void)
{
}

//================================================
// 描画処理
//================================================
void CMeshCylinder::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
}

//================================================
// テクスチャのIDの設定
//================================================
void CMeshCylinder::SetTextureID(const char* pTexturePath)
{
	// 省略用パス
	string filePath = "data/TEXTURE/";

	// 文字列の連結
	filePath += pTexturePath;

	m_TexturePath = filePath;
}
