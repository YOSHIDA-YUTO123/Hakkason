//==============================================
//
// ���f���}�l�[�W���[ [modelManager.h]
// Author:YUTO YOSHIDA
//
//==============================================

//**********************************************
// �C���N���[�h�t�@�C��
//**********************************************
#include "modelManager.h"
#include "manager.h"
#include"renderer.h"
#include<stdio.h>
#include"LoadManager.h"

//**********************************************
// �ÓI�����o�ϐ��錾
//**********************************************
int CModelManager::m_nNumAll = 0;	// ���f���̑���

using namespace Const;		// ���O���Const���g�p����
using namespace std;		// ���O���std���g�p����

//==============================================
// �R���X�g���N�^
//==============================================
CModelManager::CModelManager()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CModelManager::~CModelManager()
{
}

//==============================================
// �C���f�b�N�X�̓o�^
//==============================================
int CModelManager::Register(const char* pFilename)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nIdx = -1;

	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	for (int nCnt = 0; nCnt < nNumModel; nCnt++)
	{
		if (pFilename == NULL || m_apModelInfo[nCnt].filepath == NULL)
		{
			continue;
		}

		if (strcmp(m_apModelInfo[nCnt].filepath, pFilename) == 0)
		{
			return nCnt;
		}
	}

	if (nIdx == -1)
	{
		// ���f���̏��
		ModelInfo info;

		// �l���N���A���Ă���
		memset(&info, NULL, sizeof(info));

		////X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&info.pBuffMat,
			NULL,
			&info.dwNumMat,
			&info.pMesh)))
		{
			// ���b�Z�[�W�{�b�N�X�̕\��
			MessageBox(NULL, pFilename, "���f�����ǂݍ��߂܂���ł���", MB_OK | MB_ICONWARNING);

			return -1;
		}

		// ��������R�s�[����
		strncpy(info.filepath, pFilename, sizeof(info.filepath));

		// �v�f�̐ݒ�
		m_apModelInfo.push_back(info);

		// �C���f�b�N�X�̔ԍ���Ԃ�
		nIdx = m_nNumAll;

		m_nNumAll++;
	}

	return nIdx;
}

//==============================================
// ���b�V���̎擾
//==============================================
LPD3DXMESH CModelManager::GetMesh(int nIdx)
{
	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	if (nIdx < 0 || nIdx >= nNumModel)
	{
		return nullptr;
	}

	return m_apModelInfo[nIdx].pMesh;
}

//==============================================
// �o�b�t�@�̎擾
//==============================================
LPD3DXBUFFER CModelManager::GetBuffMat(int nIdx)
{
	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	if (nIdx < 0 || nIdx >= nNumModel)
	{
		return nullptr;
	}

	return m_apModelInfo[nIdx].pBuffMat;
}

//==============================================
// �}�e���A���̂̎擾
//==============================================
DWORD CModelManager::GetNumMat(int nIdx)
{
	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	if (nIdx < 0 || nIdx >= nNumModel)
	{
		return 0;
	}

	return m_apModelInfo[nIdx].dwNumMat;
}

