//================================================
//
// ���b�V���T�[�N���̕`�� [impact.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "MeshCircle.h"
#include "manager.h"
#include "renderer.h"
#include "meshfield.h"
#include "texmanager.h"
using namespace std;

using namespace Const;							// ���O���Const���g�p����

//================================================
// �R���X�g���N�^
//================================================
CMeshCircle::CMeshCircle()
{
	m_fDecAlv = NULL;
	m_fHeight = NULL;
	m_fInRadius = NULL;
	m_fOutRadius = NULL;
	m_nLife = NULL;
	m_fSpeed = NULL;
	m_InCol = WHITE;
	m_OutCol = WHITE;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumIdx = NULL;
	m_nNumPolygon = NULL;
	m_nNumVtx = NULL;
	m_nSegH = 1;
	m_nSegV = 1;
	m_pIdxBuffer = nullptr;
	m_pVtxBuffer = nullptr;
	m_pos = VEC3_NULL;
	m_rot = VEC3_NULL;
}

//================================================
// �f�X�g���N�^
//================================================
CMeshCircle::~CMeshCircle()
{
}

//================================================
// ��������
//================================================
CMeshCircle* CMeshCircle::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fInRadius, const float fOutRadius, const int nSegH)
{
	// ���b�V���T�[�N���𐶐�
	CMeshCircle* pCircle = new CMeshCircle;

	// z�̕�����1�Œ�
	const int nSegV = 1;

	// ���_���̐ݒ�
	pCircle->m_nNumVtx = (nSegH + 1) * (nSegV + 1);

	// �|���S�����̐ݒ�
	pCircle->m_nNumPolygon = ((nSegH * nSegV) * 2) + (4 * (nSegV - 1));

	// �C���f�b�N�X���̐ݒ�
	pCircle->m_nNumIdx = pCircle->m_nNumPolygon + 2;

	pCircle->m_nSegH = nSegH;
	pCircle->m_nSegV = nSegV;

	pCircle->m_pos = pos;
	pCircle->m_OutCol = col;
	pCircle->m_InCol = col;
	pCircle->m_fInRadius = fInRadius;
	pCircle->m_fOutRadius = fOutRadius;

	// �����̓����x��������
	pCircle->m_InCol.a = col.a * 0.5f;

	// ����������
	if (FAILED(pCircle->Init()))
	{
		pCircle->Uninit();
		pCircle = nullptr;
		return nullptr;
	}

	return pCircle;
}

//================================================
// �T�[�N���̐ݒ菈��
//================================================
void CMeshCircle::SetParam(const float fHeight, const float fSpeed, const int nLife, const D3DXVECTOR3 rot)
{
	// �����ɉ����������x�̌����l�̌v�Z
	m_fDecAlv = m_OutCol.a / nLife;

	// �v�f�̐ݒ菈��
	m_fHeight = fHeight;
	m_fSpeed = fSpeed;
	m_nLife = nLife;
	m_rot = rot;
}

//================================================
// ����������
//================================================
HRESULT CMeshCircle::Init(void)
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

	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �v�Z�p�̈ʒu
	D3DXVECTOR3 posWk;

	// ���_�̃J�E���g
	int nCntVtx = 0;

	float fTexPosX = 1.0f / m_nSegH;

	// ���̕���������
	for (int nCnt = 0; nCnt <= m_nSegH; nCnt++)
	{
		// �p�x�̊��������߂�
		float fAngle = (D3DX_PI * 2.0f) * m_nSegH * nCnt;

		// �ʒu�����߂�
		posWk.x = sinf(fAngle) * m_fInRadius;
		posWk.y = m_fHeight;
		posWk.z = cosf(fAngle) * m_fInRadius;

		// �ʒu�̐ݒ�
		pVtx[nCntVtx].pos = posWk;

		// �@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �F�̐ݒ�
		pVtx[nCntVtx].col = m_InCol;

		// �e�N�X�`���̐ݒ�
		pVtx[nCntVtx].tex = D3DXVECTOR2(fTexPosX * nCnt, 1.0f);

		nCntVtx++;
	}

	// ���̕���������
	for (int nCnt = 0; nCnt <= m_nSegH; nCnt++)
	{
		// �p�x�̊��������߂�
		float fAngle = (D3DX_PI * 2.0f) * m_nSegH * nCnt;

		// �ʒu�����߂�
		posWk.x = sinf(fAngle) * m_fOutRadius;
		posWk.y = 0.0f;
		posWk.z = cosf(fAngle) * m_fOutRadius;

		// �ʒu�̐ݒ�
		pVtx[nCntVtx].pos = posWk;

		// �@���̐ݒ�
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �F�̐ݒ�
		pVtx[nCntVtx].col = m_OutCol;

		// �e�N�X�`���̐ݒ�
		pVtx[nCntVtx].tex = D3DXVECTOR2(fTexPosX * nCnt, 1.0f);

		nCntVtx++;
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
void CMeshCircle::Uninit(void)
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
void CMeshCircle::Update(void)
{
	int nCntVtx = 0; // ���_���̃J�E���^�[

	// ���a���g�傷��
	m_fInRadius += m_fSpeed;
	m_fOutRadius += m_fSpeed;

	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �����̒��_�̍X�V
	for (int nCntX = 0; nCntX <= m_nSegH; nCntX++)
	{
		D3DXVECTOR3 posWk = VEC3_NULL;

		// ����̊��������߂�
		float fAngle = (D3DX_PI * 2.0f) / m_nSegH * nCntX;

		// �ό`�ɒ��_������
		posWk.x = sinf(fAngle) * m_fInRadius;
		posWk.y = m_pos.y;
		posWk.z = cosf(fAngle) * m_fInRadius;

		pVtx[nCntVtx].pos = posWk;

		// ���_�̃J�E���g�����Z
		nCntVtx++;
	}

	// �O���̒��_�̍X�V
	for (int nCntX = 0; nCntX <= m_nSegH; nCntX++)
	{
		D3DXVECTOR3 posWk = VEC3_NULL;

		float fAngle = (D3DX_PI * 2.0f) / m_nSegH * nCntX;

		posWk.x = sinf(fAngle) * m_fOutRadius;
		posWk.y = m_pos.y;
		posWk.z = cosf(fAngle) * m_fOutRadius;

		pVtx[nCntVtx].pos = posWk;

		nCntVtx++;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

	// a�l�����炷
	m_InCol.a -= m_fDecAlv;
	m_OutCol.a -= m_fDecAlv;

	// ���������炷
	m_nLife--;

	// �������s������
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		return;
	}
}

//================================================
// �`�揈��
//================================================
void CMeshCircle::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �J�����O���I���ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//================================================
// �e�N�X�`���̃p�X�̐ݒ�
//================================================
void CMeshCircle::SetTextureID(const char* pTexturePath)
{
	// �ȗ��p�p�X
	string filePath = "data/TEXTURE/";

	// ������̘A��
	filePath += pTexturePath;

	m_TexturePath = filePath;
}
