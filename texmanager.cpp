//****************************************************************
//
// �e�N�X�`�����ꊇ�Ǘ�����N���X�̏���[texmanager.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "texmanager.h"
#include "manager.h"
#include <string>
#include <fstream>
#include <sstream>
#include "renderer.h"
#include <assert.h>

// ���O���
using namespace std;

// �ÓI�����o�ϐ��錾
unordered_map<string, LPDIRECT3DTEXTURE9> CLoadTexture::m_TexMap = {};

//*********************************************
// �R���X�g���N�^
//*********************************************
CLoadTexture::CLoadTexture()
{
}

//*********************************************
// �f�X�g���N�^
//*********************************************
CLoadTexture::~CLoadTexture()
{
}

//*********************************************
// �e�N�X�`�����O���t�@�C������ǂ݂���
//*********************************************
void CLoadTexture::Load(std::string LoadFilePath)
{
	// �ȗ��p�p�X
	string LoadfilePath = "data/TXT/";

	// �������A������
	LoadfilePath += LoadFilePath;

	// �t�@�C�����J��
	ifstream ifs(LoadfilePath.c_str());

	// �J���Ȃ�������
	if (!ifs)
	{
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���ł���", LoadfilePath.c_str(), MB_OK);
		return;
	}

	// �s��ǂݎ��p
	string line = {};
	// ���x���A�C�R�[����ǂݍ��ޗp
	string label = {}, equal = {};

	while (getline(ifs, line))
	{
		string TextureFilePath = "data/TEXTURE/";

		string FilePath = {};

		istringstream iss(line);
		if (line.find("TEX_FILENAME") != string::npos)
		{
			iss >> label >> equal >> FilePath;
		}

		if (FilePath[0] != NULL)
		{
			// ������̘A��
			TextureFilePath += FilePath;

			GetTex(TextureFilePath);
		}

		if (line.find("#") != string::npos)
		{
			continue;
		}
	}
}

//*********************************************
// �e�N�X�`���̎擾����
//*********************************************
LPDIRECT3DTEXTURE9 CLoadTexture::GetTex(string Path)
{
	// ���݂����炻���Ԃ�
	if (m_TexMap.find(Path) != m_TexMap.end()) return m_TexMap[Path];

	// ��肪�Ȃ��ăp�X�̒������Z��������N���G�C�g
	CRenderer* pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̏���������ꎞ�ϐ�
	LPDIRECT3DTEXTURE9 TexInfo = NULL;

	// �쐬
	D3DXCreateTextureFromFile(
		pDevice,
		Path.c_str(),
		&TexInfo
	);

	// ���
	m_TexMap[Path] = TexInfo;

	// ����Ԃ�
	return m_TexMap[Path];
}

//*********************************************
// �C���f�b�N�X�Ńe�N�X�`���擾
//*********************************************
LPDIRECT3DTEXTURE9 CLoadTexture::GetTex(const int Idx)
{
	// �s���ȃC���f�b�N�X�Ȃ�A�T�[�g
	if (Idx < 0 || Idx >= (int)m_TexMap.size()) assert(0 && "���݂��Ȃ��e�N�X�`���ɃA�N�Z�X���悤�Ƃ��Ă��܂�");

	// �z��ŃA�N�Z�X���邽�߂̃C�e���[�^�[
	auto Map = m_TexMap.begin();

	// �v�f��i�߂�
	std::advance(Map, Idx);

	// Vlue��Ԃ�
	return Map->second;
}

//*********************************************
// �e�N�X�`���̔j��
//*********************************************
void CLoadTexture::UnRegistTex(void)
{
	// �}�b�v�̒��ɃA�N�Z�X
	for (auto& Map : m_TexMap) 
	{
		// nullptr�`�F�b�N
		if (Map.second != nullptr)
		{
			// �������J��
			Map.second->Release();

			// nullptr��~���l�߂�
			Map.second = nullptr;
		}
	}

	// �}�b�v���̂��N���A
	m_TexMap.clear();
}