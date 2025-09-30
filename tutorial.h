//****************************************************************
//
// �`���[�g���A���̏���[tutorial.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

// �C���N���[�h
#include "scene.h"

// �O���錾
class CPlayer;
class CMapEditer;
class CPauseManager;

// �`���[�g���A���N���X���`
class CTutorial : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTutorial();
	~CTutorial();

	// �I�[�o�[���C�h���ꂽ�����o�֐�
	HRESULT Init(void)	override;
	void Update(void)	override;
	void Uninit(void)	override;
	void Draw(void)		override;
private:
};
#endif // !_TUTORIAL_H_