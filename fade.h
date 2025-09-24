//===================================================
//
// �t�F�[�h���� [fade.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _FADE_H_
#define _FADE_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include<memory>

//***************************************************
// �O���錾
//***************************************************
class CScene;

//***************************************************
// �t�F�[�h�N���X�̒�`
//***************************************************
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,			// �t�F�[�h�Ȃ��̏��
		FADE_IN,				// �t�F�[�h�C���̏��
		FADE_OUT,				// �t�F�[�h�A�E�g�̏��
		FAFE_MAX
	}FADE;

	~CFade();

	static CFade* Create(void);
	void SetFade(std::unique_ptr<CScene> pNewScene,const D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	FADE GetState(void) const { return m_Fade; }

private:
	CFade();
	std::unique_ptr<CScene> m_pScene;		// �V�[���̃|�C���^
	FADE m_Fade;							// �t�F�[�h
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;   // ���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_col;						// �t�F�[�h�̐F
};

#endif
