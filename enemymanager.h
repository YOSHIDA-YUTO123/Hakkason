//===================================================
//
// �G�Ǘ� [enemymanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

#ifndef _ENEMYMANAGER_H_
#define _ENEMYMANAGER_H_

#include "enemy.h"

// �O���錾
class CColliderSphere;

class CEnemyManager
{
public:
	// �f�X�g���N�^
	~CEnemyManager();

	// �ÓI�����o�֐�
	// �Q�b�^�[
	static std::vector<CEnemy*>& GetpvBullet(void) { return m_pvEnemy; }
	// �Z�b�^�[
	// �A������
	static void Erase(CEnemy* Instance);
	// ����
	static void PushBackBullet(const D3DXVECTOR3 Pos, int Type);

	static void CollisionBullet(void);
private:
	// �R���X�g���N�^
	CEnemyManager() {};
	// �ÓI�����o�ϐ�
	static std::vector<CEnemy*> m_pvEnemy;	// �o���b�g�̉ϒ��z��
};
#endif // !_ENEMYMANAGER_H_