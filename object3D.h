//===================================================
//
// 3D�I�u�W�F�N�g�̕`�� [object3D.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "object.h"
#include <string>

//***************************************************
// �I�u�W�F�N�g3D�N���X�̒�`
//***************************************************
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();

	static CObject3D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const char* pTextureName);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void SetDraw(void);

	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotaition(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(const D3DXVECTOR3 Size) { m_Size = Size; }

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetSize(void) const { return m_Size; }

	void SetOffsetVtx(const D3DXCOLOR col = Const::WHITE, const int nPosX = 1, const int nPosY = 1);
	void SetTextureID(const char* pTextureName);
	void UpdatePosition(const D3DXVECTOR3 pos, const D3DXVECTOR3 Size);
	void UpdateCol(const D3DXCOLOR col);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_Size;						// �傫��
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	std::string m_TexturePath;				// �e�N�X�`���̃p�X
};
#endif