//===================================================
//
// �I�u�W�F�N�gX�t�@�C�� [objectX.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "objectX.h"
#include "manager.h"
#include "renderer.h"
#include "modelManager.h"
#include "texmanager.h"

using namespace Const;	// ���O���Const���g�p����
using namespace std;	// ���O���std���g�p����

//===================================================
// �R���X�g���N�^
//===================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	memset(m_mtxWorld, NULL, sizeof(D3DXMATRIX));

	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
}

//===================================================
// �f�X�g���N�^
//===================================================
CObjectX::~CObjectX()
{
}

//===================================================
// ��������
//===================================================
CObjectX* CObjectX::Create(const D3DXVECTOR3 pos, const char* pModelName,const D3DXVECTOR3 rot)
{
	CObjectX* pObjectX = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	pObjectX = new CObjectX;

	if (pObjectX == nullptr) return nullptr;

	pObjectX->Init();
	pObjectX->m_pos = pos;
	pObjectX->m_rot = rot;
	pObjectX->LoadModel(pModelName);

	return pObjectX;
}

//===================================================
// ����������
//===================================================
HRESULT CObjectX::Init(void)
{
	return S_OK;
}

//===================================================
// �I������
//===================================================
void CObjectX::Uninit(void)
{	
	// �������g�̔j��
	CObject::Release();
}

//===================================================
// �X�V����
//===================================================
void CObjectX::Update(void)
{
}

//===================================================
// �`�揈��
//===================================================
void CObjectX::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ����
	D3DXVECTOR3 rot = m_rot;

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_ModelPath);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();
	
	for (int nCntMat = 0; nCntMat < (int)pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CLoadTexture::GetTex(pMapObject->modelinfo.TexPath[nCntMat]));

		//���f��(�p�[�c)�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// �`�揈��(�I�[�o�[���[�h)
//===================================================
void CObjectX::Draw(const float Diffuse)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScal, mtxParent;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ����
	D3DXVECTOR3 rot = m_rot;

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_ModelPath);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL Mat = pMat[nCntMat];

		Mat.MatD3D.Diffuse.a = Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Mat.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CLoadTexture::GetTex(pMapObject->modelinfo.TexPath[nCntMat]));

		//���f��(�p�[�c)�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// �e�̕`�揈��
//===================================================
void CObjectX::DrawShadow(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�g�̕���
	D3DXVECTOR4 lightDir = D3DXVECTOR4(0.707f, -0.707f, 0.707f, 0.0f);

	// �e�𗎂Ƃ��n��
	D3DXPLANE plane = D3DXPLANE(0, -1.0f, 0, 0);

	// �e�p�̃}�g���b�N�X���쐬
	D3DXMATRIX mtxShadow, mtxShadowWorld;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	// �e�p�̃}�g���b�N�X�̍쐬
	D3DXMatrixShadow(&mtxShadow, &lightDir, &plane);

	// �e�̃}�g���b�N�X�Ǝ����̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&mtxShadowWorld, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadowWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �������̍��}�e���A�����Z�b�g
	D3DMATERIAL9 matShadow = {};

	// �e�̐F�̐ݒ�
	matShadow.Diffuse.r = 0.0f;
	matShadow.Diffuse.g = 0.0f;
	matShadow.Diffuse.b = 0.0f;
	matShadow.Diffuse.a = 1.0f;

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_ModelPath);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	// �e�̕`��
	for (int nCntMat = 0; nCntMat < (int)pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		// �e�̃}�e���A���̐ݒ�
		pDevice->SetMaterial(&matShadow);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �e�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}
	
	// �}�e���A�������Ƃɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// ���[���h�}�g���b�N�X�̐ݒ�
//===================================================
void CObjectX::SetUpMatrix(const D3DXVECTOR3 Scal)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ����
	D3DXVECTOR3 rot = m_rot;

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, Scal.x, Scal.y, Scal.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScal);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//===================================================
// ���[���h�}�g���b�N�X�̐ݒ�
//===================================================
void CObjectX::SetUpMatrix(const D3DXMATRIX mtxRot, const D3DXMATRIX mtxTrans, const D3DXVECTOR3 Scal)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, Scal.x, Scal.y, Scal.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScal);

	// �����𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
}

//===================================================
// �`��܂ł̐ݒ菈��
//===================================================
void CObjectX::SetUpDraw(const float Diffuse)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_ModelPath);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL Mat = pMat[nCntMat];

		Mat.MatD3D.Diffuse.a = Diffuse;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Mat.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CLoadTexture::GetTex(pMapObject->modelinfo.TexPath[nCntMat]));

		//���f��(�p�[�c)�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// ���f���̃��[�h����
//===================================================
HRESULT CObjectX::LoadModel(const char* pXFileName)
{
	// �ȗ��p�t�@�C���p�X
	string Path = pXFileName;
	string filePath;
	if (Path.find("data/MODEL/") == string::npos)
	{
		filePath = "data/MODEL/";
	}

	// ������̘A��
	filePath += pXFileName;

	m_ModelPath = filePath;

	return S_OK;
}

//===================================================
// �傫���̎擾
//===================================================
D3DXVECTOR3 CObjectX::GetSize(void)
{
	// �}�b�v�̃I�u�W�F�N�g�̎擾
	CModelManager::MapObject *pMapObject = CModelManager::GetModelInfo(m_ModelPath);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		return VEC3_NULL;
	}

	// �傫����Ԃ�
	return pMapObject->modelinfo.Size;
}

