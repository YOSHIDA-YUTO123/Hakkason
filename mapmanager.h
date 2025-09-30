//===================================================
//
// �}�b�v�Ǘ� [mapmanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

// ��d�C���N���[�h�h�~
#ifndef _MAPMANAGER_H_
#define _MAPMANAGER_H_

// �C���N���[�h
#include <string>
#include <memory>

// �}�b�v���Ǘ�����N���X���`
class CMapManager
{
public:
	~CMapManager();

	// �ÓI�����o�֐�
	static void Load(std::string Path);
	static CMapManager* Instance(void);
private:
	CMapManager() {}
	// �ÓI�����o�ϐ�
	static std::unique_ptr<CMapManager> m_Instance;
};
#endif // !_MAPMANAGER_H_