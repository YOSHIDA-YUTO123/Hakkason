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
	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};