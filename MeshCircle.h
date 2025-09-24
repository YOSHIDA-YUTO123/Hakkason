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
#include"object.h"

//************************************************
// ���b�V���T�[�N��(����)�N���X�̒�`
//************************************************
class CMeshCircle : public CObject
{
public:
	CMeshCircle();
	~CMeshCircle();

	/**
	* @brief ��������(�p�����[�^�̐ݒ��SetParam�֐���)
	* @param �ʒu
	* @param �F
	* @param �����̔��a
	* @param �O���̔��a
	* @param ���_��
	* @return �����̃C���X�^���X
	*/
	static CMeshCircle* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fInRadius, const float fOutRadius, const int nSegH = 32);

	/**
	* @brief �p�����[�^�̐ݒ菈��
	* @param ����(�����̒��_�̍���)
	* @param ����
	* @param ����
	* @param ����
	*/
	void SetParam(const float fHeight, const float fSpeed, const int nLife, const D3DXVECTOR3 rot = Const::VEC3_NULL);

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffer;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXCOLOR m_InCol;						// �����̐F
	D3DXCOLOR m_OutCol;						// �O���̐F
	float m_fInRadius;						// �����̔��a
	float m_fOutRadius;						// �O���̔��a
	float m_fHeight;						// ����
	float m_fDecAlv;						// A�l�̌����l
	float m_fSpeed;							// ����
	int m_nSegH, m_nSegV;					// ���̕������A�c�̕�����
	int m_nNumVtx;							// ���_�̐�
	int m_nNumPolygon;						// �|���S���̐�
	int m_nNumIdx;							// �C���f�b�N�X��
	int m_nTextureIdx;						// �e�N�X�`����ID
	int m_nLife;							// ����
};
#endif