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

// �G�̊��N���X���`
class CEnemy : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemy();
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
	D3DXVECTOR3 m_Move;	// �ړ���
	int m_nLife;		// �̗�
};
#endif // !_ENEMY_H_