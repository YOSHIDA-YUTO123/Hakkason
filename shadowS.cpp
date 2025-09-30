//===================================================
//
// �X�e���V���V���h�E [shadowS.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "shadowS.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

using namespace Const; // ���O���Const���g�p

//===================================================
// �R���X�g���N�^
//===================================================
CShadowS::CShadowS(int nPriority) : CObjectX(nPriority)
{
	m_Scal = { 1.0f,1.0f,1.0f };
	m_pVtxBuffer = nullptr;
}

//===================================================
// �f�X�g���N�^
//===================================================
CShadowS::~CShadowS()
{
}

//===================================================
// ��������
//===================================================
CShadowS* CShadowS::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 Scal)
{
	// �e�̐���
	CShadowS* pShadowS = new CShadowS;

	if (FAILED(pShadowS->Init()))
	{
		pShadowS->Uninit();
		pShadowS = nullptr;

		return nullptr;
	}

	pShadowS->SetPosition(pos);
	pShadowS->m_Scal = Scal;
	return pShadowS;
}

//===================================================
// ����������
//===================================================
HRESULT CShadowS::Init(void)
{
	// ����������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;
	}

	// ���f���̃��[�h����
	LoadModel("ShadowS.x");

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐����E���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx = nullptr;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();
	return S_OK;
}

//===================================================
// �I������
//===================================================
void CShadowS::Uninit(void)
{
	// �I�u�W�F�N�gX�̐���
	CObjectX::Uninit();
}

//===================================================
// �X�V����
//===================================================
void CShadowS::Update(void)
{

}

//===================================================
// �`�揈��
//===================================================
void CShadowS::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	SetUpMatrix(m_Scal);

	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// ��ʃN���A(�X�e���V���o�b�t�@�̃N���A)
	pDevice->Clear(0,
		NULL,D3DCLEAR_STENCIL,
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Z�o�b�t�@�ւ̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �J���[�o�b�t�@�ւ̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR); // �X�e���V���e�X�g���i�Az�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT); // �X�e���V���e�X�g���i�Az�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO); // �X�e���V���e�X�g�s���i

	// �\�ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// �e�̕`�揈��
	SetUpDraw();

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("1"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT); // �X�e���V���e�X�g���i�Az�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_DECR);	  // �X�e���V���e�X�g���i�Az�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO); // �X�e���V���e�X�g�s���i

	// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �e�̕`�揈��
	SetUpDraw();

	// �J���[�o�b�t�@�ւ̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("2"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); // �X�e���V���e�X�g���i�Az�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); // �X�e���V���e�X�g���i�Az�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);  // �X�e���V���e�X�g�s���i

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`�����Ȃ�
	pDevice->SetTexture(0, NULL);
	
	// �v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // �v���~�e�B�u�̎��	

	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// Z�o�b�t�@�ւ̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �\�ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
