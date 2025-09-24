//===================================================
//
// �A�j���[�V����3D�|���S�� [Object3DAnim.h]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _OBJECT3DANIM_H_
#define _OBJECT3DANIM_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "object.h"

//***************************************************
// �A�j���[�V����3D�|���S���N���X�̒�`
//***************************************************
class CObject3DAnim : public CObject
{
public:
	CObject3DAnim(const int nPriority = 5);
	virtual ~CObject3DAnim();

	static CObject3DAnim* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 Size, const int nDivU, const int nDivV);

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }
	D3DXVECTOR3 GetSize(void) const { return m_Size; }

	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotaition(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(const D3DXVECTOR3 Size) { m_Size = Size; }
	void SetTextureID(const char* pTextureName);
	void SetParam(const int nSpeed,const bool bLoop);
	void SetDivUV(const int nDivU, const int nDivV);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_Size;						// �傫��
	int m_nSpeed;							// �A�j���[�V�����̃X�s�[�h
	int m_nCounter;							// �J�E���^�[
	int m_nPattern;							// �p�^�[��
	int m_nDivU;							// ���̕�����
	int m_nDivV;							// �c�̕�����
	int m_nTextureIdx;						// �e�N�X�`���̃C���f�b�N�X
	bool m_bLoop;							// ���[�v���邩�ǂ���
};

#endif
