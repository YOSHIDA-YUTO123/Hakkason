//****************************************************************
//
// �e�N�X�`�����ꊇ�Ǘ�����N���X�̏���[texmanager.h]
// Author Kensaku Hatori
//
//****************************************************************

// ��\�C���N���[�h�h�~
#ifndef _TEXMANAGER_H_
#define _TEXMANAGER_H_

// �C���N���[�h
#include "main.h"
#include <unordered_map>

// �e�N�X�`�����O���t�@�C������ǂݍ��ރN���X
class CLoadTexture
{
public:
	// �f�X�g���N�^
	~CLoadTexture();

	// �ǂݍ��݁E�j��
	static void Load(std::string LoadFilePath);

	// �ÓI�����o�֐�
	static LPDIRECT3DTEXTURE9 GetTex(std::string Path);
	static LPDIRECT3DTEXTURE9 GetTex(const int Idx);
	static void UnRegistTex(void);
private:
	// �R���X�g���N�^
	CLoadTexture();

	// �ÓI�����o�ϐ�
	static std::unordered_map<std::string, LPDIRECT3DTEXTURE9> m_TexMap;	// �e�N�X�`���ւ̃C���f�b�N�X�̃}�b�v���쐬
};
#endif // !_TEXMANAGER_H_