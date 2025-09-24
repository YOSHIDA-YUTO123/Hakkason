//===================================================
//
// �r���{�[�h�A�j���[�V�����̕`�� [billboardAnim.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "billboardAnim.h"
#include "manager.h"
#include "textureManager.h"
#include "renderer.h"
#include <string>

using namespace Const;	// ���O���Const���g�p
using namespace std;	// ���O���std���g�p

//===================================================
// �R���X�g���N�^
//===================================================
CBillboardAnimation::CBillboardAnimation(int nPriority) : CObject(nPriority)
{
	m_bLoop = false;
	m_fPosTexH = NULL;
	m_fPosTexU = NULL;
	m_nSpeed = NULL;
	m_nCounter = NULL;
	m_nPattern = NULL;
	m_nDivU = 1;
	m_nDivV = 1;
	m_nTextureIdx = -1;
}

//===================================================
// �f�X�g���N�^
//===================================================
CBillboardAnimation::~CBillboardAnimation()
{
}

//===================================================
// �A�j���[�V�����̐ݒ菈��
//===================================================
void CBillboardAnimation::SetParam(const int nSpeed, const bool bLoop)
{
	m_bLoop = bLoop;
	m_nSpeed = nSpeed;
}

//===================================================
// �������̐ݒ�
//===================================================
void CBillboardAnimation::SetDivUV(const int nDivU, const int nDivV)
{
	m_nDivU = nDivU;
	m_nDivV = nDivV;
}

//===================================================
// �e�N�X�`���̍��W�̐ݒ�
//===================================================
void CBillboardAnimation::SetTextureVtx(const D3DXVECTOR2 OffPos, const D3DXVECTOR2 RateUV)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(RateUV.x, RateUV.y);
	pVtx[1].tex = D3DXVECTOR2(RateUV.x + OffPos.x, RateUV.y);
	pVtx[2].tex = D3DXVECTOR2(RateUV.x, RateUV.y + OffPos.y);
	pVtx[3].tex = D3DXVECTOR2(RateUV.x + OffPos.x, RateUV.y + OffPos.y);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();
}

//===================================================
// �F�̐ݒ�
//===================================================
void CBillboardAnimation::SetColor(const D3DXCOLOR col)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();
}

//===================================================
// �e�N�X�`����ID�̐ݒ�
//===================================================
void CBillboardAnimation::SetTextureID(const char* pTextureName)
{
	// �e�N�X�`���}�l�[�W���[�̎擾
	CTextureManager* pTexture = CManager::GetTexture();

	// �ȗ��p�p�X
	string filePath = "data/TEXTURE/Animation/";

	// �e�N�X�`���̃p�X�̘A��
	filePath += pTextureName;

	// �e�N�X�`����ID�̓o�^
	m_nTextureIdx = pTexture->Register(filePath.c_str());
}

//===================================================
// ���_���W�̍X�V
//===================================================
void CBillboardAnimation::UpdateVertexPos(const D3DXVECTOR3 pos)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �ʒu�̐ݒ�
	m_pos = pos;

	// �傫���̎擾
	D3DXVECTOR2 Size = m_Size;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Size.x, Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Size.x, -Size.y, 0.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();
}

//===================================================
// ��������
//===================================================
CBillboardAnimation* CBillboardAnimation::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nDivU, const int nDivV)
{
	CBillboardAnimation* pBillboard = new CBillboardAnimation;

	pBillboard->SetPosition(pos);
	pBillboard->SetSize(Size);

	pBillboard->m_nDivU = nDivU;
	pBillboard->m_nDivV = nDivV;

	// ����������
	if (FAILED(pBillboard->Init()))
	{
		pBillboard->Uninit();
		pBillboard = nullptr;
		return nullptr;;
	}

	return pBillboard;
}

//===================================================
// ����������
//===================================================
HRESULT CBillboardAnimation::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �傫���̎擾
	D3DXVECTOR2 Size = m_Size;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-Size.x, Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Size.x, Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-Size.x, -Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Size.x, -Size.y, 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = WHITE;
	pVtx[1].col = WHITE;
	pVtx[2].col = WHITE;
	pVtx[3].col = WHITE;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / m_nDivU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / m_nDivV);
	pVtx[3].tex = D3DXVECTOR2(1.0f / m_nDivU, 1.0f / m_nDivV);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CBillboardAnimation::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}

	// �������g�̔j��
	Release();
}

//===================================================
// �X�V����
//===================================================
void CBillboardAnimation::Update(void)
{
	// �A�j���[�V�����̃J�E���^�[��i�߂�
	m_nCounter++;

	m_fPosTexU = 1.0f / m_nDivU;
	m_fPosTexH = 1.0f / m_nDivV;

	if (m_nCounter >= m_nSpeed)
	{
		m_nCounter = 0;

		m_nPattern++;

		// Y���W�̊���
		int nRatePosY = m_nPattern / m_nDivV;

		float UV = m_fPosTexU * m_nPattern;
		float HV = nRatePosY * m_fPosTexH;

		// �e�N�X�`�����W�̍X�V
		SetTextureVtx(D3DXVECTOR2(m_fPosTexU, m_fPosTexH), D3DXVECTOR2(UV, HV));

		// �ő�܂ōs������
		if (m_nPattern >= (m_nDivU * m_nDivV))
		{
			// �p�^�[����������
			m_nPattern = 0;

			// ���[�v���Ȃ��Ȃ�
			if (!m_bLoop)
			{
				Uninit();
				return;
			}
		}
	}
}

//===================================================
// �`�揈��
//===================================================
void CBillboardAnimation::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���N���X�̎擾
	CTextureManager* pTexture = CManager::GetTexture();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X��錾
	D3DXMATRIX mtxView;

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAdress(m_nTextureIdx));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
