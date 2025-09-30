//================================================
//
// �v���C���[�N���X [player.h]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "character3D.h"

//*************************************************
// �O���錾
//*************************************************
class CInputKeyboard;
class CMotion;
class CInputJoypad;
class CCamera;

//*************************************************
// �v���C���[�N���X�̒�`
//*************************************************
class CPlayer : public CCharacter3D
{
public:

	// �v���C���[�̃��f��
	typedef enum
	{
		MODEL_BODY = 0, // ��
		MODEL_HEAD,		// ��
		MODEL_ARMR,		// �E�r
		MODEL_HANDR,	// �E��
		MODEL_ARML,		// ���r
		MODEL_HANDL,	// ����
		MODEL_LEGR,		// �E������
		MODEL_FOOTR,	// �E��
		MODEL_LEGL,		// ��������
		MODEL_FOOTL,	// ����
		MODEL_SHOTGUN,	// �e
		MODEL_MAX
	}MODEL;
	// ���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0, // �j���[�g����
		MOTIONTYPE_MOVE,		// �ړ�
		MOTIONTYPE_ACTION,		// �U��
		MOTIONTYPE_JUMP,		// �W�����v
		MOTIONTYPE_LANDING,		// ���n���[�V����
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	CPlayer();
	~CPlayer();

	static CPlayer* Create(const D3DXVECTOR3 pos, const float fAngle);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	void Debug(CInputKeyboard* pKeyboard);
	bool MoveKeyboard(CInputKeyboard* pKeyboard, CCamera* pCamera);
	bool MoveJoyPad(CInputJoypad* pJoypad, CCamera* pCamera);
	void UpdateShotBullet(CMotion* pMotion, CInputKeyboard* pKeyboard, CInputJoypad* pJoypad, const float fAngleY);

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXMATRIX m_ShotMtx;	// ���˒n�_�̃}�g���b�N�X
	int m_nCoolDown;		// ���˂̃N�[���_�E��
};

#endif