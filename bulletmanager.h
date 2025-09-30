//===================================================
//
// �o���b�g�Ǘ� [bulletmanager.h]
// Author:YUTO YOSHIDA
//
//===================================================

// ��d�C���N���[�h�h�~
#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

// �C���N���[�h
#include "object.h"
#include "bullet.h"
#include <vector>

// �e���ꊇ�Ǘ�����N���X���`
class CBulletManager
{
public:
	// �f�X�g���N�^
	~CBulletManager();

	// �ÓI�����o�֐�
	// �Q�b�^�[
	static std::vector<CBullet*>& GetpvBullet(void) { return m_pvBullet; }
	// �Z�b�^�[
	// ����
	static void PushBackBullet(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed);
protected:
private:
	// �R���X�g���N�^
	CBulletManager() {};
	// �ÓI�����o�ϐ�
	static std::vector<CBullet*> m_pvBullet;	// �o���b�g�̉ϒ��z��
};
#endif // !_BULLETMANAGER_H_