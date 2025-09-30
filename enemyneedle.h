//===================================================
//
// ���G [enemyneedle.h]
// Author:YUTO YOSHIDA
//
//===================================================

#ifndef _ENEMYNEEDLE_H_
#define _ENEMYNEEDLE_H_

// �C���N���[�h
#include "enemy.h"

// ���G�N���X��h��
class CEnemyNeedle : public CEnemy
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemyNeedle();
	~CEnemyNeedle();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemyNeedle* Create(D3DXVECTOR3 Pos);
private:
};
#endif // !_ENEMYNEEDLE_H_