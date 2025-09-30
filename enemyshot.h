//===================================================
//
// �ł��Ă���G [enemyshot.h]
// Author:YUTO YOSHIDA
//
//===================================================

// ��d�C���N���[�h
#ifndef _ENEMYSHOT_H_
#define _ENEMYSHOT_H_

// �C���N���[�h
#include "enemy.h"

// ���G�N���X��h��
class CEnemyShot : public CEnemy
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyShot();
	~CEnemyShot();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemyShot* Create(D3DXVECTOR3 Pos);
private:
};
#endif // !_ENEMYNEEDLE_H_