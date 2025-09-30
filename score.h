//================================================
//
// �X�R�A��\�����鏈�� [score.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _SCORE_H_
#define _SCORE_H_

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "object.h"
#include <memory>

//*************************************************
// �O���錾
//*************************************************
class CNumber;

//*************************************************
// �X�R�A�N���X�̒�`
//*************************************************
class CScore : public CObject
{
public:
	CScore();
	~CScore();

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="�ʒu"></param>
	/// <param name="�傫��(�S�̂̑傫��)"></param>
	/// <param name="�X�R�A"></param>
	/// <param name="0��\�����邩�ǂ���"></param>
	/// <returns>�����̃C���X�^���X</returns>
	static CScore* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nScore, const bool bShowZero = false);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	int GetScore(void) const { return m_nScore; }
	void AddScore(const int nAdd) { m_nScore += nAdd; }
private:
	static constexpr int MAX_DIGIT = 8; // �X�R�A�̌���

	std::unique_ptr<CNumber> m_apNumber[MAX_DIGIT];		// �i���o�[�N���X�ւ̃|�C���^
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR2 m_Size;									// �傫��
	int m_nScore;										// �X�R�A
	int m_nDigit;										// ����
	bool m_bShowZero;									// ����Ȃ�0�������邩�ǂ���
};

#endif