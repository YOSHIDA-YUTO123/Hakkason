//================================================
//
// �O�Ղ̕`�� [MeshOrbit.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "MeshOrbit.h"
#include "manager.h"
#include "renderer.h"
#include "texmanager.h"
using namespace std;

using namespace Const;							// ���O���Const���g�p����

//================================================
// �R���X�g���N�^
//================================================
CMeshOrbit::CMeshOrbit()
{
	m_col = WHITE;
	m_Bottom = VEC3_NULL;
	m_Top = VEC3_NULL;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumIdx = NULL;
	m_nNumPolygon = NULL;
	m_nNumVtx = NULL;
	m_nSegH = 1;
	m_pos = VEC3_NULL;
	m_pIdxBuffer = nullptr;
	m_pVtxBuffer = nullptr;
}

//================================================
// �f�X�g���N�^
//================================================
CMeshOrbit::~CMeshOrbit()
{
}

//================================================
// �O�Ղ̐���
//================================================
CMeshOrbit* CMeshOrbit::Create(const D3DXVECTOR3 Top, const D3DXVECTOR3 Bottom, const int nSegH,const D3DXCOLOR col)
{
	// �O�Ղ𐶐�
	CMeshOrbit* pOrbit = new CMeshOrbit;

	// �c�̕�����
	const int nSegV = 1;

	// ���_�̑���
	pOrbit->m_nNumVtx = (nSegH + 1) * (nSegV + 1);

	// �C���f�b�N�X�̑���
	pOrbit->m_nNumIdx = pOrbit->m_nNumVtx;

	pOrbit->m_Bottom = Bottom;
	pOrbit->m_Top = Top;
	pOrbit->m_nSegH = nSegH;
	pOrbit->m_col = col;

	// �|���S���̑���
	pOrbit->m_nNumPolygon = pOrbit->m_nNumVtx - 2;

	// �����Ɏ��s����
	if (FAILED(pOrbit->Init()))
	{
		pOrbit->Uninit();

		pOrbit = nullptr;

		return nullptr;
	}

	return pOrbit;
}

//================================================
// ����������
//================================================
HRESULT CMeshOrbit::Init(void)
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

	// �e�N�X�`����(��)
	float fPosTexH = 1.0f / m_nSegH;

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	WORD* pIdx = nullptr;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	// ���_������
	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		// �A���t�@�l�̐ݒ�
		float fAlv = m_col.a * (1.0f - (float)nCnt / m_nNumVtx);

		// ���_�̐ݒ�(��������ꂩ���ɏW�߂�)
		pVtx[nCnt].pos = m_Top;

		// �@���A�F�A�e�N�X�`���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, fAlv);
		pVtx[nCnt].tex = D3DXVECTOR2(fPosTexH * nCnt, 1.0f);

		// �C���f�b�N�X�o�b�t�@�̐ݒ�
		pIdx[nCnt] = (WORD)nCnt;
	}

	// �l�O����n�߂�
	for (int nCnt = m_nNumVtx - 4; nCnt >= 0; nCnt -= 2)
	{
		// �O�̒��_���W������
		D3DXVECTOR3 OldVtx0 = pVtx[nCnt].pos;
		D3DXVECTOR3 OldVtx1 = pVtx[nCnt + 1].pos;

		pVtx[nCnt + 2].pos = OldVtx0;
		pVtx[nCnt + 3].pos = OldVtx1;
	}

	// �V�������_��ǉ��i�擪�ɓ����j
	pVtx[0].pos = m_Bottom;
	pVtx[1].pos = m_Top;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuffer->Unlock();

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//================================================
// �I������
//================================================
void CMeshOrbit::Uninit(void)
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
void CMeshOrbit::Update(void)
{
	int nSegV = 1;			// �c�̕�����

	// ���_�̑���
	int nNumVtx = (m_nSegH + 1) * (nSegV + 1);

	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �l�O����n�߂�
	for (int nCnt = nNumVtx - 4; nCnt >= 0; nCnt -= 2)
	{
		// �O�̒��_���W������
		D3DXVECTOR3 OldVtx0 = pVtx[nCnt].pos;
		D3DXVECTOR3 OldVtx1 = pVtx[nCnt + 1].pos;

		pVtx[nCnt + 2].pos = OldVtx0;
		pVtx[nCnt + 3].pos = OldVtx1;
	}

	// �V�������_��ǉ�
	pVtx[0].pos = m_Bottom;
	pVtx[1].pos = m_Top;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}

//================================================
// �`�揈��
//================================================
void CMeshOrbit::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �J�����O���I���ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

	// a�u�����f�B���O
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

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

	// a�u�����f�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �J�����O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//================================================
// �ʒu�̐ݒ菈��
//================================================
void CMeshOrbit::SetPosition(const D3DXVECTOR3 Top, const D3DXVECTOR3 Bottom)
{
	m_Top = Top;
	m_Bottom = Bottom;
}

//================================================
// �e�N�X�`����ID�̐ݒ�
//================================================
void CMeshOrbit::SetTextureID(const char* pTexturePath)
{
	// �ȗ��p�p�X
	string filePath = "data/TEXTURE/";

	// ������̘A��
	filePath += pTexturePath;

	m_TexturePath = filePath;
}
