//===================================================
//
// �^�C�g���V�[�� [title.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "scene.h"

class CTitleManager;

//***************************************************
// �^�C�g���V�[���N���X�̒�`
//***************************************************
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	static CTitleManager* m_pTitleManager;		// �|�[�Y�}�l�[�W���[�ւ̃|�C���^
};

#endif