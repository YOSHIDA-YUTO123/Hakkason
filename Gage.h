//================================================
//
// �Q�[�W [gage.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _GAGE_H_
#define _GAGE_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object2D.h"
#include<memory>

//************************************************
// �O���錾
//************************************************
template <class T>
class CObserver;
class CTemporaryGage;

//************************************************
// �Q�[�W�N���X�̒�`
//************************************************
class CGage : public CObject2D
{
public:
	CGage(int nPriority = 6);
	~CGage();

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override = 0; // �h���N���X�Ŏ���
	virtual void Draw(void) override;
private:
};

//************************************************
// HP�Q�[�W�N���X�̒�`
//************************************************
class CHpGage : public CGage
{
public:
	CHpGage();
	~CHpGage();

	static CHpGage* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const D3DXCOLOR col,const D3DXCOLOR temporaryColor, const int nLife, const bool bDecRightToLeft);
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetHp(const int nLife) { m_nLife = nLife; }
private:
	CTemporaryGage* m_pTemporary;	// �ꎞ�I�ȃQ�[�W
	int m_nMaxLife;					// �ő��HP
	int m_nLife;					// HP
	bool m_bDecRightToLeft;			// �E���獶�Ɍ��邩����
};

//************************************************
// �_���[�W���̈ꎞ�I�ȃQ�[�W�̐���
//************************************************
class CTemporaryGage : public CGage
{
public:
	CTemporaryGage(int nPriority = 5);
	~CTemporaryGage();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetLength(const float fLength) { m_fDestLength = fLength; }
	void SetGage(const D3DXVECTOR2 Size, const bool bDecRightToLeft);
private:
	float m_fDestLength;	 // �ړI�̒���
	float m_fLength;		 // ����
	bool m_bDecRightToLeft;  // �E���獶�Ɍ��邩����
};

//************************************************
// �X�^�~�i�Q�[�W�N���X�̒�`
//************************************************
class CStaminaGage : public CGage
{
public:
	CStaminaGage();
	~CStaminaGage();

	static CStaminaGage* Create(const D3DXVECTOR3 pos, D3DXVECTOR2 Size, const D3DXCOLOR col, const float fStamina);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Set(const float fStamina) { m_fStamina = fStamina; } // �X�^�~�i�Q�[�W�̐ݒ菈��
private:
	float m_fMaxStamina;	// �ő�̃X�^�~�i
	float m_fStamina;		// ���݂̃X�^�~�i
};
#endif
