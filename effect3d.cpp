//****************************************************************
//
// �RD�G�t�F�N�g�̏���[effect3D.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "effect3d.h"
#include "textureManager.h"
#include "manager.h"
#include "renderer.h"

// ���O���
using namespace Const;

//*********************************************
// �R���X�g���N�^
//*********************************************
CEffect3D::CEffect3D(const int Priority) : CObjectBillboard(Priority)
{
	// �G�t�F�N�g�̋�����������
	m_Module.Move = VEC3_NULL;
	m_Module.nLife = NULL;
	m_Module.fAlphaDef = NULL;
	m_Module.fSizeDefX = NULL;
	m_Module.fSizeDefY = NULL;
}

//*********************************************
// �f�X�g���N�^
//*********************************************
CEffect3D::~CEffect3D()
{
}

//*********************************************
// ����������
//*********************************************
HRESULT CEffect3D::Init(void)
{
	// �e�N�X�`���̃C���f�b�N�X��ݒ�
	CObjectBillboard::SetTextureID(m_Module.FilePath);
	// ��t���[���ɉ�����A���t�@�l�ƃT�C�Y��ݒ�
	m_Module.fAlphaDef = m_Module.Col.a / m_Module.nLife;
	m_Module.fSizeDefX = CObjectBillboard::GetSize().x / m_Module.nLife;
	m_Module.fSizeDefY = CObjectBillboard::GetSize().y / m_Module.nLife;
	// �r���{�[�h�̏���������
	return CObjectBillboard::Init();
}

//*********************************************
// �I������
//*********************************************
void CEffect3D::Uninit(void)
{
	// �r���{�[�h�̏I������(��������j��)
	CObjectBillboard::Uninit();
}

//*********************************************
// �X�V����
//*********************************************
void CEffect3D::Update(void)
{
	// ���������炷
	m_Module.nLife--;
	// �������s������
	if (m_Module.nLife < 0)
	{
		Uninit();
		return;
	}

	// �F�ƃT�C�Y�����炷
	D3DXCOLOR Col = m_Module.Col;
	Col.a -= m_Module.fAlphaDef;
	D3DXVECTOR2 Size = {m_Module.fSizeDefX,m_Module.fSizeDefY};
	Size.x -= m_Module.fSizeDefX;
	Size.y -= m_Module.fSizeDefY;
	// �ʒu�𓮂���
	D3DXVECTOR3 Pos = CObjectBillboard::GetPosition();
	m_Module.Move.y += m_Module.fGravity;
	Pos += m_Module.Move;
	// �ݒ�
	CObjectBillboard::SetColor(Col);
	CObjectBillboard::SetSize(Size);
	CObjectBillboard::SetPosition(Pos);
	CObjectBillboard::Update();
}

//*********************************************
// �`�揈��
//*********************************************
void CEffect3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �[�b�g�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// a�u�����f�B���O
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObjectBillboard::Draw();

	//�[�b�g�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// a�u�����f�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//*********************************************
// ����
//*********************************************
CEffect3D* CEffect3D::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXCOLOR Col, D3DXVECTOR2 Size, float Gravity, int Life, const char* FilePath,const int Priority)
{
	CEffect3D* pEffect = NULL;
	// �������m��
	pEffect = new CEffect3D(Priority);
	// ������
	pEffect->m_Module.Move = Move;
	pEffect->m_Module.nLife = Life;
	pEffect->m_Module.Col = Col;
	pEffect->m_Module.fGravity = Gravity;
	pEffect->m_Module.FilePath = FilePath;
	pEffect->SetPosition(Pos);
	pEffect->SetSize(Size);
	// ����������
	pEffect->Init();
	return pEffect;
}