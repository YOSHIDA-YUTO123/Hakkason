//===================================================
//
// マップ管理 [mapmanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// インクルード
#include "mapmanager.h"
#include "objectX.h"
#include <iostream>
#include <fstream>

// ネームスペース
using namespace std;
using ordered_json = nlohmann::ordered_json;

// 静的メンバ変数
std::unique_ptr<CMapManager> CMapManager::m_Instance = NULL;

//=================================================
// デストラクタ
//=================================================
CMapManager::~CMapManager()
{
}

//=================================================
// 読み込む
//=================================================
void CMapManager::Load(std::string Path)
{
	// jsonファイルを開く
	ifstream ifs(Path);

	if (!ifs)
	{
		MessageBox(NULL, "ファイルが読み込めませんでした", "終了メッセージ", MB_OK);
		return;
	}
	if (ifs.is_open() == false)
	{
		MessageBox(NULL, "ファイルが読み込めませんでした", "終了メッセージ", MB_OK);
		return;
	}

	// jsonデータを宣言
	ordered_json jsonData;
	// jsonを読み込む
	ifs >> jsonData;

	// SetStage配列の中にあるデータを代入存在しなかったら終わる
	for (const auto& obj : jsonData["SetStage"])
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Rot;
		std::string LocalPath;

		// Pathタグのデータを取り出す
		LocalPath = obj["Path"];

		// Posタグのデータを取り出す
		Pos.x = obj["Pos"][0];
		Pos.y = obj["Pos"][1];
		Pos.z = obj["Pos"][2];

		// Rotタグのデータを取り出す
		Rot.x = obj["Rot"][0];
		Rot.y = obj["Rot"][1];
		Rot.z = obj["Rot"][2];

		CObjectX::Create(Pos, LocalPath.c_str(), Rot);
	}
}

//=================================================
// インスタンス取得
//=================================================
CMapManager* CMapManager::Instance(void)
{
	if (m_Instance != NULL) return m_Instance.get();
	m_Instance.reset(new CMapManager);
	return m_Instance.get();
}