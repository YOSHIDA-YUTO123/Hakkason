//================================================
//
// �����L���O�̃X�R�A��`�悷�� [RankingScore.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object2D.h"

//************************************************
// �O���錾
//************************************************
class CNumber;

//************************************************
// �����L���O�̃X�R�A�̕\��
//************************************************
class CRankingScore : public CObject
{
public:
	CRankingScore();
	~CRankingScore();

	static CRankingScore* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nScore, const bool bHilight);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	static constexpr int MAX_DIGIT = 8; // �ő�̌���

	CNumber* m_apNumber[MAX_DIGIT];		// �i���o�[�N���X�̒�`
	D3DXCOLOR m_col;					// �F
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR2 m_Size;					// �傫��
	D3DXVECTOR2 m_DestSize;				// �ړI�̑傫��
	int m_nScore;						// �X�R�A
	int m_nDestScore;					// �ړI�̒l
	float m_fCounter;					// �J�E���^�[
	bool m_bHilight;					// �����\�����邩�ǂ���
};

#endif
