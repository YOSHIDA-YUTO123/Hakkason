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
#include"texmanager.h"

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
	m_Size = VEC3_NULL;
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
	// �}�b�v�̃I�u�W�F�N�g�̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		return E_FAIL;
	}
	
	// ���f���̖��O�̐ݒ�
	m_aModelName = pModelName;

	// �傫���̎擾
	m_Size = pMapObject->modelinfo.Size;

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CModel::Uninit(void)
{

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

	// ���f���̏��̎擾
	CModelManager::MapObject *pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CLoadTexture::GetTex(m_aTexturePath));

		//���f��(�p�[�c)�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
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

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pMapObject == nullptr)
	{
		//�ۑ����Ă����}�e���A�������ɖ߂�
		pDevice->SetMaterial(&matDef);

		return;
	}

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pMapObject->modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < pMapObject->modelinfo.dwNumMat; nCntMat++)
	{
		// �}�e���A���̎擾
		D3DXMATERIAL Mat = pMat[nCntMat];

		// �����x�̐ݒ�
		Mat.MatD3D.Diffuse.a = fAlv;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&Mat.MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CLoadTexture::GetTex(m_aTexturePath));

		//���f��(�p�[�c)�̕`��
		pMapObject->modelinfo.pMesh->DrawSubset(nCntMat);
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

	// ���f���̏��̎擾
	CModelManager::MapObject* pMapObject = CModelManager::GetModelInfo(m_aModelName);

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
