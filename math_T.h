//*************************************
//
//�@�ėp�v�Z����[mat_T.h]
//�@Author:Hatori Kensaku
//
//*************************************

// ��d�C���N���[�h�h�~
#ifndef _MATHT_H_
#define _MATHT_H_

// �C���N���[�h
#include "main.h"
#include "manager.h"

//***************************************
// �N�����v
//***************************************
template <class T> T Clamp(const T t, const T min, const T max)
{
	if (t > max) return max;
	if (t < min) return min;
	return t;
}

//***************************************
// ���b�v
//***************************************
template <class T> T Wrap(const T t, const T min, const T max)
{
	if (t > max) return min;
	if (t < min) return max;
	return t;
}

//***************************************
// �p�x�̋ߓ���
//***************************************
template <class T> void ShortCut(const T Condition, T *Out)
{
	// �p�x�̋ߓ�
	if (Condition >= D3DX_PI)
	{
		*Out += D3DX_PI * 2.0f;
	}
	else if (Condition <= -D3DX_PI)
	{
		*Out -= D3DX_PI * 2.0f;
	}
}

//***************************************
// �p�x�̐��K��
//***************************************
template <class T> void Normalize(const T Condition, T* Out)
{
	// �p�x�̐��K��
	if (Condition > D3DX_PI)
	{
		*Out = -D3DX_PI + (*Out - D3DX_PI);
	}
	else if (Condition < -D3DX_PI)
	{
		*Out = D3DX_PI + (*Out + D3DX_PI);
	}
}

//***************************************
// ���`���
//***************************************
template <class T> T Lerp(const T t, const T dest, const T start)
{
	return (dest - start) * t;
}

//***************************************
// �C�[�W���O
//***************************************
template <class T> T EaseInSine(const T t)
{
	return (1 - cosf((t * D3DX_PI) / 2));
}

template <class T> T EaseOutSine(const T t)
{
	return sinf((t * D3DX_PI) / 2);
}

template <class T> T EaseInOutSine(const T t)
{
	return (-(cosf(D3DX_PI * t) - 1) / 2);
}

template <class T> T EaseInBounce(const T t)
{
	return 1 - EaseOutBounce(1 - t);
}

template <class T> T EaseOutBounce(T t)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (t < 1 / d1)
	{
		return (n1 * t * t);
	}
	else if (t < 2 / d1)
	{
		return (n1 * (t -= 1.5f / d1) * t + 0.75f);
	}
	else if (t < 2.5 / d1)
	{
		return (n1 * (t -= 2.25f / d1) * t + 0.9375f);
	}
	else 
	{
		return (n1 * (t -= 2.625f / d1) * t + 0.984375f);
	}
}

template <class T> T EaseInOutBounce(const T t)
{
	return t < 0.5
		? ((1 - EaseOutBounce(1 - 2 * t)) / 2)
		: ((1 + EaseOutBounce(2 * t - 1)) / 2);
}
#endif // !_MATHT_H_