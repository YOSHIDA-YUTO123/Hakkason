//================================================
//
// �G [enemy.h]
// Author: KENSAKU HATORI
//
//================================================

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
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
private:
};