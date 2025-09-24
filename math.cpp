//===================================================
//
// 計算 [math.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// インクルードファイル
//***************************************************
#include "math.h"

//===================================================
// 距離の取得
//===================================================
float math::GetDistance(const D3DXVECTOR3 diff)
{
	// 距離を二乗する
	float sqX = diff.x * diff.x;
	float sqY = diff.y * diff.y;
	float sqZ = diff.z * diff.z;
	
	// 距離を求める
	float Out = sqrtf(sqX + sqY + sqZ);
	
	return Out;
}

//===================================================
// 目的の方向ベクトルの取得
//===================================================
D3DXVECTOR3 math::GetVector(const D3DXVECTOR3 dest, const D3DXVECTOR3 pos)
{
	// 方向を求める
	D3DXVECTOR3 diff = dest - pos;

	// 正規化する
	D3DXVec3Normalize(&diff, &diff);

	return diff;
}

//===================================================
// 目的までの角度の取得
//===================================================
float math::GetTargetAngle(const D3DXVECTOR3 dest, const D3DXVECTOR3 pos)
{
	D3DXVECTOR3 diff = dest - pos;

	float fAngle = atan2f(diff.x, diff.z);

	return fAngle;
}

//===================================================
// 位置の行列をD3DXVECTOR3型に変換
//===================================================
D3DXVECTOR3 math::GetPositionFromMatrix(const D3DXMATRIX mtxWorld)
{
	D3DXVECTOR3 pos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	return pos;
}

//===================================================
// 回転行列をオイラー角に変換
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
