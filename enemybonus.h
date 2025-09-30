//===================================================
//
// �{�[�i�X�G [enemybonus.h]
// Author:YUTO YOSHIDA
//
//===================================================

// ��d�C���N���[�h
#ifndef _ENEMYBONUS_H_
#define _ENEMYBONUS_H_

// �C���N���[�h
#include "enemy.h"

// ���G�N���X��h��
class CEnemyBonus : public CEnemy
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyBonus();
	~CEnemyBonus();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemyBonus* Create(D3DXVECTOR3 Pos);
private:
	int m_nTimer;	// ��������
};
#endif // !_ENEMYNEEDLE_H_