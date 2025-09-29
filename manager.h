//===================================================
//
// �}�l�[�W���[ [manager.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "main.h"
#include<memory>
#include"scene.h"

//***************************************************
// �O���錾
//***************************************************
class CRenderer;
class CScene;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CLight;
class CFade;
class CSlow;
class CCamera;

//***************************************************
// �}�l�[�W���[�N���X�̒�`
//***************************************************
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFps(const int fps) { m_fps = fps; }

	static CRenderer* GetRenderer(void) { return m_pRenderer.get(); }
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard.get(); }
	static CInputJoypad* GetInputJoypad(void) { return m_pInputJoypad.get(); }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse.get(); }
	static CSound* GetSound(void) { return m_pSound.get(); }
	static CFade* GetFade(void) { return m_pFade.get(); }
	static CSlow* GetSlow(void) { return m_pSlow.get(); }
	static CLight* GetLight(void) { return m_pLight.get(); }
	static CCamera* GetCamera(void) { return m_pCamera.get(); }
	static int GetFrameCounter(void);
	static bool GetShowDebug(void) { return m_bShowDebug; }
	static void SetMode(std::unique_ptr<CScene> pNewScene);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); }
	static void DrawScene(void);
private:
	static std::unique_ptr<CRenderer> m_pRenderer;				// �����_���[�̃|�C���^
	static std::unique_ptr<CInputKeyboard> m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static std::unique_ptr<CInputJoypad> m_pInputJoypad;		// �p�b�h�̃|�C���^
	static std::unique_ptr<CInputMouse> m_pInputMouse;			// �}�E�X�̃|�C���^
	static std::unique_ptr<CSound> m_pSound;					// �T�E���h�̃|�C���^
	static std::unique_ptr<CLight> m_pLight;					// ���C�g�ւ̃|�C���^
	static std::unique_ptr<CScene> m_pScene;					// �V�[���̃N���X�ւ̃|�C���^
	static std::unique_ptr<CSlow> m_pSlow;						// �X���[���[�V�����N���X�ւ̃|�C���^
	static std::unique_ptr<CFade> m_pFade;						// �t�F�[�h�N���X�ւ̃|�C���^
	static std::unique_ptr<CCamera> m_pCamera;					// �J�����N���X�ւ̃|�C���^
	static int m_nFrameCounter;									// �t���[���J�E���^�[
	static bool m_bShowDebug;									// �f�o�b�O�\�������邩���Ȃ���
	int m_fps;													// fps�i�[�p�ϐ�
};
#endif