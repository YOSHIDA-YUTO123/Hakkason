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
class CCamera;

//*************************************************
// �v���C���[�N���X�̒�`
//*************************************************
class CPlayer : public CCharacter3D
{
public:

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

	D3DXVECTOR3 m_move; // �ړ���
};

#endif