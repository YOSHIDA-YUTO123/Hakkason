//================================================
//
// �v���C���[�N���X [player.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "player.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "bullet.h"
#include "motion.h"
#include "debugproc.h"
#include "renderer.h"
#include "math.h"
#include "bulletmanager.h"

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p
using namespace math;  // ���O���math�̎g�p

//*************************************************
// �萔�錾
//*************************************************
const D3DXVECTOR3 SHADOW_SCAL = { 2.0f,2.0f,2.0f };		// �e�̃��f���̊g�嗦
const D3DXVECTOR3 PLAYER_SIZE = { 10.0f,100.0f,10.0f };	// �v���C���[�̑傫��
constexpr float INERTIA = 0.25f;						// �ړ�����
constexpr float BULLET_MOVE = 5.0f;						// �e�̑��x
constexpr int SHOT_COOLDOWN = 60;						// ���˃N�[���_�E��
constexpr int BULLET_LIFE = 60;							// �e�̎���

//=================================================
// �R���X�g���N�^
//=================================================
CPlayer::CPlayer()
{
	m_col = WHITE;
	m_fFlashTime = NULL;
	D3DXMatrixIdentity(&m_ShotMtx);
	m_nCoolDown = NULL;
	m_move = VEC3_NULL;
}

//=================================================
// �f�X�g���N�^
//=================================================
CPlayer::~CPlayer()
{
}

//=================================================
// ��������
//=================================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, const float fAngle)
{
	CPlayer* pPlayer = new CPlayer;

	pPlayer->SetPosition(pos);
	pPlayer->SetRotation(D3DXVECTOR3(0.0f, fAngle, 0.0f));

	// ����������
	if (FAILED(pPlayer->Init()))
	{
		pPlayer->Uninit();
		pPlayer = nullptr;
		return nullptr;
	}

	return pPlayer;
}

//=================================================
// ����������
//=================================================
HRESULT CPlayer::Init(void)
{
	// �L�����N�^�[�̐ݒ�
	CCharacter3D::SetCharacter(10, 1.5f, SHADOW_SCAL, PLAYER_SIZE);

	// ����������
	if (FAILED(CCharacter3D::Init()))
	{
		return E_FAIL;
	}

	// ���[�V�����̓ǂݍ���
	CCharacter3D::LoadMotion("player.txt", MOTIONTYPE_MAX);

	return S_OK;
}

//=================================================
// �I������
//=================================================
void CPlayer::Uninit(void)
{
	// �I������
	CCharacter3D::Uninit();
}

//=================================================
// �X�V����
//=================================================
void CPlayer::Update(void)
{
	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CCharacter3D::GetPosition();

	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// �W���C�p�b�h�̎擾
	CInputJoypad* pJoypad = CManager::GetInputJoypad();

	// ���[�V�����̎擾
	CMotion* pMotion = CCharacter3D::GetMotion();

	// ���[�V�������擾�ł��Ȃ������珈�����Ȃ�
	if (pMotion == nullptr) return;

	// ���[�h�Ɏ��s���Ă����珈�����Ȃ�
	if (!pMotion->IsLoad()) return;
	
	// ���[�V�����̎�ނ̎擾
	int nMotionType = pMotion->GetBlendType();

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// �L�[�{�[�h,�p�b�h�̈ړ�
		if ((MoveKeyboard(pKeyboard, pCamera) || MoveJoyPad(pJoypad, pCamera)) && nMotionType != MOTIONTYPE_ACTION)
		{
			// �ړ����[�V�����ɂ���
			pMotion->SetMotion(MOTIONTYPE_MOVE, true, 10);
		}
		else if (nMotionType == MOTIONTYPE_MOVE)
		{
			// �j���[�g�������[�V�����ɂ���
			pMotion->SetMotion(MOTIONTYPE_NEUTRAL, true, 10);
		}
	}

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * INERTIA;
	m_move.z += (0.0f - m_move.z) * INERTIA;

	// �ړ��ʂ̍X�V
	pos += m_move;

	// ���S�_����v���C���[�܂ł̃x�N�g��������
	D3DXVECTOR3 CircleVec = GetPosition() - VEC3_NULL;

	// �~�̑傫����ݒ�
	float Radius = 1500.0f;

	// �����蔻��
	if (D3DXVec3Length(&CircleVec) > Radius)
	{
		// ���S�_�܂ł̃x�N�g���A�����x�N�g��
		D3DXVECTOR3 PushPos, Dir;
		Dir = VEC3_NULL - GetPosition();
		// ���܂��������v�Z
		float VecLength = D3DXVec3Length(&Dir);
		// �����x�N�g�����v�Z
		D3DXVec3Normalize(&Dir, &Dir);
		float FillDist = VecLength - Radius;
		// �����߂��ʒu���v�Z
		PushPos = GetPosition() + (Dir * FillDist);
		// �����͍l�����Ȃ�
		PushPos.y = GetPosition().y;
		// �ʒu�������o����̈ʒu�ɐݒ�
		pos = PushPos;
	}

	// �p�x�̎擾
	float fRotY = CCharacter3D::GetRotation().y;

	// �e�̔��˂̍X�V����
	UpdateShotBullet(pMotion, pKeyboard, pJoypad, fRotY);

	// ���[�V�����̍X�V����
	CCharacter3D::UpdateMotion();

	// �X�V����
	CCharacter3D::Update();

	// �ʒu�̐ݒ�
	CCharacter3D::SetPosition(pos);

	if (pCamera != nullptr)
	{
		// �J�����̒Ǐ]
		pCamera->SetTracking(pos, pos, 0.1f);
	}

#ifdef _DEBUG

	// �f�o�b�O���
	Debug(pKeyboard);
#endif // _DEBUG

}

//=================================================
// �`�揈��
//=================================================
void CPlayer::Draw(void)
{
	if (CCharacter3D::GetState() != STATE_DAMAGE)
	{
		// �`�揈��
		CCharacter3D::Draw();
	}
	else
	{
		m_fFlashTime += 0.1f;

		m_col.g = 1.0f - fabsf(sinf(m_fFlashTime));
		m_col.b = 1.0f - fabsf(sinf(m_fFlashTime));

		// �F�̐ݒ�
		CCharacter3D::Draw(m_col);
	}
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_ShotMtx);

	// �e�̈ʒu�A�����̐ݒ�
	D3DXVECTOR3 ParentRot = CCharacter3D::GetModelRot(MODEL_SHOTGUN);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, ParentRot.y, ParentRot.x, ParentRot.z);
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxRot);

	// �傫���̎擾
	D3DXVECTOR3 ParentSize = CCharacter3D::GetModelSize(MODEL_SHOTGUN);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, ParentSize.x * 0.5f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxTrans);

	// �e�̃}�g���b�N�X�̎擾
	mtxParent = CCharacter3D::GetParent(MODEL_SHOTGUN);

	// �e�̃��[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_ShotMtx, &m_ShotMtx, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_ShotMtx);
}

//=================================================
// �G�ɓ�������
//=================================================
void CPlayer::Hit(const int nDamage)
{
	if (CCharacter3D::GetState() != STATE_DAMAGE)
	{
		// �_���[�W���󂯂�
		CCharacter3D::Hit(nDamage);

		// ��Ԃ̕ύX
		CCharacter3D::SetState(STATE_DAMAGE, 60);
	}
}

//=================================================
// �f�o�b�O���
//=================================================
void CPlayer::Debug(CInputKeyboard* pKeyboard)
{
#ifdef _DEBUG

	D3DXVECTOR3 pos = CCharacter3D::GetPosition();

	CDebugProc::Print("********************************************\n");
	CDebugProc::Print("              �v���C���[���\n");
	CDebugProc::Print("********************************************\n");
	CDebugProc::Print("�v���C���[�̈ʒu = [ %.2f ] [ %.2f ] [ %.2f ]\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("�v���C���[�̗̑� = [ %d ]\n",CCharacter3D::GetLife());

	if (pKeyboard->GetTrigger(DIK_TAB))
	{

	}

#endif // _DEBUG

}

//=================================================
// �L�[�{�[�h�̈ړ�
//=================================================
bool CPlayer::MoveKeyboard(CInputKeyboard* pKeyboard, CCamera* pCamera)
{
	bool bMove = false;

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pCamera == nullptr) return false;

	// �ړ����x�̎擾
	float fSpeed = CCharacter3D::GetSpeed();

	// ���݂̖ړI�̊p�x�̎擾
	float fDestRotY = CCharacter3D::GetRotDest().y;

	// �J�����̌���
	D3DXVECTOR3 cameraRot = pCamera->GetRotaition();

	// �W���C�p�b�h�̎擾
	CInputJoypad* pJoyPad = CManager::GetInputJoypad();

	if (pJoyPad->GetJoyStickL())
	{
		return false;
	}

	if (pKeyboard->GetPress(DIK_A))
	{
		//�v���C���[�̈ړ�(��)
		if (pKeyboard->GetPress(DIK_W) == true)
		{
			m_move.x += sinf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;
			m_move.z += cosf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;

			// �ړI�̊p�x�̐ݒ�
			fDestRotY = cameraRot.y + D3DX_PI * 0.75f;

			bMove = true;
		}
		//�v���C���[�̈ړ�(��)
		else if (pKeyboard->GetPress(DIK_S))
		{
			m_move.x += sinf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;
			m_move.z += cosf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;

			// �ړI�̊p�x�̐ݒ�
			fDestRotY = cameraRot.y + D3DX_PI * 0.25f;

			bMove = true;
		}
		// �v���C���[�̈ړ�(��)
		else
		{
			m_move.z += sinf(cameraRot.y) * fSpeed;
			m_move.x -= cosf(cameraRot.y) * fSpeed;

			// �ړI�̊p�x�̐ݒ�
			fDestRotY = cameraRot.y + D3DX_PI * 0.5f;

			bMove = true;
		}
	}
	//�v���C���[�̈ړ�(�E)
	else if (pKeyboard->GetPress(DIK_D))
	{
		//�v���C���[�̈ړ�(��)
		if (pKeyboard->GetPress(DIK_W))
		{
			m_move.x += sinf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;
			m_move.z += cosf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;

			// �ړI�̊p�x�̐ݒ�
			fDestRotY = cameraRot.y - D3DX_PI * 0.75f;

			bMove = true;
		}
		//�v���C���[�̈ړ�(��)
		else if (pKeyboard->GetPress(DIK_S))
		{
			m_move.x += sinf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;
			m_move.z += cosf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;

			// �ړI�̊p�x�̐ݒ�
			fDestRotY = cameraRot.y - D3DX_PI * 0.25f;

			bMove = true;
		}
		// �v���C���[�̈ړ�(�E)
		else
		{
			m_move.z -= sinf(cameraRot.y) * fSpeed;
			m_move.x += cosf(cameraRot.y) * fSpeed;

			fDestRotY = cameraRot.y - D3DX_PI * 0.5f;

			bMove = true;
		}
	}
	//�v���C���[�̈ړ�(��)
	else if (pKeyboard->GetPress(DIK_W) == true)
	{
		m_move.x += sinf(cameraRot.y) * fSpeed;
		m_move.z += cosf(cameraRot.y) * fSpeed;

		fDestRotY = cameraRot.y + D3DX_PI;

		bMove = true;
	}
	//�v���C���[�̈ړ�(��)
	else if (pKeyboard->GetPress(DIK_S) == true)
	{
		m_move.x -= sinf(cameraRot.y) * fSpeed;
		m_move.z -= cosf(cameraRot.y) * fSpeed;

		fDestRotY = cameraRot.y;

		bMove = true;
	}

	// �ړI�̊p�x�̐ݒ�
	CCharacter3D::SetRotDest(D3DXVECTOR3(0.0f, fDestRotY, 0.0f));

	return bMove;
}

//=================================================
// �p�b�h�̈ړ�����
//=================================================
bool CPlayer::MoveJoyPad(CInputJoypad* pJoypad, CCamera* pCamera)
{
	bool bMove = false;

	XINPUT_STATE* pStick;

	pStick = pJoypad->GetJoyStickAngle();

	// �擾�ł��Ȃ������珈�����Ȃ�
	if (pCamera == nullptr) return false;

	// �J�����̌���
	D3DXVECTOR3 cameraRot = pCamera->GetRotaition();

	// L�X�e�B�b�N�̊p�x
	float LStickAngleY = pStick->Gamepad.sThumbLY;
	float LStickAngleX = pStick->Gamepad.sThumbLX;

	// �f�b�h�]�[��
	float deadzone = 32767.0f * 0.25f;

	// �X�e�B�b�N�̌X�����p�x�����߂�
	float magnitude = sqrtf((LStickAngleX * LStickAngleX) + (LStickAngleY * LStickAngleY));

	// �ړ����x�̎擾
	float fSpeed = CCharacter3D::GetSpeed();

	// ���݂̖ړI�̊p�x�̎擾
	float fDestRotY = CCharacter3D::GetRotDest().y;

	// ��������
	if (magnitude > deadzone)
	{
		bMove = true;

		// �A���O���𐳋K��
		float normalizeX = (LStickAngleX / magnitude);
		float normalizeY = (LStickAngleY / magnitude);

		// �v���C���[�̈ړ���
		float moveX = normalizeX * cosf(-cameraRot.y) - normalizeY * sinf(-cameraRot.y);
		float moveZ = normalizeX * sinf(-cameraRot.y) + normalizeY * cosf(-cameraRot.y);

		// �ړ��ʂ��X�e�B�b�N�̊p�x�ɂ���ĕύX
		float speedWk = fSpeed * ((magnitude - deadzone) / (32767.0f - deadzone));

		// �v���C���[�̈ړ�
		m_move.x += moveX * speedWk;
		m_move.z += moveZ * speedWk;

		// �v���C���[�̊p�x���ړ������ɂ���
		fDestRotY = atan2f(-moveX, -moveZ);
	}

	// �ړI�̊p�x�̐ݒ�
	CCharacter3D::SetRotDest(D3DXVECTOR3(0.0f, fDestRotY, 0.0f));

	return bMove;
}

//=================================================
// �e�̔��˂̍X�V����
//=================================================
void CPlayer::UpdateShotBullet(CMotion* pMotion,CInputKeyboard *pKeyboard,CInputJoypad *pJoypad,const float fAngleY)
{
	// �N�[���_�E�������������甭�˂ł���
	if (m_nCoolDown <= 0)
	{
		if (pKeyboard->GetPress(DIK_RETURN) || pJoypad->GetTriggerPress(pJoypad->JOYKEY_R2))
		{
			pMotion->SetMotion(MOTIONTYPE_ACTION, true, 5);
		}
	}
	else
	{
		m_nCoolDown--;
	}

	// �t���[���̔���
	if (pMotion->IsEventFrame(6, 6, MOTIONTYPE_ACTION))
	{
		// �N�[���_�E���̐ݒ�
		m_nCoolDown = SHOT_COOLDOWN;

		// ���˒n�_�̎擾
		D3DXVECTOR3 shotGunPos = GetPositionFromMatrix(m_ShotMtx);

		// �e�̐���
		CBulletManager::PushBackBullet(shotGunPos, VEC3_NULL,
			D3DXVECTOR3(sinf(fAngleY + D3DX_PI), 0.0f, cosf(fAngleY + D3DX_PI)), BULLET_MOVE, BULLET_LIFE);

		// �e�̐���
		CBulletManager::PushBackBullet(shotGunPos, VEC3_NULL,
			D3DXVECTOR3(sinf(fAngleY + D3DX_PI * 1.05f), 0.0f, cosf(fAngleY + D3DX_PI * 1.05f)), BULLET_MOVE, BULLET_LIFE);

		// �e�̐���
		CBulletManager::PushBackBullet(shotGunPos, VEC3_NULL,
			D3DXVECTOR3(sinf(fAngleY - D3DX_PI * 1.05f), 0.0f, cosf(fAngleY - D3DX_PI * 1.05f)), BULLET_MOVE, BULLET_LIFE);
	}
}
