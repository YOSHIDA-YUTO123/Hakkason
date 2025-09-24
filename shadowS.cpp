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
CShadowS* CShadowS::Create(const D3DXVECTOR3 pos)
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
	LoadModel("data/MODEL/ShadowS.x");

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
