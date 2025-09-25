//===================================================
//
// �v�Z [math.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "math.h"

//===================================================
// �����̎擾
//===================================================
float math::GetDistance(const D3DXVECTOR3 diff)
{
	// �������悷��
	float sqX = diff.x * diff.x;
	float sqY = diff.y * diff.y;
	float sqZ = diff.z * diff.z;
	
	// ���������߂�
	float Out = sqrtf(sqX + sqY + sqZ);
	
	return Out;
}

//===================================================
// �ړI�̕����x�N�g���̎擾
//===================================================
D3DXVECTOR3 math::GetVector(const D3DXVECTOR3 dest, const D3DXVECTOR3 pos)
{
	// ���������߂�
	D3DXVECTOR3 diff = dest - pos;

	// ���K������
	D3DXVec3Normalize(&diff, &diff);

	return diff;
}

//===================================================
// �ړI�܂ł̊p�x�̎擾
//===================================================
float math::GetTargetAngle(const D3DXVECTOR3 dest, const D3DXVECTOR3 pos)
{
	D3DXVECTOR3 diff = dest - pos;

	float fAngle = atan2f(diff.x, diff.z);

	return fAngle;
}

//===================================================
// �ʒu�̍s���D3DXVECTOR3�^�ɕϊ�
//===================================================
D3DXVECTOR3 math::GetPositionFromMatrix(const D3DXMATRIX mtxWorld)
{
	D3DXVECTOR3 pos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	return pos;
}

//===================================================
// ��]�s����I�C���[�p�ɕϊ�
//===================================================
D3DXVECTOR3 math::MatrixToEulerXYZ(const D3DXMATRIX mtxWorld)
{
	D3DXVECTOR3 rot;

	if (fabsf(mtxWorld._32) < 1.0f)
	{
		rot.x = asinf(-mtxWorld._32);
		rot.y = atan2f(mtxWorld._31,mtxWorld._33);
		rot.z = atan2f(mtxWorld._12, mtxWorld._22);
	}
	else
	{
		rot.x = (mtxWorld._32 <= -1.0f) ? D3DX_PI * 0.5f : -D3DX_PI * 0.5f;
		rot.y = atan2f(-mtxWorld._13, mtxWorld._11);
		rot.z = 0.0f;
	}

	return rot;
}

//===================================================
// �����_���ʂ܂ł̃����_���֐�
//===================================================
float math::Randf(float Max, float Min)
{
	if (Max <= 0 || Min <= 0) return 0.0f;
	// �\�{���ď\���̈�ɂ���
	float Out = (rand() % (int)(Max * 100.0f) + (int)(Min * 100.0f)) * 0.01f;
	return Out;
}

//===================================================
// �x�N�g���Ԃ������_���ȃX�J���[�l�ŕ⊮
//===================================================
D3DXVECTOR3 math::RandVec(D3DXVECTOR3 Max, D3DXVECTOR3 Min)
{
	// �o�͗p
	D3DXVECTOR3 randVec;

	// �n�_ + ���� * ����
	randVec.x = Min.x + (float)(rand()) / RAND_MAX * (Max.x - Min.x);
	randVec.y = Min.y + (float)(rand()) / RAND_MAX * (Max.y - Min.y);
	randVec.z = Min.z + (float)(rand()) / RAND_MAX * (Max.z - Min.z);

	// ���K�����ĕ����x�N�g���ɂ���
	D3DXVec3Normalize(&randVec, &randVec);

	return randVec;
}
