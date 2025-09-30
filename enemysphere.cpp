//================================================
//
// ���G [enemysphere.cpp]
// Author: KENSAKU HATORI
//
//================================================

// �C���N���[�h
#include "player.h"
#include "game.h"
#include "manager.h"
#include "enemysphere.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "enemymanager.h"

//================================================
// �R���X�g���N�^
//================================================
CEnemySphere::CEnemySphere() : CEnemy(TYPE_ONE)
{
}

//================================================
// �f�X�g���N�^
//================================================
CEnemySphere::~CEnemySphere()
{
}

//================================================
// ����������
//================================================
HRESULT CEnemySphere::Init(void)
{
	// ����������
	CEnemy::Init();

	// ����I��
	return S_OK;
}

//================================================
// �I������
//================================================
void CEnemySphere::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//================================================
// �X�V����
//================================================
void CEnemySphere::Update(void)
{
	// �V�[�����Q�[���ȊO�Ȃ瑁�����^�[��
	if (CManager::GetMode() != CScene::MODE_GAME) return;
	// �v���C���[����������Ă��Ȃ������瑁�����^�[��
	if (CGame::GetPlayer() == NULL) return;

	// �v���C���[�܂ł̃x�N�g��������
	D3DXVECTOR3 pVec = CGame::GetPlayer()->GetModelPos(1) - GetPosition();

	// ���K��
	D3DXVec3Normalize(&pVec, &pVec);

	// �X�s�[�h��������
	pVec *= 2.0f;
	pVec.y = 0.0f;

	// �ݒ�
	SetMove(pVec);

	// �X�V����
	CEnemy::Update();
}

//================================================
// �`�揈��
//================================================
void CEnemySphere::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//================================================
// ����
//================================================
CEnemySphere* CEnemySphere::Create(D3DXVECTOR3 Pos)
{
	// �������m�ۂ��邽�߂̃C���X�^���X��錾
	CEnemySphere* Instance = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	Instance = new CEnemySphere;

	// �C���X�^���X�������ł��Ȃ�������
	if (Instance == nullptr) return nullptr;

	// ����������
	Instance->Init();
	Instance->SetPosition(Pos);

	// ���f����ǂݍ���
	Instance->LoadModel("enemy_blue.x");

	// �C���X�^���X��Ԃ�
	return Instance;
}