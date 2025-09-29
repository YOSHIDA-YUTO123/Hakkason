//================================================
//
// ���ʂ̃^�C�}�[��\�����鏈�� [NormalTimer.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "NormalTimer.h"

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p

//=================================================
// �R���X�g���N�^
//=================================================
CNormalTimer::CNormalTimer()
{
	m_nCounter = NULL;
}

//=================================================
// �f�X�g���N�^
//=================================================
CNormalTimer::~CNormalTimer()
{
}

//=================================================
// ��������
//=================================================
CNormalTimer* CNormalTimer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime)
{
	CNormalTimer* pTimer = new CNormalTimer;

	pTimer->SetPosition(pos);
	pTimer->SetSize(Size);
	pTimer->SetTime(nTime);

	// ����������
	if (FAILED(pTimer->Init()))
	{
		pTimer->Uninit();
		pTimer = nullptr;
		return nullptr;
	}

	return pTimer;
}

//=================================================
// ����������
//=================================================
HRESULT CNormalTimer::Init(void)
{
	// ����������
	if (FAILED(CTimer::Init()))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̐ݒ�
	CTimer::SetTexture("number000.png");

	return S_OK;
}

//=================================================
// �I������
//=================================================
void CNormalTimer::Uninit(void)
{
	// �I������
	CTimer::Uninit();
}

//=================================================
// �X�V����
//=================================================
void CNormalTimer::Update(void)
{
	m_nCounter++;

	// ��b�o�߂�����
	if (m_nCounter >= FRAME)
	{
		// ���݂̎��Ԃ̎擾
		int nTime = CTimer::GetTime();

		nTime--;

		// �͈͐���
		if (nTime <= 0)
		{
			nTime = 0;
		}

		// ���݂̎��Ԃ̐ݒ�
		CTimer::SetTime(nTime);

		m_nCounter = 0;
	}

	// �X�V����
	CTimer::Update();
}

//=================================================
// �`�揈��
//=================================================
void CNormalTimer::Draw(void)
{
	// �`�揈��
	CTimer::Draw();
}
