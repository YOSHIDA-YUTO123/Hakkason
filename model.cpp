//===================================================
//
// ���f���̕`�������N���X [model.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "model.h"
#include "object.h"
#include "modelManager.h"
#include "manager.h"
#include"renderer.h"
#include<stdio.h>
#include"textureManager.h"

using namespace Const;		   // ���O���Const���g�p����

//===================================================
// �萔�錾
//===================================================
constexpr int MAX_TEXTURE = 2; // �e�N�X�`���̍ő吔

//===================================================
// �R���X�g���N�^
//===================================================
CModel::CModel()
{
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
	m_offpos = VEC3_NULL;
	m_offrot = VEC3_NULL;
	m_pParent = nullptr;
	m_nModelIdx = NULL;
	m_pTextureIdx = nullptr;
	m_Size = VEC3_NULL;
	m_nTextureMTIdx = -1;
	m_nParentIdx = -1;
}

//===================================================
// �f�X�g���N�^
//===================================================
CModel::~CModel()
{
}

//===================================================
// ����������
//===================================================
HRESULT CModel::Init(const char* pModelName)
{
	// ���f���N���X�̎擾
	CModelManager* pModel = CManager::GetModel();

	// �e�N�X�`���N���X�̎擾
	CTextureManager* pTexture = CManager::GetTexture();

	// ���f���}�l�[�W���[�N���X�̎擾
	CModelManager* pModelManager = CManager::GetModel();

	// ���f���̔ԍ��̓o�^
	m_nModelIdx = pModelManager->Register(pModelName);

	if (m_nModelIdx == -1)
	{
		return E_FAIL;
	}

	// ���f���̖��O�̐ݒ�
	m_aModelName = pModelName;

	// �}�e���A���̎擾
	DWORD dwNumMat = pModel->GetNumMat(m_nModelIdx);
	LPD3DXBUFFER pBuffMat = pModel->GetBuffMat(m_nModelIdx);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	// �}�e���A���̐����������̊m��
	m_pTextureIdx = new int[dwNumMat];

	for (int nCnt = 0; nCnt < (int)dwNumMat; nCnt++)
	{
		// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
		m_pTextureIdx[nCnt] = pTexture->Register(pMat[nCnt].pTextureFilename);
	}

	// �傫���̎擾
	m_Size = pModel->GetSize(m_nModelIdx);

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CModel::Uninit(void)
{
	if (m_pTextureIdx != nullptr)
	{
		delete[]m_pTextureIdx;
		m_pTextureIdx = nullptr;
	}
}

//===================================================
// �X�V����
//===================================================
void CModel::Update(void)
{
}

//===================================================
// �`�揈��
//===================================================
void CModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�̎擾
	CTextureManager* pTexture = CManager::GetTexture();

	// ���f���N���X�̎擾
	CModelManager* pModel = CManager::GetModel();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScal,mtxParent;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offpos.x, m_pos.y + m_offpos.y, m_pos.z + m_offpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{ // �e�����݂��Ă���
		// �e���f���̃}�g���b�N�X�̎擾
		mtxParent = m_pParent->GetMatrixWorld();
	}
	else
	{
		// ���[���h�}�g���b�N�X�̎擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�̃��[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_nModelIdx == -1)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->GetBuffMat(m_nModelIdx)->GetBufferPointer();

	// �}�e���A���̑����̎擾
	DWORD dwNumMat = pModel->GetNumMat(m_nModelIdx);

	// ���b�V���̎擾
	LPD3DXMESH pMesh = pModel->GetMesh(m_nModelIdx);

	for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_pTextureIdx[nCntMat] != -1)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAdress(m_pTextureIdx[nCntMat]));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		//���f��(�p�[�c)�̕`��
		pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// �`�揈��(�����x�ݒ�)
//===================================================
void CModel::Draw(const float fAlv)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�̎擾
	CTextureManager* pTexture = CManager::GetTexture();

	// ���f���N���X�̎擾
	CModelManager* pModel = CManager::GetModel();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScal, mtxParent;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offpos.x, m_pos.y + m_offpos.y, m_pos.z + m_offpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{ // �e�����݂��Ă���
		// �e���f���̃}�g���b�N�X�̎擾
		mtxParent = m_pParent->GetMatrixWorld();
	}
	else
	{
		// ���[���h�}�g���b�N�X�̎擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�̃��[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	if (m_nModelIdx == -1)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pModel->GetBuffMat(m_nModelIdx)->GetBufferPointer();

	// �}�e���A���̑����̎擾
	DWORD dwNumMat = pModel->GetNumMat(m_nModelIdx);

	// ���b�V���̎擾
	LPD3DXMESH pMesh = pModel->GetMesh(m_nModelIdx);

	for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
	{
		D3DXMATERIAL mat = pMat[nCntMat];
		mat.MatD3D.Diffuse.a = fAlv;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&mat.MatD3D);

		if (m_pTextureIdx[nCntMat] != -1)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAdress(m_pTextureIdx[nCntMat]));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		//���f��(�p�[�c)�̕`��
		pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// �e�̕`�揈��
//===================================================
void CModel::DrawShadow(void)
{
	// �����_���[�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���C�g�̕���
	D3DXVECTOR4 lightDir = D3DXVECTOR4(-0.707f, -0.707f, -0.707f, 0.0f);

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

	// ���f���̎擾
	CModelManager* pModel = CManager::GetModel();

	// ���b�V���̎擾
	LPD3DXMESH pMesh = pModel->GetMesh(m_nModelIdx);

	// ���b�V����nullptr��������֐��𔲂���
	if (pMesh == nullptr) return;

	// �}�e���A���̐��̎擾
	DWORD dwNumMat = pModel->GetNumMat(m_nModelIdx);

	// �e�̕`��
	for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
	{
		// �e�̃}�e���A���̐ݒ�
		pDevice->SetMaterial(&matShadow);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �e�̕`��
		pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�������Ƃɖ߂�
	pDevice->SetMaterial(&matDef);
}

//===================================================
// �e�̐ݒ�
//===================================================
void CModel::SetParent(CModel* pModel, const int nIdx)
{
	m_pParent = pModel;
	m_nParentIdx = nIdx;
}

//===================================================
// ���̃R�s�[
//===================================================
void CModel::Copy(CModel* pModel)
{
	pModel->m_offpos = m_offpos;	// ��̈ʒu
	pModel->m_offrot = m_offrot;	// ��̌���
}

//===================================================
// ��������
//===================================================
CModel* CModel::Create(const char *pModelName)
{
	CModel* pModel = nullptr;

	// ���f���̐���
	pModel = new CModel;

	if (pModel == nullptr) return nullptr;

	pModel->Init(pModelName);

	return pModel;
}
