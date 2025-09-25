//****************************************************************
//
// 3Dparticle�̏���[particle3D.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

// �C���N���[�h
#include "object.h"

// 3Dparticle�N���X���`
class CParticle3D : public CObject
{
public:
	// �f�t�H���gparticle�̍\����
	struct BaceEffectInfo
	{
		D3DXVECTOR3 MaxDir;				// ���̕����̕����x�N�g��
		D3DXVECTOR3 MinDir;				// ���̕����x�N�g��
		D3DXVECTOR3 Pos;				// �ʒu
		D3DXCOLOR Col;					// �F
		float fMaxSpeed, fMinSpeed;		// particle�̑���
		float Gravity;					// particle�̏d��
		int nNumEffect;					// �G�t�F�N�g�̐�
		int nMaxLife,nMinLife;			// particle�G�t�F�N�g�̎���
		int nLife;						// particle�̎���
		int nCoolDown;					// �N�[���_�E��
		int nCounter;					// �o�����Ă���̃J�E���^
		int nPriority = 3;				// �`�揇
		bool bLoop;						// ���[�v���邩
		const char* FilePath;			// �e�N�X�`���p�X
	};

	// �f�t�H���gparticle�̍\����
	struct DefoultEffectInfo
	{
		BaceEffectInfo Bece;	// ��Ղ̃G�t�F�N�g�̏��
		float MaxRadius;		// particle�̍ő�̑傫��
		float MinRadius;		// particle�̍ŏ��̑傫��
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CParticle3D();
	~CParticle3D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

	// �ÓI�����o�֐�
	// ����
	static CParticle3D* Create(DefoultEffectInfo ParticleInfo);
private:
	// �����o�ϐ�
	DefoultEffectInfo m_ParticleInfo;
};

// 3Dparticle�N���X���`
class CZoneParticle3D : public CObject
{
public:
	// �f�t�H���gparticle�̍\����
	struct ZoneEffectInfo
	{
		CParticle3D::DefoultEffectInfo ParticleInfo;	// ��{�ƂȂ�G�t�F�N�g�̏��
		D3DXVECTOR3 DestPos;							// �ڕW�̈ʒu
		float fMaxRadius, fMinRadius;					// ���a
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CZoneParticle3D();
	~CZoneParticle3D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

	// �ÓI�����o�֐�
	// ����
	static CZoneParticle3D* Create(ZoneEffectInfo ParticleInfo);
private:
	// �����o�ϐ�
	ZoneEffectInfo m_ParticleInfo;
};
#endif // !_PARTICLE_H_