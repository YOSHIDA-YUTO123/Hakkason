//================================================
//
// �����L���O�}�l�[�W���[ [RankingManager.cpp]
// Author: YUTO YOSHIDA
// 
// << �����L���O�̃X�R�A�̓ǂݍ��݁A�\�[�g�A�������s�� >>
//
//================================================

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "RankingManager.h"
#include "LoadManager.h"
#include <algorithm>
#include "RankingScore.h"

using namespace Const;	// ���O���Const�̎g�p
using namespace std;	// ���O���std�̎g�p

//================================================
// �R���X�g���N�^
//================================================
CRankingManager::CRankingManager()
{
	// �l�̃N���A
	ZeroMemory(&m_aScore, sizeof(m_aScore));
	m_nResultScore = NULL;
	m_nUpdateScoreIdx = -1;
}

//================================================
// �f�X�g���N�^
//================================================
CRankingManager::~CRankingManager()
{
}

//================================================
// ��������
//================================================
void CRankingManager::Create(void)
{
	// �����L���O�}�l�[�W���[�̐���
	auto pManager = new CRankingManager;
	pManager->Init();
}

//================================================
// �����L���O�̐ݒ菈��
//================================================
void CRankingManager::SetRanking(void)
{
	// ���ʐ�����
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		// �C���f�b�N�X����v���Ă��邩��r
		const bool bHilight = (m_nUpdateScoreIdx == nCnt) ? true : false;

		// �����L���O�̃X�R�A�̐���
		CRankingScore::Create(D3DXVECTOR3(950.0f, 130.0f + nCnt * 100.0f, 0.0f), D3DXVECTOR2(45.0f, 45.0f), m_aScore[nCnt], bHilight);
	}
}

//================================================
// ����������
//================================================
HRESULT CRankingManager::Init(void)
{
	// �X�R�A�̃��[�h
	Load();

	return S_OK;
}

//================================================
// �I������
//================================================
void CRankingManager::Uninit(void)
{
	// �������g�̔j��
	CObject::Release();
}

//================================================
// �X�V����
//================================================
void CRankingManager::Update(void)
{
}

//================================================
// �`�揈��
//================================================
void CRankingManager::Draw(void)
{
}

//================================================
// �X�R�A�̃��[�h
//================================================
void CRankingManager::Load(void)
{
	// �t�@�C���̓ǂݍ���
	fstream ranking_file("data/TXT/ranking.txt");
	string line;
	string input;

	int nCnt = 0;

	// �t�@�C�����J������
	if (ranking_file.is_open())
	{
		// ���[�h�}�l�[�W���[�̐���
		unique_ptr<CLoadManager> pLoad = make_unique<CLoadManager>();

		// �t�@�C������s���ǂݎ��
		while (getline(ranking_file, line))
		{
			// �����L���O�̏��ʐ��𒴂����甲����
			if (nCnt >= NUM_RANK)
			{
				continue;
			}

			istringstream value_Input(line);

			// �l����
			value_Input >> m_aScore[nCnt];

			nCnt++;
		}

		// �t�@�C�����N���A
		pLoad.reset();
		ranking_file.close();
		ranking_file.clear();
	}
	else
	{
		// ���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�t�@�C�����J������", "data/TXT/ranking.txt", MB_OK);
	}

	// �t�@�C�����J��
	ifstream result_file("data/TXT/result_score.txt");

	// �t�@�C�����J������
	if (result_file.is_open())
	{
		// �X�R�A��ǂݍ���
		result_file >> m_nResultScore;

		result_file.close();
		result_file.clear();
	}
	else
	{
		// ���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�t�@�C�����J������", "data/TXT/ranking.txt", MB_OK);
	}

	// �X�R�A�̃\�[�g
	Sort();

	// �����L���O�̐ݒ�
	SetRanking();

	// �Z�[�u
	Save();
}

//================================================
// �X�R�A�̃\�[�g
//================================================
void CRankingManager::Sort(void)
{
	// �Ō�̃X�R�A�Ɣ�r
	if (m_aScore[NUM_RANK - 1] < m_nResultScore)
	{
		m_aScore[NUM_RANK - 1] = m_nResultScore;
	}

	// �X�R�A���\�[�g����
	sort(m_aScore, m_aScore + NUM_RANK, greater<int>());

	// ���ʐ������ׂ�
	for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
	{
		// �X�R�A����v������
		if (m_aScore[nCnt] == m_nResultScore)
		{
			// �C���f�b�N�X�̎擾
			m_nUpdateScoreIdx = nCnt;
			break;
		}
	}
}

//================================================
// �X�R�A�̃Z�[�u����
//================================================
void CRankingManager::Save(void)
{
	// �t�@�C�����J��
	ofstream file("data/TXT/ranking.txt");

	// �t�@�C�����J������
	if (file.is_open())
	{
		// ���ʂ̐�����
		for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
		{
			file << m_aScore[nCnt] << "\n";
		}

		file.close();
		file.clear();
	}
}
