//================================================
//
// �^�C�}�[��\�����鏈��(���N���X) [timer.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _TIMER_H_
#define _TIMER_H_

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
// �^�C�}�[�N���X�̒�`
//*************************************************
class CTimer : public CObject
{
public:
	CTimer();
	~CTimer();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;
	void SetTexture(const char* pTexturePath);

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR2 GetSize(void) const { return m_Size; }
	void SetTime(const int nTime) { m_nTime = nTime; }

	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR2 Size) { m_Size = Size; }
	int GetTime(void) const { return m_nTime; }

protected:
	static constexpr int MAX_DIGIT = 2;				// �ő�̌���

	CNumber* GetNumber(const int nIdx);

private:

	std::unique_ptr<CNumber> m_apNumber[MAX_DIGIT]; // �i���o�[�N���X�̒�`
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR2 m_Size;								// �傫��
	int m_nTime;									// ����
};

#endif
