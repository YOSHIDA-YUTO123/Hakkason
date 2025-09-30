//===================================================
//
// マップ管理 [mapmanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

// 二重インクルード防止
#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

// インクルード
#include <string>
#include <memory>

// マップを管理するクラスを定義
class CMapManager
{
public:
	~CMapManager();

	// 静的メンバ関数
	static void Load(std::string Path);
	static CMapManager* Instance(void);
private:
	CMapManager() {}
	// 静的メンバ変数
	static std::unique_ptr<CMapManager> m_Instance;
};
#endif // !_MAPMANAGER_H_