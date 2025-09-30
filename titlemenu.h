//****************************************************************
//
// �^�C�g�����j���[�̏���[titlemenu.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��d�C���N���[�h�h�~
#ifndef _TITLEMENU_H_
#define _TITLEMENU_H_

// �C���N���[�h
#include "object2D.h"

// �^�C�g�����j���[�̊��N���X���`
class CTitleMenu : public CObject2D
{
public:
	// �|�[�Y�̋K��l��ݒ�
	struct Config {
		static const D3DXCOLOR SelectColor;		// �I��ł��鎞�̐F
		static const D3DXCOLOR DefoultColor;	// �ʏ�̐F
	};

	// ���j���[�̗񋓌^
	typedef enum
	{
		START = 0,	// �X�^�[�g(�n�߂�)
		EXIT,		// �C�O�W�b�g(��߂�)
		MAX
	}Menu;

	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleMenu();
	~CTitleMenu();

	// ���z�֐�
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	// �ÓI�����o�֐�
	// ����
	static CTitleMenu* Create(D3DXVECTOR3 Pos, Menu Menu);
protected:
	int m_nAnimCounter;		// �J�E���^�[
};

// �X�^�[�g���j���[�N���X���`
class CStart : public CTitleMenu
{
public:
	// �|�[�Y���j���[�̋K��l��ݒ�
	struct Config {
		static constexpr const char* FilePath = "data\\TEXTURE\\Title\\Start.png";	// �p�X
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CStart();
	~CStart();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
private:
};

// Exit���j���[�N���X���`
class CExit : public CTitleMenu
{
public:
	// �|�[�Y���j���[�̋K��l��ݒ�
	struct Config {
		static constexpr const char* FilePath = "data\\TEXTURE\\Title\\Exit.png";	// �p�X
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CExit();
	~CExit();

	// �I�[�o�[���C�h���ꂽ�֐�
	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
private:
};
#endif // !_TITLEMENU_H_