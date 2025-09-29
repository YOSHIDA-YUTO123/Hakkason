//================================================
//
// ���b�V���V�����_�[�̕`�� [MeshCylinder.h]
// Author: YUTO YOSHIDA
//
//================================================

//*************************************************
// ���d�C���N���[�h�h�~
//*************************************************
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//************************************************
// �C���N���[�h�t�@�C��
//************************************************
#include "object.h"
#include <string>

//************************************************
// ���b�V���V�����_�[�̃N���X�̒�`
//************************************************
class CMeshCylinder : public CObject
{
public:
	CMeshCylinder(const int nPriority = 2);
	~CMeshCylinder();

	static CMeshCylinder* Create(const D3DXVECTOR3 pos, const float fRadius, const float fHeight, const int nSegH, const int nSegV);

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
	std::string m_TexturePath;				// �e�N�X�`���̃p�X
	float m_fRadius;						// ���a
	float m_fHeight;						// ����
	int m_nSegH, m_nSegV;					// ���̕������A�c�̕�����
	int m_nNumVtx;							// ���_�̐�
	int m_nNumPolygon;						// �|���S���̐�
	int m_nNumIdx;							// �C���f�b�N�X��
};

#endif
