//================================================
//
// ���G [enemysphere.h]
// Author: KENSAKU HATORI
//
//================================================

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