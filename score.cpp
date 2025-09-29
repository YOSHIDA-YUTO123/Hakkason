//================================================
//
// �X�R�A��\�����鏈�� [score.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "score.h"
#include "number.h"
#include "math.h"

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p
using namespace math;  // ���O���math�̎g�p

//=================================================
// �R���X�g���N�^
//=================================================
CScore::CScore()
{
	m_bShowZero = false;
	m_nDigit = NULL;
	m_pos = VEC3_NULL;
	m_Size = VEC2_NULL;
	m_nScore = NULL;

	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}

//=================================================
// �f�X�g���N�^
//=================================================
CScore::~CScore()
{
}

//=================================================
// ��������
//=================================================
CScore* CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nScore, const bool bShowZero)
{
	// �X�R�A�̐���
	CScore* pScore = new CScore;

	pScore->m_pos = pos;
	pScore->m_Size = Size;
	pScore->m_nScore = nScore;
	pScore->m_bShowZero = bShowZero;

	// ����������
	if (FAILED(pScore->Init()))
	{
		pScore->Uninit();
		pScore = nullptr;
		return nullptr;
	}

	return pScore;
}

//=================================================
// ����������
//=================================================
HRESULT CScore::Init(void)
{
	// �v�Z�p
	int nScoreWk = m_nScore;

	// �X�R�A������Ȃ�
	if (nScoreWk != 0)
	{
		// ���������߂�
		while (nScoreWk != 0)
		{
			nScoreWk /= 10;
			m_nDigit++;
		}
	}
	else
	{
		// �X�R�A��0�������猅�ɂ���
		m_nDigit++;
	}

	// �����̐���
	m_nDigit = Clamp(m_nDigit, 0, MAX_DIGIT);

	// �[����\������Ȃ�
	if (m_bShowZero)
	{
		// �������ő�ɂ���
		m_nDigit = MAX_DIGIT;
	}
	// �����̊��������߂�
	float fWidth = m_Size.x / MAX_DIGIT;

	// ��̈ʒu
	float fOffPosX = fWidth * 2.0f;

	// ��������
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		// �i���o�[�N���X�̐���
		m_apNumber[nCnt] = new CNumber;

		// ����������
		HRESULT resutl = m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fOffPosX * nCnt), m_pos.y, m_pos.z), D3DXVECTOR2(fWidth, m_Size.y));

		// �������Ɏ��s������
		if (FAILED(resutl))
		{
			return E_FAIL;
		}

		// �e�N�X�`���̓ǂݍ���
		m_apNumber[nCnt]->SetTextureID("number000.png");
	}

	return S_OK;
}

//=================================================
// �I������
//=================================================
void CScore::Uninit(void)
{
	// ��������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �I������
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = nullptr;
	}

	// �������g�̔j��
	CObject::Release();
}

//=================================================
// �X�V����
//=================================================
void CScore::Update(void)
{
	
	// ��������
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
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
		int nNumber = m_nScore / nDivi % 10;

		m_apNumber[nCnt]->SetUV(nNumber);
	}
}

//=================================================
// �`�揈��
//=================================================
void CScore::Draw(void)
{
	// ��������
	for (int nCnt = 0; nCnt < m_nDigit; nCnt++)
	{
		// null�Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;

		// �`�揈��
		m_apNumber[nCnt]->Draw();
	}
}
