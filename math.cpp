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
