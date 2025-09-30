//================================================
//
// ���ƕb�������^�C�}�[�̃N���X�̏��� [DualUnitTimer.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _DUALUNITTER_H_
#define _DUALUNITTER_H_

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "timer.h"

//*************************************************
// ���ƕb�̃^�C�}�[�̃N���X�̒�`
//*************************************************
class CDualUnitTimer : public CTimer
{
public:
	CDualUnitTimer();
	~CDualUnitTimer();

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="�ʒu"></param>
	/// <param name="�傫��"></param>
	/// <param name="����"></param>
	/// <returns>�����̃C���X�^���X</returns>
	static CDualUnitTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	int GetTimer(void) const { return m_nCurrentTime; }
private:
	CTimer* m_pMinute; // �^�C�}�[�N���X�ւ̃|�C���^(��)
	int m_nCurrentTime;// ���݂̎���
	int m_nCounter;	   // �J�E���^�[
};

#endif
