//===================================================
//
// �A�j���[�V�����r���{�[�h�̕`�������N���X [billboardAnim.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

//***************************************************
// ���d�C���N���[�h�h�~
//***************************************************
#ifndef _BILLBOARDANIM_H_
#define _BILLBOARDANIM_H_

//***************************************************
// �C���N���[�h�t�@�C��
//***************************************************
#include "object.h"
#include <string>

//***************************************************
// �r���{�[�h(�A�j���[�V����)�N���X�̒�`
//***************************************************
class CBillboardAnimation : public CObject
{
public:
	CBillboardAnimation(int nPriority = 4);
	virtual ~CBillboardAnimation();

	/// <summary>
	/// ��������(SetParam�֐��ŃA�j���[�V�����̐ݒ�����Ă�������)
	/// </summary>
	/// <param name="�ʒu"></param>
	/// <param name="�傫��"></param>
	/// <param name="���̕�����"></param>
	/// <param name="�c�̕�����"></param>
	/// <returns>�����̃C���X�^���X</returns>
	static CBillboardAnimation* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size,const int nDivU,const int nDivV);

	virtual HRESULT Init(void) override;
	virtual void Uninit(void) override;
	virtual void Update(void) override;
	virtual void Draw(void) override;

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }
	D3DXVECTOR2 GetSize(void) const { return m_Size; }

	void SetParam(const int nSpeed, const bool bLoop);
	void SetDivUV(const int nDivU, const int nDivV);

	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(const D3DXVECTOR2 size) { m_Size = size; }

	void SetTextureVtx(const D3DXVECTOR2 OffPos, const D3DXVECTOR2 RateUV);
	void SetColor(const D3DXCOLOR col);
	void SetTextureID(const char* pTextureName);
	void UpdateVertexPos(const D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu�̃N���X�̃|�C���^
	D3DXVECTOR2 m_Size;						// �傫��
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	std::string m_TexturePath;				// �e�N�X�`���̃t�@�C���p�X
	float m_fPosTexU;						// �e�N�X�`�����WUV
	float m_fPosTexH;						// �e�N�X�`�����WHV
	int m_nSpeed;							// �A�j���[�V�����̑���
	int m_nPattern;							// �A�j���[�V�����̃p�^�[��
	int m_nCounter;							// �A�j���[�V�����̃J�E���^�[
	int m_nDivU;							// �e�N�X�`�����W�̕�������
	int m_nDivV;							// �e�N�X�`�����W�̕������c 
	bool m_bLoop;							// ���[�v���邩�ǂ���
};

#endif