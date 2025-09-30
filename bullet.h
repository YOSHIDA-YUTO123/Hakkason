//================================================
//
// �e [bullet.h]
// Author: KENSAKU HATORI
//
//================================================

// �C���N���[�h
#include "objectX.h"

// �e�̃N���X���`
class CBullet : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBullet();
	~CBullet();

	// �����o�֐�
	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed);
private:
	D3DXVECTOR3 m_Move;		// �ړ���
};