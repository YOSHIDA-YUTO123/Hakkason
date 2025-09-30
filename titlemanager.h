//****************************************************************
//
// �^�C�g���}�l�W���[�̏���[titlemanager.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

// �C���N���[�h
#include "object.h"
#include "titlemenu.h"
#include "titlelogo.h"

// �^�C�g���}�l�[�W���[�̃N���X���`
class CTitleManager : public CObject
{
public:
	// �|�[�Y���j���[�̋K��l��ݒ�
	struct Config {
		// ���j���[�̋K��l��ݒ�
		struct Menu {
			static const D3DXVECTOR3 Bace;				// ���S�̊�ƂȂ�ʒu
			static constexpr float OffSet = 100.0f;		// ���j���[�̌���
			static constexpr float Width = 100.0f;		// ����
			static constexpr float Height = 100.0f;		// ����
			static constexpr float DestWidth = 150.0f;	// ����
			static constexpr float DestHeight = 150.0f;	// ����
			static constexpr int Frame = 30;			// �t���[��
		};
		// ���S�̋K��l��ݒ�
		struct Logo {
			static const D3DXVECTOR3 Apper;													// �����ʒu
			static const D3DXVECTOR3 Dest;													// �ڕW
			static const D3DXVECTOR2 Size;													// �傫��
			static constexpr int AnimFrame = 60;											// �A�j���[�V�����t���[��
			static constexpr const char* FilePath = "data\\TEXTURE\\Title\\TitleLogo.png";	// �e�N�X�`���̃p�X
		};
	};

	// �f�X�g���N�^
	~CTitleManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {};

	// �Z�b�^�[
	void SetMenu(CTitleMenu::Menu Menu) { m_SelectMenu = Menu; };

	// �Q�b�^�[
	CTitleMenu::Menu GetSelectMenu(void) { return m_SelectMenu; };
	CTitleLogo* GetTitleLogo(void) { return m_TitleLogo; };

	// �ÓI�����o�֐�
	// �Q�b�^�[
	static CTitleManager* GetSingleton(void) { return m_Singleton; };
	static bool GetLower(void) { return m_Singleton->GetTitleLogo()->GetLower(); };
	// ����
	static CTitleManager* CreateSingleton(void);
private:
	// �R���X�g���N�^
	CTitleManager() {};

	// �ÓI�����o�ϐ�
	static CTitleManager* m_Singleton;		// �V���O���g��
	CTitleLogo* m_TitleLogo;				// �^�C�g�����S
	std::vector<CTitleMenu*> m_apTitleMenu;	// �|�[�Y���j���[
	CTitleMenu::Menu m_SelectMenu;			// �I��ł��郁�j���[
};
#endif // !_TITLEMANAGER_H_