//==============================================
// �傫���̎擾
//==============================================
D3DXVECTOR3 CModelManager::GetSize(int nIdx)
{
	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	if (nIdx < 0 || nIdx >= nNumModel)
	{
		return VEC3_NULL;
	}

	// ���_���W�̎擾
	int nNumVtx;	// ���_��
	DWORD sizeFVF;  // ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff; // ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	nNumVtx = m_apModelInfo[nIdx].pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�擾
	sizeFVF = D3DXGetFVFVertexSize(m_apModelInfo[nIdx].pMesh->GetFVF());

	// ���_�o�b�t�@�̃��b�N
	m_apModelInfo[nIdx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// ���_���W���r���ău���b�N�̍ŏ��l,�ő�l���擾
		if (vtx.x < m_apModelInfo[nIdx].vtxMin.x)
		{
			m_apModelInfo[nIdx].vtxMin.x = vtx.x;
		}
		if (vtx.y < m_apModelInfo[nIdx].vtxMin.y)
		{
			m_apModelInfo[nIdx].vtxMin.y = vtx.y;
		}
		if (vtx.z < m_apModelInfo[nIdx].vtxMin.z)
		{
			m_apModelInfo[nIdx].vtxMin.z = vtx.z;
		}
		if (vtx.x > m_apModelInfo[nIdx].vtxMax.x)
		{
			m_apModelInfo[nIdx].vtxMax.x = vtx.x;
		}
		if (vtx.y > m_apModelInfo[nIdx].vtxMax.y)
		{
			m_apModelInfo[nIdx].vtxMax.y = vtx.y;
		}
		if (vtx.z > m_apModelInfo[nIdx].vtxMax.z)
		{
			m_apModelInfo[nIdx].vtxMax.z = vtx.z;
		}

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// �傫��
	D3DXVECTOR3 Size = VEC3_NULL;

	// �T�C�Y�ɑ��
	Size.x = m_apModelInfo[nIdx].vtxMax.x - m_apModelInfo[nIdx].vtxMin.x;
	Size.y = m_apModelInfo[nIdx].vtxMax.y - m_apModelInfo[nIdx].vtxMin.y;
	Size.z = m_apModelInfo[nIdx].vtxMax.z - m_apModelInfo[nIdx].vtxMin.z;

	// ���_�o�b�t�@�̃A�����b�N
	m_apModelInfo[nIdx].pMesh->UnlockVertexBuffer();

	return Size;
}

//==============================================
// ���ׂĂ�xFile�̃��[�h����
//==============================================
HRESULT CModelManager::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C�����J��
	fstream file("data/TXT/Modellist.txt");
	string line, input;

	// null����Ȃ�������
	if (file.is_open())
	{
		// ���[�h�}�l�[�W���[�̐���
		unique_ptr<CLoadManager> pLoad = make_unique<CLoadManager>();

		// �t�@�C������s���ǂݎ��
		while (getline(file, line))
		{
			size_t equal_pos = line.find("="); // =�̈ʒu

			// [=] ���������߂�
			input = line.substr(equal_pos + 1);

			// �����񂪈�v���Ă�����
			if (line.find("FILENAME") != string::npos)
			{
				// ���l��ǂݍ��ޏ���
				istringstream value_Input = pLoad->SetInputvalue(input);

				// ���f���̖��O�i�[�p�ϐ�
				string modelName;

				// ���l��������
				value_Input >> modelName;

				// ���f���̖��O����
				const char* MODEL_NAME = modelName.c_str();

				// ���f���̏��
				ModelInfo info;

				// �l���N���A���Ă���
				memset(&info, NULL, sizeof(info));

				////X�t�@�C���̓ǂݍ���
				if (FAILED(D3DXLoadMeshFromX(MODEL_NAME,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&info.pBuffMat,
					NULL,
					&info.dwNumMat,
					&info.pMesh)))
				{
					// ���b�Z�[�W�{�b�N�X�̕\��
					MessageBox(NULL, MODEL_NAME, "���f�����ǂݍ��߂܂���ł���", MB_OK | MB_ICONWARNING);

					return E_FAIL;
				}

				// ��������R�s�[����
				strncpy(info.filepath, MODEL_NAME, sizeof(info.filepath));

				// �v�f�̐ݒ�
				m_apModelInfo.push_back(info);

				m_nNumAll++;
			}
		}

		// �t�@�C�������
		file.close();
		file.clear();
	}
	else
	{
		// ���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�t�@�C�����J���܂���", "modelManager.txt", MB_OK | MB_ICONWARNING);
		return E_FAIL;
	}

	return S_OK;
}

//==============================================
// ���ׂĂ�xFile�̔j������
//==============================================
void CModelManager::UnLoad(void)
{
	// ���f���̐�
	int nNumModel = static_cast<int>(m_apModelInfo.size());

	// ���ׂẴ��f���̃N���A
	for (int nCnt = 0; nCnt < nNumModel; nCnt++)
	{
		// ���b�V���̔j��
		if (m_apModelInfo[nCnt].pMesh != nullptr)
		{
			m_apModelInfo[nCnt].pMesh->Release();
			m_apModelInfo[nCnt].pMesh = nullptr;
		}

		// �}�e���A���̔j��
		if (m_apModelInfo[nCnt].pBuffMat != nullptr)
		{
			m_apModelInfo[nCnt].pBuffMat->Release();
			m_apModelInfo[nCnt].pBuffMat = nullptr;
		}
	}

	// �v�f�̃N���A
	m_apModelInfo.clear();
}
