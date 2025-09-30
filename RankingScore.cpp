//================================================
//
// �����L���O�̃X�R�A��`�悷�� [RankingScore.h]
// Author: YUTO YOSHIDA
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "RankingScore.h"
#include "number.h"

using namespace Const; // ���O���Const�̎g�p

//************************************************
// �萔�錾
//************************************************
constexpr int ADD_FRAME = 120; // ���Z�t���[��
constexpr int ADD_SCPRE_OFFSET = 60; // ���Z�X�R�A�̃I�t�Z�b�g

//================================================
// �R���X�g���N�^
//================================================
CRankingScore::CRankingScore() : CObject(7)
{
	// �ő�̌�������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
	
	m_col = WHITE;
	m_pos = VEC3_NULL;
	m_DestSize = VEC2_NULL;
	m_Size = VEC2_NULL;
	m_nDestScore = NULL;
	m_nScore = NULL;
	m_fCounter = NULL;
	m_bHilight = false;
}

//================================================
// �f�X�g���N�^
//================================================
CRankingScore::~CRankingScore()
{
}

//================================================
// ��������
//================================================
CRankingScore* CRankingScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nScore, const bool bHilight)
{
	CRankingScore* pScore = new CRankingScore;
	
	pScore->m_pos = pos;
	pScore->m_DestSize = Size;
	pScore->m_nDestScore = nScore;
	pScore->m_bHilight = bHilight;
	
	// ����������
	if (FAILED(pScore->Init()))
	{
		pScore->Uninit();
		pScore = nullptr;
		return nullptr;
	}

	return pScore;
}

//================================================
// ����������
//================================================
HRESULT CRankingScore::Init(void)
{
	// ���������߂�
	float fWidth = m_DestSize.x * 1.5f;

	// �ő�̉��������߂�
	float fMaxWidth = fWidth * MAX_DIGIT;
	
	// �傫���̐ݒ�
	m_Size = m_DestSize * 50.0f;

	// �ő�̌�������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// ����������
		if (m_apNumber[nCnt] == nullptr)
		{
			// �i���o�[�̐�������
			m_apNumber[nCnt] = new CNumber;

			// �ʒu���v�Z
			float fPosX = m_pos.x - (fMaxWidth / MAX_DIGIT * nCnt);

			// ����������
			HRESULT result = m_apNumber[nCnt]->Init(
				D3DXVECTOR3(fPosX, m_pos.y, m_pos.z),
				D3DXVECTOR2(m_Size.x,m_Size.y));

			// �������Ɏ��s������
			if (FAILED(result))
			{
				return E_FAIL;
			}

			// �e�N�X�`����ID�̐ݒ�
			m_apNumber[nCnt]->SetTextureID("number000.png");
		}
	}
	return S_OK;
}

//================================================
// �I������
//================================================
void CRankingScore::Uninit(void)
{
	// �ő�̌�������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// �I������
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}

	// �������g�̔j��
	CObject::Release();
}

//================================================
// �X�V����
//================================================
void CRankingScore::Update(void)
{
	// �ړI�̒l�𒴂�����
	if (m_nDestScore <= m_nScore)
	{
		m_nScore = m_nDestScore;
	}
	else
	{
		// ���Z�l�����߂�
		int nAddScore = m_nDestScore / ADD_FRAME;

		if (nAddScore <= 0)
		{
			// �Œ�ۏ�
			nAddScore = ADD_SCPRE_OFFSET;
		}

		// �X�R�A�����Z
		m_nScore += nAddScore;
	}

	// �ő�̌�������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// �g�p����Ă��Ȃ��Ȃ珈�����Ȃ�
		if (m_apNumber[nCnt] == nullptr) continue;
	
		// �����\������Ȃ�
		if (m_bHilight)
		{
			m_fCounter += 0.005f;

			// �F�̐ݒ�
			m_col.g = fabsf(sinf(m_fCounter));
			m_col.b = fabsf(sinf(m_fCounter));

			// �F�̐ݒ�
			m_apNumber[nCnt]->SetColor(m_col);
		}

		// �X�R�A������l
		int nData = 10;

		// ���ɉ������l�����߂�
		int nDivi = (int)pow((double)nData, (double)nCnt);

		// �e�N�X�`�����W�����߂�
		int nNumber = m_nScore / nDivi % 10;

		// �e�N�X�`�����W�̐ݒ�
		m_apNumber[nCnt]->SetUV(nNumber);

		// �ړI�̑傫���ɋ߂Â���
		m_Size += (m_DestSize - m_Size) * 0.01f;

		// �傫���̐ݒ�
		m_apNumber[nCnt]->SetSize(m_Size);

		// �X�V����
		m_apNumber[nCnt]->Update();
	}
}

//================================================
// �`�揈��
//================================================
void CRankingScore::Draw(void)
{
	// �ő�̌�������
	for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
	{
		// �`�揈��
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}
