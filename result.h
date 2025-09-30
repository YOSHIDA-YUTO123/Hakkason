//===================================================
//
// ���U���g�V�[�� [result.h]
// Author:YUTO YOSHIDA
//
//===================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include"main.h"
#include "scene.h"
#include<memory>

//***************************************************
// �O���錾
//***************************************************

//***************************************************
// ���U���g(����)�N���X�̒�`
//***************************************************
class CResultWin : public CScene
{
public:

	CResultWin();
	~CResultWin();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};

//***************************************************
// ���U���g(�s�k)�N���X�̒�`
//***************************************************
class CResultLose : public CScene
{
public:

	CResultLose();
	~CResultLose();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif