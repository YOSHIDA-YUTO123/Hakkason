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

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p

//*************************************************
// �萔�錾
//*************************************************
const D3DXVECTOR3 SHADOW_SCAL = { 1.0f,1.0f,1.0f };		// �e�̃��f���̊g�嗦
const D3DXVECTOR3 PLAYER_SIZE = { 10.0f,100.0f,10.0f };	// �v���C���[�̑傫��
constexpr float INERTIA = 0.25f;						// �ړ�����

//=================================================
// �R���X�g���N�^
//=================================================
CPlayer::CPlayer()
{
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
	// ����������
	if (FAILED(CCharacter3D::Init()))
	{
		return E_FAIL;
	}

	// �L�����N�^�[�̐ݒ�
	CCharacter3D::SetCharacter(10, 5.0f, SHADOW_SCAL, PLAYER_SIZE);

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

	// �ړ��ʂ̌���
	m_move.x += (0.0f - m_move.x) * INERTIA;
	m_move.z += (0.0f - m_move.z) * INERTIA;

	// �ړ��ʂ̍X�V
	pos += m_move;

	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();

	// �p�x�̎擾
	float fRotY = CCharacter3D::GetRotation().y;

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

	if (pKeyboard->GetTrigger(DIK_1))
	{
		CBullet::Create(VEC3_NULL, D3DXVECTOR3(0.0f, fRotY, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 2.0f);
	}
}

//=================================================
// �`�揈��
//=================================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter3D::Draw();
}

////=================================================
//// �L�[�{�[�h�̈ړ�
////=================================================
//bool CPlayer::MoveKeyboard(CInputKeyboard* pKeyboard, CCamera* pCamera)
//{
//	bool bMove = false;
//
//	// �擾�ł��Ȃ������珈�����Ȃ�
//	if (pCamera == nullptr) return false;
//
//	// �ړ����x�̎擾
//	float fSpeed = CCharacter3D::GetSpeed();
//
//	float fDestRotY = 
//	// �J�����̌���
//	D3DXVECTOR3 cameraRot = pCamera->GetRotaition();
//
//	// �W���C�p�b�h�̎擾
//	CInputJoypad* pJoyPad = CManager::GetInputJoypad();
//
//	if (pJoyPad->GetJoyStickL())
//	{
//		return false;
//	}
//
//	if (pKeyboard->GetPress(DIK_A))
//	{
//		//�v���C���[�̈ړ�(��)
//		if (pKeyboard->GetPress(DIK_W) == true)
//		{
//			m_move.x += sinf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;
//			m_move.z += cosf(cameraRot.y - D3DX_PI * 0.25f) * fSpeed;
//
//			*pRotDest = cameraRot.y + D3DX_PI * 0.75f;
//
//			bMove = true;
//		}
//		//�v���C���[�̈ړ�(��)
//		else if (pKeyboard->GetPress(DIK_S))
//		{
//			move.x += sinf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;
//			move.z += cosf(cameraRot.y - D3DX_PI * 0.75f) * fSpeed;
//
//			*pRotDest = cameraRot.y + D3DX_PI * 0.25f;
//
//			bMove = true;
//		}
//		// �v���C���[�̈ړ�(��)
//		else
//		{
//			move.z += sinf(cameraRot.y) * fSpeed;
//			move.x -= cosf(cameraRot.y) * fSpeed;
//
//			*pRotDest = cameraRot.y + D3DX_PI * 0.5f;
//
//			bMove = true;
//		}
//	}
//	//�v���C���[�̈ړ�(�E)
//	else if (pKeyboard->GetPress(DIK_D))
//	{
//		//�v���C���[�̈ړ�(��)
//		if (pKeyboard->GetPress(DIK_W))
//		{
//			move.x += sinf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;
//			move.z += cosf(cameraRot.y + D3DX_PI * 0.25f) * fSpeed;
//
//			*pRotDest = cameraRot.y - D3DX_PI * 0.75f;
//
//			bMove = true;
//		}
//		//�v���C���[�̈ړ�(��)
//		else if (pKeyboard->GetPress(DIK_S))
//		{
//			move.x += sinf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;
//			move.z += cosf(cameraRot.y + D3DX_PI * 0.75f) * fSpeed;
//
//			*pRotDest = cameraRot.y - D3DX_PI * 0.25f;
//
//			bMove = true;
//		}
//		// �v���C���[�̈ړ�(�E)
//		else
//		{
//			move.z -= sinf(cameraRot.y) * fSpeed;
//			move.x += cosf(cameraRot.y) * fSpeed;
//
//			*pRotDest = cameraRot.y - D3DX_PI * 0.5f;
//
//			bMove = true;
//		}
//	}
//	//�v���C���[�̈ړ�(��)
//	else if (pKeyboard->GetPress(DIK_W) == true)
//	{
//		move.x += sinf(cameraRot.y) * fSpeed;
//		move.z += cosf(cameraRot.y) * fSpeed;
//
//		*pRotDest = cameraRot.y + D3DX_PI;
//
//		bMove = true;
//	}
//	//�v���C���[�̈ړ�(��)
//	else if (pKeyboard->GetPress(DIK_S) == true)
//	{
//		move.x -= sinf(cameraRot.y) * fSpeed;
//		move.z -= cosf(cameraRot.y) * fSpeed;
//
//		*pRotDest = cameraRot.y;
//
//		bMove = true;
//	}
//
//	// �ړ��ʂ̐ݒ�
//	m_pMove->Set(move);
//
//	return bMove;
//}
