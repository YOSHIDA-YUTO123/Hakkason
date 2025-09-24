//===================================================
//
// �X�e���V���V���h�E [shadowS.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _SHADOWS_H_
#define _SHADOWS_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "objectX.h"

//***************************************************
// �e(�X�e���V��)�̃N���X�̒�`
//***************************************************
class CShadowS : public CObjectX
{
public:
	CShadowS(int nPriority = 3);
	~CShadowS();
	static CShadowS* Create(const D3DXVECTOR3 pos);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer; // ���_�o�b�t�@�ւ̃|�C���^
};

#endif