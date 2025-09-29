//================================================
//
// �e [shadow.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _SHADOW_H_
#define _SHADOW_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object3D.h"
#include <memory>
#include <string>

//*************************************************
// �O���錾
//*************************************************

//*************************************************
// �e�N���X�̒�`
//*************************************************
class CShadow
{
public:
	CShadow();
	~CShadow();

	static std::unique_ptr<CShadow> Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight,const D3DXCOLOR col);

	HRESULT Init(void);
	void Uninit(void);
	void Update(const D3DXVECTOR3 player, const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const float fMaxHeight, const float fAlv);
	void Draw(void);

	// �e�̐ݒ�
	void SetFieldAngle(D3DXVECTOR3 Nor, D3DXVECTOR3 up);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer; // ���_�o�b�t�@
	D3DXVECTOR3 m_pos;					  // �ʒu
	D3DXVECTOR3 m_rot;					  // ����
	D3DXVECTOR3 m_Size;					  // �傫��
	D3DXMATRIX m_mtxWorld;				  // ���[���h�}�g���b�N�X
	D3DXCOLOR m_col;					  // �F
	std::string m_TexturePath;			  // �e�N�X�`���̃p�X

};
#endif