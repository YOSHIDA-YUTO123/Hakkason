//===================================================
//
// モデルの描画をするクラス [model.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "model.h"
#include "object.h"
#include "modelManager.h"
#include "manager.h"
#include"renderer.h"
#include<stdio.h>
#include"texmanager.h"

using namespace Const;		   // 名前空間Constを使用する

//===================================================
// 定数宣言
//===================================================
constexpr int MAX_TEXTURE = 2; // テクスチャの最大数

//===================================================
// コンストラクタ
//===================================================
CModel::CModel()
{
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
	m_offpos = VEC3_NULL;
	m_offrot = VEC3_NULL;
	m_pParent = nullptr;
	m_Size = VEC3_NULL;
	m_nParentIdx = -1;
}

//===================================================
// デストラクタ
//===================================================
CModel::~CModel()
{
}

//===================================================
// 初期化処理
//===================================================
HRESULT CModel::Init(const char* pModelName)
{
	// マップのオブジェクトの取得
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// 取得できなかったら処理しない
	if (pMapObject == nullptr)
	{
		return E_FAIL;
	}
	
	// モデルの名前の設定
	m_aModelName = pModelName;

	// 大きさの取得
	m_Size = pMapObject->modelinfo.Size;

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CModel::Uninit(void)
{

}

//===================================================
// 更新処理
//===================================================
void CModel::Update(void)
{
}

//===================================================
// 描画処理
//===================================================
void CModel::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScal,mtxParent;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offpos.x, m_pos.y + m_offpos.y, m_pos.z + m_offpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{ // 親が存在している
		// 親モデルのマトリックスの取得
		mtxParent = m_pParent->GetMatrixWorld();
	}
	else
	{
		// ワールドマトリックスの取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親のワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// モデルの情報の取得
	CModelManager::MapObject *pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// 取得できなかったら処理しない
	if (pMapObject == nullptr)
	{
		//保存していたマテリアルを元に戻す
		pDevice->SetMaterial(&matDef);

		return;
	}

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, CLoadTexture::GetTex(m_aTexturePath));

		//モデル(パーツ)の描画
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================
// 描画処理(透明度設定)
//===================================================
void CModel::Draw(const float fAlv)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScal, mtxParent;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offpos.x, m_pos.y + m_offpos.y, m_pos.z + m_offpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{ // 親が存在している
		// 親モデルのマトリックスの取得
		mtxParent = m_pParent->GetMatrixWorld();
	}
	else
	{
		// ワールドマトリックスの取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親のワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// モデルの情報の取得
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// 取得できなかったら処理しない
	if (pMapObject == nullptr)
	{
		//保存していたマテリアルを元に戻す
		pDevice->SetMaterial(&matDef);

		return;
	}

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		// マテリアルの取得
		D3DXMATERIAL Mat = pMat[nCntMat];

		// 透明度の設定
		Mat.MatD3D.Diffuse.a = fAlv;

		//マテリアルの設定
		pDevice->SetMaterial(&Mat.MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, CLoadTexture::GetTex(m_aTexturePath));

		//モデル(パーツ)の描画
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================
// 影の描画処理
//===================================================
void CModel::DrawShadow(void)
{
	// レンダラーの取得
	CRenderer* pRenderer = CManager::GetRenderer();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ライトの方向
	D3DXVECTOR4 lightDir = D3DXVECTOR4(-0.707f, -0.707f, -0.707f, 0.0f);

	// 影を落とす地面
	D3DXPLANE plane = D3DXPLANE(0, -1.0f, 0, 0);

	// 影用のマトリックスを作成
	D3DXMATRIX mtxShadow, mtxShadowWorld;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	// 影用のマトリックスの作成
	D3DXMatrixShadow(&mtxShadow, &lightDir, &plane);

	// 影のマトリックスと自分のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&mtxShadowWorld, &m_mtxWorld, &mtxShadow);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadowWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// 半透明の黒マテリアルをセット
	D3DMATERIAL9 matShadow = {};

	// 影の色の設定
	matShadow.Diffuse.r = 0.0f;
	matShadow.Diffuse.g = 0.0f;
	matShadow.Diffuse.b = 0.0f;
	matShadow.Diffuse.a = 1.0f;

	// モデルの情報の取得
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// 取得できなかったら処理しない
	if (pMapObject == nullptr)
	{
		//保存していたマテリアルを元に戻す
		pDevice->SetMaterial(&matDef);

		return;
	}

	// 影の描画
	for (int nCntMat = 0; nCntMat < (int)pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		// 影のマテリアルの設定
		pDevice->SetMaterial(&matShadow);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// 影の描画
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	// マテリアルをもとに戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================
// 親の設定
//===================================================
void CModel::SetParent(CModel* pModel, const int nIdx)
{
	m_pParent = pModel;
	m_nParentIdx = nIdx;
}

//===================================================
// 情報のコピー
//===================================================
void CModel::Copy(CModel* pModel)
{
	pModel->m_offpos = m_offpos;	// 基準の位置
	pModel->m_offrot = m_offrot;	// 基準の向き
}

//===================================================
// 生成処理
//===================================================
CModel* CModel::Create(const char *pModelName)
{
	CModel* pModel = nullptr;

	// モデルの生成
	pModel = new CModel;

	if (pModel == nullptr) return nullptr;

	pModel->Init(pModelName);

	return pModel;
}
