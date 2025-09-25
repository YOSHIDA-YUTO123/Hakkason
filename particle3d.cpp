//****************************************************************
//
// 3Dparticle�̏���[particle3D.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "particle3d.h"
#include "effect3d.h"
#include "math.h"

// ���O���
using namespace Const;
using namespace math;

//*********************************************
// �R���X�g���N�^
//*********************************************
CParticle3D::CParticle3D()
{
	// �p�[�e�B�N���̏���������
	m_ParticleInfo = {};
}

//*********************************************
// �f�X�g���N�^
//*********************************************
CParticle3D::~CParticle3D()
{
}

//*********************************************
// ����������
//*********************************************
HRESULT CParticle3D::Init(void)
{
	return S_OK;
}

//*********************************************
// �I������
//*********************************************
void CParticle3D::Uninit(void)
{
	// �������g�̔j��
	Release();
}

//*********************************************
// �X�V����
//*********************************************
void CParticle3D::Update(void)
{
	// �J�E���^�[��i�߂�
	m_ParticleInfo.Bece.nCounter++;

	// �N�[���_�E���𒴂�����
	if (m_ParticleInfo.Bece.nCounter > m_ParticleInfo.Bece.nCoolDown)
	{
		// �������s���Ă��Ȃ�������A���[�v����ꍇ�Ȃ�
		if (m_ParticleInfo.Bece.nLife > 0 || m_ParticleInfo.Bece.bLoop == true)
		{
			// �w�肳�ꂽ��������
			for (int nCount = 0; nCount < m_ParticleInfo.Bece.nNumEffect; nCount++)
			{
				// ���������_���Ō��߂�
				int Life = rand() % m_ParticleInfo.Bece.nMaxLife + m_ParticleInfo.Bece.nMinLife;

				float Speed = math::Randf(m_ParticleInfo.Bece.fMaxSpeed, m_ParticleInfo.Bece.fMinSpeed);

				float fRadius = math::Randf(m_ParticleInfo.MaxRadius, m_ParticleInfo.MinRadius);

				float Gravity = m_ParticleInfo.Bece.Gravity;

				// �ړ��ʂ��v�Z
				D3DXVECTOR3 Move;
				Move = math::RandVec(m_ParticleInfo.Bece.MaxDir, m_ParticleInfo.Bece.MinDir);
				Move *= Speed;

				// �v���C�I���e�B���s���Ȓl��������f�t�H���g�ɌŒ�
				if (m_ParticleInfo.Bece.nPriority < 0 || m_ParticleInfo.Bece.nPriority > NUM_PRIORITY) m_ParticleInfo.Bece.nPriority = 3;

				// ����
				CEffect3D::Create(m_ParticleInfo.Bece.Pos, Move, m_ParticleInfo.Bece.Col, D3DXVECTOR2(fRadius, fRadius), Gravity, Life, m_ParticleInfo.Bece.FilePath,m_ParticleInfo.Bece.nPriority);
			}
		}
		else
		{
			// �������g�̔j��
			Uninit();
			// �����̐؂�グ
			return;
		}
		// �J�E���^�[�����Z�b�g�A���������炷
		m_ParticleInfo.Bece.nCounter = 0;
		m_ParticleInfo.Bece.nLife--;
	}
}

//*********************************************
// ����
//*********************************************
CParticle3D* CParticle3D::Create(DefoultEffectInfo ParticleInfo)
{
	CParticle3D* pParticle = NULL;
	// �������m��
	pParticle = new CParticle3D;
	// ����������
	pParticle->Init();
	// ���̐ݒ�
	pParticle->m_ParticleInfo = ParticleInfo;
	pParticle->m_ParticleInfo.Bece.nCounter = ParticleInfo.Bece.nCoolDown;
	return pParticle;
}