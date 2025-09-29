//****************************************************************
//
// モデルを一括管理するクラスの処理[modelmanager.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// インクルード
#include "modelmanager.h"
#include "manager.h"
#include <cassert>
#include "renderer.h"
#include <fstream>
#include <sstream>

// 名前空間
using namespace std;
using namespace Const;

// 静的メンバ変数
unordered_map<std::string, CModelManager::MapObject> CModelManager::m_ModelMap = {};

//*********************************************
// コンストラクタ
//*********************************************
CModelManager::CModelManager()
{
}

//*********************************************
// モデルの大きさの設定処理
//*********************************************
void CModelManager::SetModelSize(MapObject* pMapObject)
{
	// 頂点座標の取得
	int nNumVtx;	// 頂点数
	DWORD sizeFVF;  // 頂点フォーマットのサイズ
	BYTE* pVtxBuff; // 頂点バッファへのポインタ

	// 頂点数の取得
	nNumVtx = pMapObject->modelinfo.pMesh->GetNumVertices();

	// 頂点フォーマットのサイズ取得
	sizeFVF = D3DXGetFVFVertexSize(pMapObject->modelinfo.pMesh->GetFVF());

	// 頂点バッファのロック
	pMapObject->modelinfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// 最小の頂点
	D3DXVECTOR3 vtxMin = VEC3_NULL;

	// 最大の頂点
	D3DXVECTOR3 vtxMax = VEC3_NULL;

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点座標を比較してブロックの最小値,最大値を取得
		if (vtx.x < vtxMin.x)
		{
			vtxMin.x = vtx.x;
		}
		if (vtx.y < vtxMin.y)
		{
			vtxMin.y = vtx.y;
		}
		if (vtx.z < vtxMin.z)
		{
			vtxMin.z = vtx.z;
		}
		if (vtx.x > vtxMax.x)
		{
			vtxMax.x = vtx.x;
		}
		if (vtx.y > vtxMax.y)
		{
			vtxMax.y = vtx.y;
		}
		if (vtx.z > vtxMax.z)
		{
			vtxMax.z = vtx.z;
		}

		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	// 大きさ
	D3DXVECTOR3 Size = VEC3_NULL;

	// サイズに代入
	pMapObject->modelinfo.Size.x = vtxMax.x - vtxMin.x;
	pMapObject->modelinfo.Size.y = vtxMax.y - vtxMin.y;
	pMapObject->modelinfo.Size.z = vtxMax.z - vtxMin.z;

	// 頂点バッファのアンロック
	pMapObject->modelinfo.pMesh->UnlockVertexBuffer();
}

//*********************************************
// デストラクタ
//*********************************************
CModelManager::~CModelManager()
{
}

//*********************************************
// ファイルを開く
//*********************************************
void CModelManager::Load(std::string LoadFilePath)
{
	// 省略用パス
	string txtFilePath = "data/TXT/";

	// 文字列の連結
	txtFilePath += LoadFilePath;

	ifstream ifs(txtFilePath.c_str());

	if (!ifs)
	{
		MessageBox(NULL, "ファイルが読み込めませんでした", txtFilePath.c_str(), MB_OK);
		return;
	}

	string line = {};
	string label = {}, equal = {};

	while (getline(ifs, line))
	{
		string FilePath;
		string Category;

		istringstream iss(line);
		if (line.find("MODELFILE_NAME") != string::npos)
		{
			iss >> label >> equal >> FilePath;
		}
		if (line.find("CATEGORY") != string::npos)
		{
			iss >> label >> equal >> Category;
		}

		if (FilePath[0] != NULL && Category[0] != NULL)
		{
			string filePath = "data/MODEL/";

			GetModelInfo(filePath += FilePath);
		}

		if (line.find("#") != string::npos)
		{
			continue;
		}
	}
}

//*********************************************
// モデルの情報を取得 & 追加
//*********************************************
CModelManager::MapObject* CModelManager::GetModelInfo(string Path)
{
	// すでに存在したらその情報を返す
	if (m_ModelMap.find(Path) != m_ModelMap.end()) return &m_ModelMap[Path];

	// 被りがなくてパスの長さが短かったらクリエイト
	CRenderer* pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// モデルの情報を読み込む一時変数
	MapObject LocalInfo = {};

	// Xファイル読込
	HRESULT hr;
	hr = D3DXLoadMeshFromX(
		Path.c_str(),
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&LocalInfo.modelinfo.pBuffMat,
		NULL,
		&LocalInfo.modelinfo.dwNumMat,
		&LocalInfo.modelinfo.pMesh
	);

	// 読み込めなかったら
	if (FAILED(hr))
	{
		// 失敗したら
		assert(0 && "モデルパスが間違っています");
	}

	//マテリアル辺のポインタを取得
	D3DXMATERIAL* pMat;
	pMat = (D3DXMATERIAL*)LocalInfo.modelinfo.pBuffMat->GetBufferPointer();

	// マテリアル分パスを確保
	LocalInfo.modelinfo.TexPath.resize(LocalInfo.modelinfo.dwNumMat);

	// マテリアルの数分回す
	for (int nCntMat = 0; nCntMat < (int)LocalInfo.modelinfo.dwNumMat; nCntMat++)
	{
		// パスが存在したら
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// 代入
			LocalInfo.modelinfo.TexPath[nCntMat] = pMat[nCntMat].pTextureFilename;
		}
	}

	// モデルの大きさの取得
	SetModelSize(&LocalInfo);

	// マップにVlueとして設定
	m_ModelMap[Path] = LocalInfo;

	// 情報を返す
	return &m_ModelMap[Path];
}

//*********************************************
// モデルの情報を取得
//*********************************************
CModelManager::MapObject* CModelManager::GetModelInfo(const int Indx)
{
	// 不正なインデックスならアサート
	if (Indx < 0 || Indx >= (int)m_ModelMap.size()) assert(0 && "存在しないモデルにアクセスしようとしています");

	// 配列でアクセスするためのイテレーター
	auto Map = m_ModelMap.begin();

	// 要素を進める
	std::advance(Map, Indx);

	// Vlueを返す
	return &Map->second;
}

//*********************************************
// いろいろ破棄
//*********************************************
void CModelManager::UnRegistModel(void)
{
	// マップの中にアクセス
	for (auto& Map : m_ModelMap)
	{
		// nullptrチェック
		if (Map.second.modelinfo.pMesh != nullptr)
		{
			// メモリ開放
			Map.second.modelinfo.pMesh->Release();

			// nullptrを代入する
			Map.second.modelinfo.pMesh = nullptr;
		}
		// nullptrチェック
		if (Map.second.modelinfo.pBuffMat != nullptr)
		{
			// メモリ開放
			Map.second.modelinfo.pBuffMat->Release();

			// nullptrを代入する
			Map.second.modelinfo.pBuffMat = nullptr;
		}
	}

	// マップ自体をクリア
	m_ModelMap.clear();
}