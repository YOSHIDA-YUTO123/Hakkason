//================================================
//
// �G [enemy.h]
// Author: KENSAKU HATORI
//
//================================================

// ��d�C���N���[�h�h�~
#ifndef _ENEMY_H_
#define _ENEMY_H_

// �C���N���[�h
#include "objectX.h"
#include <string>
#include <memory>

// �O���錾
class CShadow;

// �G�̊��N���X���`
class CEnemy : public CObjectX
{
public:

	typedef enum
	{
		TYPE_ONE = 0,
		TYPE_TWO,
		TYPE_THREE,
		TYPE_FOUR,
		TYPE_MAX
	}TYPE;

	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemy();
	CEnemy(const TYPE type);
	~CEnemy();

	// �����o�֐�
	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	void SetDamage(const int nDamage) { m_nLife -= nDamage; }

	// �Z�b�^�[
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }

	// �Q�b�^�[
	D3DXVECTOR3 GetMove(void) { return m_Move; }
private:
	std::unique_ptr<CShadow> m_pShadow; // �e�̃N���X�ւ̃|�C���^
	D3DXVECTOR3 m_Move;	// �ړ���
	TYPE m_type;		// ���
	int m_nLife;		// �̗�
};
#endif // !_ENEMY_H_