//****************************************************************
//
// ���f�����ꊇ�Ǘ�����N���X�̏���[modelmanager.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

// �C���N���[�h
#include "texmanager.h"

// ���f���}�l�[�W���[���`
class CModelManager
{
public:
	// ���f���̊�b���̍\����
	struct ModelInfo
	{
		// ���f�����̍\����
		LPD3DXMESH pMesh;					// ���b�V���ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;				// �}�e���A���ւ̃|�C���^
		DWORD dwNumMat;						// �}�e���A���̐�
		std::vector<std::string> TexPath;	// �e�N�X�`���p�X
		D3DXVECTOR3 Size;					// �傫��
	};

	// �}�b�v�ɏo���I�u�W�F�N�g�̊�b���
	struct MapObject
	{
		ModelInfo modelinfo;	// ���f���̊�{���
	};

	// �f�X�g���N�^
	~CModelManager();

	// �ǂݍ��݁E�j��
	static void Load(std::string LoadFilePath);

	// �ÓI�����o�֐�
	static void UnRegistModel(void);

	// �Q�b�^�[
	static MapObject* GetModelInfo(std::string Path);
	static MapObject* GetModelInfo(const int Indx);
private:
	// �R���X�g���N�^�E�f�X�g���N�^
	CModelManager();

	// ���f���̑傫���̐ݒ菈��
	static void SetModelSize(MapObject *pMapObject);

	// �ÓI�����o�ϐ�
	static std::unordered_map<std::string, MapObject> m_ModelMap;	// ���f�������i�[����ϐ�
};
#endif // !_MODELMANAGER_H_