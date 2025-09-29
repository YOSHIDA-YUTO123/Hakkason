//================================================
//
// ���b�V���C���p�N�g [impact.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _IMPACT_H_
#define _IMPACT_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object.h"
#include <string>

//************************************************
// ���b�V���T�[�N��(����)�N���X�̒�`
//************************************************
class CMeshCircle : public CObject
{
public:
	CMeshCircle();
	~CMeshCircle();

	/// <summary>
	/// ��������(�p�����[�^�[�̐ݒ��SetParam�֐���)
	/// </summary>
	/// <param name="�ʒu"></param>
	/// <param name="�F"></param>
	/// <param name="�����̔��a"></param>
	/// <param name="�O���̔��a"></param>
	/// <param name="������"></param>
	/// <returns>�����̃C���X�^���X</returns>
	static CMeshCircle* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fInRadius, const float fOutRadius, const int nSegH = 32);

	/// <summary>
	/// �p�����[�^�̐ݒ菈��
	/// </summary>
	/// <param name="����(����)"></param>
	/// <param name="�g�呬�x"></param>
	/// <param name="����"></param>
	/// <param name="����"></param>
	void SetParam(const float fHeight, const float fSpeed, const int nLife, const D3DXVECTOR3 rot = Const::VEC3_NULL);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetTextureID(const char* pTexturePath);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffer;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXCOLOR m_InCol;						// �����̐F
	D3DXCOLOR m_OutCol;						// �O���̐F
	std::string m_TexturePath;				// �e�N�X�`���̃p�X
	float m_fInRadius;						// �����̔��a
	float m_fOutRadius;						// �O���̔��a
	float m_fHeight;						// ����
	float m_fDecAlv;						// A�l�̌����l
	float m_fSpeed;							// ����
	int m_nSegH, m_nSegV;					// ���̕������A�c�̕�����
	int m_nNumVtx;							// ���_�̐�
	int m_nNumPolygon;						// �|���S���̐�
	int m_nNumIdx;							// �C���f�b�N�X��
	int m_nLife;							// ����
};
#endif