//===================================================
//
// �Q�[���V�[�� [game.h]
// Author:YUTO YOSHIDA
//
//===================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _GAME_H_
#define _GAME_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include"main.h"
#include "scene.h"
#include<memory>
#include<string>

//***************************************************
// �O���錾
//***************************************************
class CMeshField;
class CPlayer;
class CMeshCylinder;
class CPauseManager;
class CGameCamera;
class CLoadManager;
class CEnemy;
class CPlayer;
class CDualUnitTimer;

//***************************************************
// �Q�[���N���X�̒�`
//***************************************************
class CGame : public CScene
{
public:

	// �Q�[���̏��
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_ENEMY_DEATH,
		STATE_END,
		STATE_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	static void SetState(const STATE state) { m_state = state; }
	// �Q�b�^�[
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static STATE GetState(void) { return m_state; }
private:
	static CPlayer* m_pPlayer;			// �v���C���[�̃C���X�^���X
	static CDualUnitTimer* m_pTimer;	// �^�C�}�[�̃C���X�^���X
	static STATE m_state;				// �Q�[���̏��
	int m_nScore;				// �X�R�A
	int m_nCounterState;				// ��ԃJ�E���^�[
};

#endif

