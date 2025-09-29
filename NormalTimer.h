//================================================
//
// ���ʂ̃^�C�}�[��\�����鏈�� [NormalTimer.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _NORMALTIMER_H_
#define _NORMALTIMER_H_

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "timer.h"

//*************************************************
// ���ʂ̃^�C�}�[�N���X�̒�`
//*************************************************
class CNormalTimer : public CTimer
{
public:
	CNormalTimer();
	~CNormalTimer();

	static CNormalTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	int m_nCounter;	// �J�E���^�[
};

#endif
