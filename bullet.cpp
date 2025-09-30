//================================================
//
// �e [bullet.cpp]
// Author: KENSAKU HATORI
//
//================================================

// �C���N���[�h
#include "bullet.h"

//================================================
// �R���X�g���N�^
//================================================
CBullet::CBullet()
{
}

//================================================
// �f�X�g���N�^
//================================================
CBullet::~CBullet()
{
}

//================================================
// ����������
//================================================
HRESULT CBullet::Init(void)
{
	// ����������
	CObjectX::Init();

	// ����I��
	return S_OK;
}

//================================================
// �X�V����
//================================================
void CBullet::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 myPos = GetPosition();

	// �ʒu�����炷
	myPos += m_Move;

	// �ݒ�
	SetPosition(myPos);

	// �X�V����
	CObjectX::Update();
}

//================================================
// �I������
//================================================
void CBullet::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//================================================
// �`�揈��
//================================================
void CBullet::Draw(void)
{
	// �`�揈��
	CObjectX::Draw();
}

//================================================
// ��������
//================================================
CBullet* CBullet::Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR3 Dir, const float Speed)
{
	// �������m�ۂ��邽�߂̃C���X�^���X��錾
	CBullet* Instance = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	Instance = new CBullet;

	// �C���X�^���X�������ł��Ȃ�������
	if (Instance == nullptr) return nullptr;

	// ����������
	Instance->Init();
	Instance->SetPosition(Pos);
	Instance->SetRotation(Rot);
	Instance->m_Move = Dir * Speed;

	// ���f����ǂݍ���
	Instance->LoadModel("Test.x");

	// �C���X�^���X��Ԃ�
	return Instance;
}