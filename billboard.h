//===================================================
//
// �r���{�[�h��`�悷��N���X [billboard.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "object.h"
#include <string>

//***************************************************
// �r���{�[�h�N���X�̒�`
//***************************************************
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 7);
	virtual ~CObjectBillboard();

	static CObjectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pTextureName);

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	/// <summary>
	/// �}�g���b�N�X�̐ݒ菈��
	/// </summary>
	/// <param name="mtxRot"></param>
	/// <param name="mtxTrans"></param>
	void SetMatrix(const D3DXMATRIX mtxRot, const D3DXMATRIX mtxTrans);

	/// <summary>
	/// �`��̐ݒ菈�� (SetMatrix�̌�ɌĂ�)
	/// </summary>
	/// <param name=""></param>
	void SetUpDraw(void);

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR2 GetSize(void) const { return m_Size; }
	
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR2 size) { m_Size = size; }

	void SetColor(const D3DXCOLOR col);
	void SetTextureID(const char* pTextureName);
	void UpdateVertexPos(const D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu�̃N���X�̃|�C���^
	D3DXVECTOR2 m_Size;						// �傫��
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	std::string m_TexturePath;				// �e�N�X�`���̃p�X
};
#endif