//****************************************************************
//
// �G�t�F�N�g�̂̏���[effect3D.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

// �C���N���[�h
#include "billboard.h"

// 3D�G�t�F�N�g�̃N���X���`
class CEffect3D : public CObjectBillboard
{
public:
	// �G�t�F�N�g�̋���
	struct EffectModule {
		// �����o�ϐ�
		D3DXVECTOR3 Move;		// �ړ���
		D3DXCOLOR Col;			// �F
		float fGravity;			// �d��
		float fAlphaDef;		// 1�t���[���Ō���A���t�@�l
		float fSizeDefX;		// 1�t���[���Ō���傫��X
		float fSizeDefY;		// 1�t���[���Ō���傫��Y
		int nLife;				// ����
		const char* FilePath;	// �e�N�X�`���ւ̃p�X
	};

	// �e�N�X�`���̃p�X��ݒ�
	struct Config {
		static constexpr const char* Sphere = "Effect\\effect000.jpg";
		static constexpr const char* Smoke = "Effect\\smoke.jpg";
	};
	// �R���X�g���N�^�E�f�X�g���N�^
	CEffect3D(const int Priority = 3);
	~CEffect3D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	// ����
	static CEffect3D* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXCOLOR Col, D3DXVECTOR2 Size, float Gravity, int Life, const char* FilePath,const int Priority = 3);
private:
	// �����o�ϐ�
	EffectModule m_Module;	// ���W���[��
};
#endif // !_EFFECT3D_H_