//===================================================
//
// �t�F�[�h���� [fade.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "fade.h"
#include"manager.h"
#include"renderer.h"

using namespace Const; // ���O���Const���g�p
using namespace std; // ���O���std���g�p

//===================================================
// �R���X�g���N�^
//===================================================
CFade::CFade()
{
	m_pScene = nullptr;
	m_Fade = FADE_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0, 0.0f, 1.0f);
}

//===================================================
// �f�X�g���N�^
//===================================================
CFade::~CFade()
{
}

//===================================================
// ��������
//===================================================
CFade* CFade::Create(void)
{
	// �t�F�[�h�̐���
	CFade* pFade = new CFade;

	if (FAILED(pFade->Init()))
	{
		pFade->Uninit();

		pFade = nullptr;

		return nullptr;
	}

	return pFade;
}

//===================================================
// �t�F�[�h
//===================================================
void CFade::SetFade(unique_ptr<CScene> pNewScene, const D3DXCOLOR col)
{
	if (m_Fade != FADE_NONE)
	{
		// �j������
		pNewScene.reset();
		pNewScene = nullptr;

		return;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		m_pScene.reset();
		m_pScene = nullptr;
	}

	m_col = col;
	m_Fade = FADE_OUT;

	// ���L����n��
	m_pScene = move(pNewScene);
}

//===================================================
// ����������
//===================================================
HRESULT CFade::Init(void)
{
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

	m_Fade = FADE_IN;
	m_col = D3DXCOLOR(0.0f, 0.0, 0.0f, 1.0f);
	m_pScene = nullptr;

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

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
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}
}

//===================================================
// �X�V����
//===================================================
void CFade::Update(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_col.a -= 0.03f;

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_Fade = FADE_NONE;
			}

			// ���_�o�b�t�@�̃��b�N
			m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = m_col;
			pVtx[1].col = m_col;
			pVtx[2].col = m_col;
			pVtx[3].col = m_col;

			// ���_�o�b�t�@�̃A�����b�N
			m_pVtxBuffer->Unlock();
		}
		else if (m_Fade == FADE_OUT)
		{
			// �t�F�[�h�A�E�g���
			m_col.a += 0.03f;

			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_Fade = FADE_IN;

				// ���[�h�ݒ�
				CManager::SetMode(move(m_pScene));
				return;
			}

			// ���_�o�b�t�@�̃��b�N
			m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = m_col;
			pVtx[1].col = m_col;
			pVtx[2].col = m_col;
			pVtx[3].col = m_col;

			// ���_�o�b�t�@�̃A�����b�N
			m_pVtxBuffer->Unlock();
		}
	}
}

//===================================================
// �`�揈��
//===================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`�����Ȃ�
	pDevice->SetTexture(0, NULL);

	// �v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // �v���~�e�B�u�̎��	
}

