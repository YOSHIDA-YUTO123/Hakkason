//================================================
//
// ���b�V���V�����_�[�̕`�� [MeshCylinder.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "MeshCylinder.h"
#include "manager.h"
#include "renderer.h"
#include "texmanager.h"
using namespace std;

using namespace Const; // ���O���Const�̎g�p

//================================================
// �R���X�g���N�^
//================================================
CMeshCylinder::CMeshCylinder(const int nPriority) : CObject(nPriority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pIdxBuffer = nullptr;
	m_pVtxBuffer = nullptr;
	m_fHeight = NULL;
	m_fRadius = NULL;
	m_nNumIdx = NULL;
	m_nNumPolygon = NULL;
	m_nNumVtx = NULL;
	m_nSegH = 1;
	m_nSegV = 1;
	m_rot = VEC3_NULL;
	m_pos = VEC3_NULL;
}

//================================================
// �f�X�g���N�^
//================================================
CMeshCylinder::~CMeshCylinder()
{
}

//================================================
// �V�����_�[�̐�������
//================================================
CMeshCylinder* CMeshCylinder::Create(const D3DXVECTOR3 pos, const float fRadius, const float fHeight, const int nSegH, const int nSegV)
{
	// ���b�V���t�B�[���h�𐶐�
	CMeshCylinder* pCylinder = new CMeshCylinder;

	if (pCylinder == nullptr) return nullptr;

	// ���_���̐ݒ�
	pCylinder->m_nNumVtx = (nSegH + 1) * (nSegV + 1);

	// �|���S�����̐ݒ�
	pCylinder->m_nNumPolygon = ((nSegH * nSegV) * 2) + (4 * (nSegV - 1));

	// �C���f�b�N�X���̐ݒ�
	pCylinder->m_nNumIdx = pCylinder->m_nNumPolygon + 2;

	pCylinder->m_pos = pos;
	pCylinder->m_fRadius = fRadius;
	pCylinder->m_fHeight = fHeight;
	pCylinder->m_nSegH = nSegH;
	pCylinder->m_nSegV = nSegV;

	// ����������
	if (FAILED(pCylinder->Init()))
	{
		pCylinder->Uninit();

		// null�ɂ���
		pCylinder = nullptr;

		return nullptr;
	}

	return pCylinder;
}

//================================================
// ����������
//================================================
HRESULT CMeshCylinder::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	//�C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	int nCntVtx = 0;

	float fTexPosX = 1.0f / m_nSegH;
	float fTexPosY = 1.0f / m_nSegV;

	D3DXVECTOR3 posWk;

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV <= m_nSegV; nCntV++)
	{
		for (int nCntH = 0; nCntH <= m_nSegH; nCntH++)
		{
			// �p�x�̊��������߂�
			float fAngle = (D3DX_PI * 2.0f) / m_nSegH * nCntH;

			// �ʒu�̐ݒ�
			posWk.x = sinf(fAngle) * m_fRadius;
			posWk.y = m_fHeight - (m_fHeight / m_nSegV * nCntV);
			posWk.z = cosf(fAngle) * m_fRadius;

			// �ʒu�̐ݒ�
			pVtx[nCntVtx].pos = posWk;

			D3DXVECTOR3 nor = pVtx[nCntVtx].pos - m_pos;
			D3DXVec3Normalize(&nor, &nor);

			// �@���x�N�g���̐ݒ�
			pVtx[nCntVtx].nor = nor;
		
			//���_�J���[�̐ݒ�
			pVtx[nCntVtx].col = WHITE;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtx].tex = D3DXVECTOR2(fTexPosX * nCntH, fTexPosY * nCntV);

			nCntVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

	int IndxNum = m_nSegH + 1;//X

	int IdxCnt = 0;//�z��

	int Num = 0;//

	WORD* pIdx = nullptr;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < m_nSegV; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= m_nSegH; IndxCount2++, IndxNum++, Num++)
		{
			// �C���f�b�N�X�o�b�t�@�̐ݒ�
			pIdx[IdxCnt] = static_cast<WORD>(IndxNum);
			pIdx[IdxCnt + 1] = static_cast<WORD>(Num);
			IdxCnt += 2;
		}

		// NOTE:�Ō�̍s����Ȃ�������
		if (IndxCount1 < m_nSegV - 1)
		{
			pIdx[IdxCnt] = static_cast<WORD>(Num - 1);
			pIdx[IdxCnt + 1] = static_cast<WORD>(IndxNum);
			IdxCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuffer->Unlock();

	return S_OK;
}

//================================================
// �I������
//================================================
void CMeshCylinder::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuffer != nullptr)
	{
		m_pIdxBuffer->Release();
		m_pIdxBuffer = nullptr;
	}

	// �������g�̔j��
	CObject::Release();
}

//================================================
// �X�V����
//================================================
void CMeshCylinder::Update(void)
{
}

//================================================
// �`�揈��
//================================================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffer);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CLoadTexture::GetTex(m_TexturePath));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVtx, 0, m_nNumPolygon);
}

//================================================
// �e�N�X�`����ID�̐ݒ�
//================================================
void CMeshCylinder::SetTextureID(const char* pTexturePath)
{
	// �ȗ��p�p�X
	string filePath = "data/TEXTURE/";

	// ������̘A��
	filePath += pTexturePath;

	m_TexturePath = filePath;
}
