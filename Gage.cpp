//================================================
//
// �Q�[�W [gage.cpp]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "Gage.h"
#include "player.h"
#include "game.h"

using namespace Const; // ���O���Const���g�p

//================================================
// �R���X�g���N�^
//================================================
CGage::CGage(int nPriority) : CObject2D(nPriority)
{
}

//================================================
// �f�X�g���N�^
//================================================
CGage::~CGage()
{
}

////================================================
//// ��������
////================================================
//CGage* CGage::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const D3DXCOLOR col)
//{
//	return nullptr;
//}

//================================================
// ����������
//================================================
HRESULT CGage::Init(void)
{
	// ����������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
// �I������
//================================================
void CGage::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//================================================
// �`�揈��
//================================================
void CGage::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//================================================
// �R���X�g���N�^
//================================================
CHpGage::CHpGage()
{
	m_pTemporary = nullptr;
	m_nLife = NULL;
	m_nMaxLife = NULL;
	m_bDecRightToLeft = true;
}

//================================================
// �f�X�g���N�^
//================================================
CHpGage::~CHpGage()
{
}

//================================================
// HP�Q�[�W�̐�������
//================================================
CHpGage* CHpGage::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const D3DXCOLOR col, const D3DXCOLOR temporaryColor, const int nLife, const bool bDecRightToLeft)
{
	// HP�Q�[�W�̐���
	CHpGage* pGage = new CHpGage;

	pGage->SetPosition(pos);
	pGage->SetSize(Size);

	// �ݒ菈��
	pGage->Init();
	pGage->SetSize(Size.x, Size.x, Size.y, Size.y);

	pGage->m_nLife = nLife;
	pGage->m_nMaxLife = nLife;
	pGage->m_bDecRightToLeft = bDecRightToLeft;

	pGage->m_pTemporary = new CTemporaryGage;

	pGage->SetPosition(pos);
	pGage->SetSize(Size);
	pGage->m_pTemporary->Init();
	pGage->m_pTemporary->SetGage(Size, bDecRightToLeft);
	pGage->SetColor(temporaryColor);

	return pGage;
}

//================================================
// ����������
//================================================
HRESULT CHpGage::Init(void)
{
	// ����������
	if (FAILED(CGage::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
// �I������
//================================================
void CHpGage::Uninit(void)
{
	m_pTemporary = nullptr;

	// �I������
	CGage::Uninit();
}

//================================================
// �X�V����
//================================================
void CHpGage::Update(void)
{
	// �v���C���[�̎擾
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr) return;

	// �v���C���[�̎����̎擾
	m_nLife = pPlayer->GetLife();

	// �̗͂̊������v�Z����
	float fRateLife = m_nLife / static_cast<float>(m_nMaxLife);

	// �傫��
	D3DXVECTOR2 Size = CObject2D::GetSize();

	// �傫���̎擾
	float fLength = fRateLife * Size.x;

	if (m_pTemporary != nullptr)
	{
		// �����̐ݒ�
		m_pTemporary->SetLength(fLength);
	}

	// �E���獶�Ɍ���Ȃ�
	if (m_bDecRightToLeft)
	{
		// �ݒ菈��
		CObject2D::SetSize(0.0f, fLength, Size.y, Size.y);
	}
	else
	{
		// �ݒ菈��
		CObject2D::SetSize(fLength, 0.0f, Size.y, Size.y);
	}
}

//================================================
// �`�揈��
//================================================
void CHpGage::Draw(void)
{
	// �`�揈��
	CGage::Draw();
}

//================================================
// �R���X�g���N�^
//================================================
CTemporaryGage::CTemporaryGage(int nPriority) : CGage(nPriority)
{
	m_fDestLength = NULL;
	m_fLength = NULL;
	m_bDecRightToLeft = true;
}

//================================================
// �f�X�g���N�^
//================================================
CTemporaryGage::~CTemporaryGage()
{
}

//================================================
// ����������
//================================================
HRESULT CTemporaryGage::Init(void)
{
	// ����������
	if (FAILED(CGage::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
// �I������
//================================================
void CTemporaryGage::Uninit(void)
{
	// �I������
	CGage::Uninit();
}

//================================================
// �X�V����
//================================================
void CTemporaryGage::Update(void)
{
	// �ړI�̒����ɋ߂Â���
	m_fLength += (m_fDestLength - m_fLength) * 0.05f;

	// �傫��
	D3DXVECTOR2 Size = CObject2D::GetSize();

	// �E���獶�Ɍ���Ȃ�
	if (m_bDecRightToLeft)
	{
		// �ݒ菈��
		CObject2D::SetSize(0.0f, m_fLength, Size.y, Size.y);
	}
	else
	{
		// �ݒ菈��
		CObject2D::SetSize(m_fLength, 0.0f, Size.y, Size.y);
	}
}

//================================================
// �`�揈��
//================================================
void CTemporaryGage::Draw(void)
{
	// �`�揈��
	CGage::Draw();
}

//================================================
// �Q�[�W�̐ݒ菈��
//================================================
void CTemporaryGage::SetGage(const D3DXVECTOR2 Size, const bool bDecRightToLeft)
{
	// �Q�[�W�̐ݒ菈��
	CObject2D::SetSize(Size.x, Size.x, Size.y, Size.y);
	m_fLength = m_fDestLength = Size.x;	 // �����̐ݒ�
	m_bDecRightToLeft = bDecRightToLeft; // �E���猸�邩�����猸�邩
}

//================================================
// �R���X�g���N�^
//================================================
CStaminaGage::CStaminaGage() 
{
}

//================================================
// �f�X�g���N�^
//================================================
CStaminaGage::~CStaminaGage()
{
}

//================================================
// ��������
//================================================
CStaminaGage* CStaminaGage::Create(const D3DXVECTOR3 pos, D3DXVECTOR2 Size, const D3DXCOLOR col,const float fStamina)
{
	// �X�^�~�i�Q�[�W�̐���
	CStaminaGage* pGage = new CStaminaGage;

	// �ݒ菈��
	pGage->SetPosition(pos);
	pGage->SetSize(Size);

	if (FAILED(pGage->Init()))
	{// �������Ɏ��s������
		// �I������
		pGage->Uninit();
		pGage = nullptr;

		return nullptr;
	}

	pGage->SetSize(Size.x, Size.x, Size.y, Size.y);
	pGage->m_fMaxStamina = fStamina;
	pGage->m_fStamina = fStamina;

	return pGage;
}

//================================================
// ����������
//================================================
HRESULT CStaminaGage::Init(void)
{
	// ����������
	if (FAILED(CGage::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//================================================
// �I������
//================================================
void CStaminaGage::Uninit(void)
{
	// �I������
	CGage::Uninit();
}

//================================================
// �X�V����
//================================================
void CStaminaGage::Update(void)
{
	// �X�^�~�i�̊��������߂�
	float fRate = m_fStamina / m_fMaxStamina;

	// �傫���̎擾
	D3DXVECTOR2 Size = CObject2D::GetSize();

	// �����̑傫�������߂�
	float fLength = Size.x * fRate;

	// �ݒ菈��
	CObject2D::SetSize(0.0f, fLength, Size.y, Size.y);
}

//================================================
// �`�揈��
//================================================
void CStaminaGage::Draw(void)
{
	// �`�揈��
	CGage::Draw();
}
