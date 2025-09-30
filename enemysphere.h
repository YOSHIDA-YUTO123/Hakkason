//================================================
//
// ���G [enemysphere.h]
// Author: KENSAKU HATORI
//
//================================================

// ��d�C���N���[�h�h�~
#ifndef _ENEMTSPHERE_H_
#define _ENEMTSPHERE_H_

// �C���N���[�h
#include "enemy.h"

// ���̂̓G�N���X���`
class CEnemySphere : public CEnemy
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEnemySphere();
	~CEnemySphere();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEnemySphere* Create(D3DXVECTOR3 Pos);
private:
};
#endif // !_ENEMTSPHERE_H_