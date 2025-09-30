//===================================================
//
// �}�b�v�Ǘ� [mapmanager.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// �C���N���[�h
#include "mapmanager.h"
#include "objectX.h"
#include <iostream>
#include <fstream>

// �l�[���X�y�[�X
using namespace std;
using ordered_json = nlohmann::ordered_json;

// �ÓI�����o�ϐ�
std::unique_ptr<CMapManager> CMapManager::m_Instance = NULL;

//=================================================
// �f�X�g���N�^
//=================================================
CMapManager::~CMapManager()
{
}

//=================================================
// �ǂݍ���
//=================================================
void CMapManager::Load(std::string Path)
{
	// json�t�@�C�����J��
	ifstream ifs(Path);

	if (!ifs)
	{
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł���", "�I�����b�Z�[�W", MB_OK);
		return;
	}
	if (ifs.is_open() == false)
	{
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł���", "�I�����b�Z�[�W", MB_OK);
		return;
	}

	// json�f�[�^��錾
	ordered_json jsonData;
	// json��ǂݍ���
	ifs >> jsonData;

	// SetStage�z��̒��ɂ���f�[�^�������݂��Ȃ�������I���
	for (const auto& obj : jsonData["SetStage"])
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 Rot;
		std::string LocalPath;

		// Path�^�O�̃f�[�^�����o��
		LocalPath = obj["Path"];

		// Pos�^�O�̃f�[�^�����o��
		Pos.x = obj["Pos"][0];
		Pos.y = obj["Pos"][1];
		Pos.z = obj["Pos"][2];

		// Rot�^�O�̃f�[�^�����o��
		Rot.x = obj["Rot"][0];
		Rot.y = obj["Rot"][1];
		Rot.z = obj["Rot"][2];

		CObjectX::Create(Pos, LocalPath.c_str(), Rot);
	}
}

//=================================================
// �C���X�^���X�擾
//=================================================
CMapManager* CMapManager::Instance(void)
{
	if (m_Instance != NULL) return m_Instance.get();
	m_Instance.reset(new CMapManager);
	return m_Instance.get();
}