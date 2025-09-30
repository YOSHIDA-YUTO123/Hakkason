//****************************************************************
//
// �^�C�g�����S�̏���[titlelogo.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

// �C���N���[�h
#include "object2D.h"

// �^�C�g�����S�N���X���`
class CTitleLogo : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleLogo();
	~CTitleLogo();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Lower(void);

	// �Q�b�^�[
	bool GetLower(void);

	// �ÓI�����o�֐�
	// ����
	static CTitleLogo* Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR2 Size, const char* FilePath);
private:
	int m_nFrameCounter;	// �t���[�����J�E���g
};
#endif // !_TITLELOGO_H_