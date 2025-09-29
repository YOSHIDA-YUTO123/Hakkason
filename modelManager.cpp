//****************************************************************
//
// ���f�����ꊇ�Ǘ�����N���X�̏���[modelmanager.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "modelmanager.h"
#include "manager.h"
#include <cassert>
#include "renderer.h"
#include <fstream>
#include <sstream>

// ���O���
using namespace std;
using namespace Const;

// �ÓI�����o�ϐ�
unordered_map<std::string, CModelManager::MapObject> CModelManager::m_ModelMap = {};

//*********************************************
// �R���X�g���N�^
//*********************************************
CModelManager::CModelManager()
{
}

//*********************************************
// ���f���̑傫���̐ݒ菈��
//*********************************************
void CModelManager::SetModelSize(MapObject* pMapObject)
{
	// ���_���W�̎擾
	int nNumVtx;	// ���_��
	DWORD sizeFVF;  // ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; // ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	nNumVtx = pMapObject->modelinfo.pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�擾
	sizeFVF = D3DXGetFVFVertexSize(pMapObject->modelinfo.pMesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	pMapObject->modelinfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// �ŏ��̒��_
	D3DXVECTOR3 vtxMin = VEC3_NULL;

	// �ő�̒��_
	D3DXVECTOR3 vtxMax = VEC3_NULL;

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ���_���W���r���ău���b�N�̍ŏ��l,�ő�l���擾
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

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// �傫��
	D3DXVECTOR3 Size = VEC3_NULL;

	// �T�C�Y�ɑ��
	pMapObject->modelinfo.Size.x = vtxMax.x - vtxMin.x;
	pMapObject->modelinfo.Size.y = vtxMax.y - vtxMin.y;
	pMapObject->modelinfo.Size.z = vtxMax.z - vtxMin.z;

	// ���_�o�b�t�@�̃A�����b�N
	pMapObject->modelinfo.pMesh->UnlockVertexBuffer();
}

//*********************************************
// �f�X�g���N�^
//*********************************************
CModelManager::~CModelManager()
{
}

//*********************************************
// �t�@�C�����J��
//*********************************************
void CModelManager::Load(std::string LoadFilePath)
{
	// �ȗ��p�p�X
	string txtFilePath = "data/TXT/";

	// ������̘A��
	txtFilePath += LoadFilePath;

	ifstream ifs(txtFilePath.c_str());

	if (!ifs)
	{
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł���", txtFilePath.c_str(), MB_OK);
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
// ���f���̏����擾 & �ǉ�
//*********************************************
CModelManager::MapObject* CModelManager::GetModelInfo(string Path)
{
	// ���łɑ��݂����炻�̏���Ԃ�
	if (m_ModelMap.find(Path) != m_ModelMap.end()) return &m_ModelMap[Path];

	// ��肪�Ȃ��ăp�X�̒������Z��������N���G�C�g
	CRenderer* pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���f���̏���ǂݍ��ވꎞ�ϐ�
	MapObject LocalInfo = {};

	// X�t�@�C���Ǎ�
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

	// �ǂݍ��߂Ȃ�������
	if (FAILED(hr))
	{
		// ���s������
		assert(0 && "���f���p�X���Ԉ���Ă��܂�");
	}

	//�}�e���A���ӂ̃|�C���^���擾
	D3DXMATERIAL* pMat;
	pMat = (D3DXMATERIAL*)LocalInfo.modelinfo.pBuffMat->GetBufferPointer();

	// �}�e���A�����p�X���m��
	LocalInfo.modelinfo.TexPath.resize(LocalInfo.modelinfo.dwNumMat);

	// �}�e���A���̐�����
	for (int nCntMat = 0; nCntMat < (int)LocalInfo.modelinfo.dwNumMat; nCntMat++)
	{
		// �p�X�����݂�����
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// ���
			LocalInfo.modelinfo.TexPath[nCntMat] = pMat[nCntMat].pTextureFilename;
		}
	}

	// ���f���̑傫���̎擾
	SetModelSize(&LocalInfo);

	// �}�b�v��Vlue�Ƃ��Đݒ�
	m_ModelMap[Path] = LocalInfo;

	// ����Ԃ�
	return &m_ModelMap[Path];
}

//*********************************************
// ���f���̏����擾
//*********************************************
CModelManager::MapObject* CModelManager::GetModelInfo(const int Indx)
{
	// �s���ȃC���f�b�N�X�Ȃ�A�T�[�g
	if (Indx < 0 || Indx >= (int)m_ModelMap.size()) assert(0 && "���݂��Ȃ����f���ɃA�N�Z�X���悤�Ƃ��Ă��܂�");

	// �z��ŃA�N�Z�X���邽�߂̃C�e���[�^�[
	auto Map = m_ModelMap.begin();

	// �v�f��i�߂�
	std::advance(Map, Indx);

	// Vlue��Ԃ�
	return &Map->second;
}

//*********************************************
// ���낢��j��
//*********************************************
void CModelManager::UnRegistModel(void)
{
	// �}�b�v�̒��ɃA�N�Z�X
	for (auto& Map : m_ModelMap)
	{
		// nullptr�`�F�b�N
		if (Map.second.modelinfo.pMesh != nullptr)
		{
			// �������J��
			Map.second.modelinfo.pMesh->Release();

			// nullptr��������
			Map.second.modelinfo.pMesh = nullptr;
		}
		// nullptr�`�F�b�N
		if (Map.second.modelinfo.pBuffMat != nullptr)
		{
			// �������J��
			Map.second.modelinfo.pBuffMat->Release();

			// nullptr��������
			Map.second.modelinfo.pBuffMat = nullptr;
		}
	}

	// �}�b�v���̂��N���A
	m_ModelMap.clear();
}