//================================================
//
// �^�C�}�[��\�����鏈�� [timer.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "timer.h"
#include "number.h"
#include <cassert>

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p
using namespace std;   // ���O���std�̎g�p

//=================================================
// �R���X�g���N�^
//=================================================
CTimer::CTimer()
{
	m_nTime = NULL;
	m_pos = VEC3_NULL;
	m_Size = VEC2_NULL;

	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}

//=================================================
// �f�X�g���N�^
//=================================================
CTimer::~CTimer()
{
}

//=================================================
// ����������
//=================================================
HRESULT CTimer::Init(void)
{
	// �����̊��������߂�
	float fWidth = m_Size.x / MAX_DIGIT;

	// ��̈ʒu
	float fOffPosX = fWidth * 2.0f;

	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// �i���o�[�N���X�̐���
		m_apNumber[nCnt] = make_unique<CNumber>();

		// ����������
		HRESULT resutl = m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fOffPosX * nCnt), m_pos.y, m_pos.z), D3DXVECTOR2(fWidth, m_Size.y));

		// �������Ɏ��s������
		if (FAILED(resutl))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=================================================
// �I������
//=================================================
void CTimer::Uninit(void)
{
	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �I������
		m_apNumber[nCnt]->Uninit();
		m_apNumber[nCnt].reset();
	}

	// �������g�̔j��
	CObject::Release();
}

//=================================================
// �X�V����
//=================================================
void CTimer::Update(void)
{
	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �i���o�[�̍X�V����
		m_apNumber[nCnt]->Update();

		// �X�R�A������l
		int nData = 10;

		// ���ɉ������l�����߂�
		int nDivi = (int)pow((double)nData, (double)nCnt);

		// �e�N�X�`�����W�����߂�
		int nNumber = m_nTime / nDivi % 10;

		m_apNumber[nCnt]->SetUV(nNumber);

		// ����
		if (m_nTime <= 0)
		{
			m_nTime = 0;
		}
	}
}

//=================================================
// �`�揈��
//=================================================
void CTimer::Draw(void)
{
	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �`�揈��
		m_apNumber[nCnt]->Draw();
	}
}

//=================================================
// �e�N�X�`���̃p�X�̐ݒ�
//=================================================
void CTimer::SetTexture(const char* pTexturePath)
{
	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �e�N�X�`���̃p�X�̐ݒ�
		m_apNumber[nCnt]->SetTextureID(pTexturePath);
	}
}

//=================================================
// �i���o�[�N���X�̎擾
//=================================================
CNumber* CTimer::GetNumber(const int nIdx)
{
	// �����Ă�����
	if (nIdx < 0 || nIdx > MAX_DIGIT)
	{
		assert(false && "�^�C�}�[�z��I�[�o�[");
	}

	return m_apNumber[nIdx].get();
}
