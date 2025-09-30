//================================================
//
// �����L���O�}�l�[�W���[ [RankingManager.h]
// Author: YUTO YOSHIDA
// 
// << �����L���O�̃X�R�A�̓ǂݍ��݁A�\�[�g�A>>
// << �����o���A�������s��					>>
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object.h"

//*************************************************
// �����L���O�}�l�[�W���[�̃N���X�̒�`
//*************************************************
class CRankingManager : public CObject
{
public:
	~CRankingManager();

	static void Create(void);
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	CRankingManager();
	void Load(void);
	void Sort(void);
	void Save(void);
	void SetRanking(void);

	static constexpr int NUM_RANK = 5; // �����L���O�̏��ʂ̐�
	int m_aScore[NUM_RANK];			   // �����L���O�̃X�R�A
	int m_nResultScore;				   // ���U���g�̃X�R�A
	int m_nUpdateScoreIdx;			   // �X�V���郉���L���O�X�R�A�C���f�b�N�X
};
#endif
