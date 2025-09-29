//****************************************************************
//
// テクスチャを一括管理するクラスの処理[texmanager.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// インクルード
#include "texmanager.h"
#include "manager.h"
#include <string>
#include <fstream>
#include <sstream>
#include "renderer.h"
#include <assert.h>

// 名前空間
using namespace std;

// 静的メンバ変数宣言
unordered_map<string, LPDIRECT3DTEXTURE9> CLoadTexture::m_TexMap = {};

//*********************************************
// コンストラクタ
//*********************************************
CLoadTexture::CLoadTexture()
{
}

//*********************************************
// デストラクタ
//*********************************************
CLoadTexture::~CLoadTexture()
{
}

//*********************************************
// テクスチャを外部ファイルから読みこむ
//*********************************************
void CLoadTexture::Load(std::string LoadFilePath)
{
	// 省略用パス
	string LoadfilePath = "data/TXT/";

	// 文字列を連結する
	LoadfilePath += LoadFilePath;

	// ファイルを開く
	ifstream ifs(LoadfilePath.c_str());

	// 開けなかったら
	if (!ifs)
	{
		MessageBox(NULL, "ファイルが読み込めませんでした", LoadfilePath.c_str(), MB_OK);
		return;
	}

	// 行を読み取る用
	string line = {};
	// ラベル、イコールを読み込む用
	string label = {}, equal = {};

	while (getline(ifs, line))
	{
		string TextureFilePath = "data/TEXTURE/";

		string FilePath = {};

		istringstream iss(line);
		if (line.find("TEX_FILENAME") != string::npos)
		{
			iss >> label >> equal >> FilePath;
		}

		if (FilePath[0] != NULL)
		{
			// 文字列の連結
			TextureFilePath += FilePath;

			GetTex(TextureFilePath);
		}

		if (line.find("#") != string::npos)
		{
			continue;
		}
	}
}

//*********************************************
// テクスチャの取得処理
//*********************************************
LPDIRECT3DTEXTURE9 CLoadTexture::GetTex(string Path)
{
	// 存在したらそれを返す
	if (m_TexMap.find(Path) != m_TexMap.end()) return m_TexMap[Path];

	// 被りがなくてパスの長さが短かったらクリエイト
	CRenderer* pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの情報を代入する一時変数
	LPDIRECT3DTEXTURE9 TexInfo = NULL;

	// 作成
	D3DXCreateTextureFromFile(
		pDevice,
		Path.c_str(),
		&TexInfo
	);

	// 代入
	m_TexMap[Path] = TexInfo;

	// 情報を返す
	return m_TexMap[Path];
}

//*********************************************
// インデックスでテクスチャ取得
//*********************************************
LPDIRECT3DTEXTURE9 CLoadTexture::GetTex(const int Idx)
{
	// 不正なインデックスならアサート
	if (Idx < 0 || Idx >= (int)m_TexMap.size()) assert(0 && "存在しないテクスチャにアクセスしようとしています");

	// 配列でアクセスするためのイテレーター
	auto Map = m_TexMap.begin();

	// 要素を進める
	std::advance(Map, Idx);

	// Vlueを返す
	return Map->second;
}

//*********************************************
// テクスチャの破棄
//*********************************************
void CLoadTexture::UnRegistTex(void)
{
	// マップの中にアクセス
	for (auto& Map : m_TexMap) 
	{
		// nullptrチェック
		if (Map.second != nullptr)
		{
			// メモリ開放
			Map.second->Release();

			// nullptrを敷き詰める
			Map.second = nullptr;
		}
	}

	// マップ自体をクリア
	m_TexMap.clear();
}