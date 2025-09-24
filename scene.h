//===================================================
//
// �V�[��(���N���X) [scene.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include"main.h"

//***************************************************
// �V�[���N���X�̒�`
//***************************************************
class CScene
{
public:

	// ���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g�����
		MODE_EDIT,		// �ҏW
		MODE_TUTORIAL,	// �`���[�g���A�����
		MODE_OPENING,	// ���ꃀ�[�r�[
		MODE_GAME,		// �Q�[�����
		MODE_RESULT,	// ���U���g���
		MODE_RANKING,	// �����L���O���
		MODE_MAX
	}MODE;

	CScene(MODE mode);
	virtual ~CScene();

	MODE GetMode(void) const { return m_mode; }
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

private:
	MODE m_mode; // ���[�h
};
#endif