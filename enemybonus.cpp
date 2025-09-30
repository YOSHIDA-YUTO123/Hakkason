//===================================================
//
// �{�[�i�X�G [enemybonus.cpp]
// Author:YUTO YOSHIDA
//
//===================================================

// �C���N���[�h
#include "enemybonus.h"
#include "player.h"
#include "game.h"
#include "manager.h"
#include "Collision.h"
#include "Collider.h"
#include "bulletmanager.h"
#include "enemymanager.h"
#include "effect3d.h"
#include "particle3d.h"

//===================================================
// �R���X�g���N�^
//===================================================
CEnemyBonus::CEnemyBonus() : CEnemy(TYPE_ONE)
{
}

//===================================================
// �f�X�g���N�^
//===================================================
CEnemyBonus::~CEnemyBonus()
{
}

//===================================================
// ����������
//===================================================
HRESULT CEnemyBonus::Init(void)
{
	// ����������
	CEnemy::Init();

	// ����I��
	return S_OK;
}

//===================================================
// �I������
//===================================================
void CEnemyBonus::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//===================================================
// �X�V����
//===================================================
void CEnemyBonus::Update(void)
{
	// �V�[�����Q�[���ȊO�Ȃ瑁�����^�[��
	if (CManager::GetMode() != CScene::MODE_GAME) return;

	// �v���C���[����������Ă��Ȃ������瑁�����^�[��
	if (CGame::GetPlayer() == NULL) return;

	m_nTimer++;

	// �v���C���[�܂ł̃x�N�g��������
	D3DXVECTOR3 pVec = CGame::GetPlayer()->GetModelPos(1) - GetPosition();

	float Speed = 2.0f;

	if (D3DXVec3Length(&pVec) < 300.0f)
	{
		Speed = 0.0f;
	}
	if (D3DXVec3Length(&pVec) > 0.0f)
	{
		Speed = -2.0f;
	}

	// ���K��
	D3DXVec3Normalize(&pVec, &pVec);

	// �X�s�[�h��������
	pVec *= Speed;
	pVec.y = 0.0f;

	// �ݒ�
	SetMove(pVec);

	// �΂̏���ݒ�
	CParticle3D::DefoultEffectInfo FireInfo;
	FireInfo.Bece.Col = { 1.0f,0.89f,0.0f,1.0f };
	FireInfo.Bece.fMaxSpeed = 1.0f;
	FireInfo.Bece.fMinSpeed = 1.0f;
	FireInfo.Bece.MaxDir = { 0.1f,0.5f,0.1f };
	FireInfo.Bece.MinDir = { -0.1f,0.5f,-0.1f };
	FireInfo.Bece.nLife = 1;
	FireInfo.Bece.nMaxLife = 30;
	FireInfo.Bece.nMinLife = 30;
	FireInfo.Bece.nNumEffect = 1;
	FireInfo.Bece.Pos = { GetPosition().x,GetPosition().y ,GetPosition().z };
	FireInfo.MaxRadius = 3.8f;
	FireInfo.MinRadius = 2.8f;
	FireInfo.Bece.bLoop = false;
	FireInfo.Bece.nCoolDown = 2;
	FireInfo.Bece.Gravity = 0.03f;
	FireInfo.Bece.FilePath = CEffect3D::Config::Sphere;
	FireInfo.Bece.nPriority = 5;

	// ����
	CParticle3D::Create(FireInfo);

	// �X�V����
	CEnemy::Update();

	if (m_nTimer > 300)
	{
		CEnemyManager::Erase(this);
	}
}

//===================================================
// �`�揈��
//===================================================
void CEnemyBonus::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//===================================================
// ����
//===================================================
CEnemyBonus* CEnemyBonus::Create(D3DXVECTOR3 Pos)
{
	// �������m�ۂ��邽�߂̃C���X�^���X��錾
	CEnemyBonus* Instance = nullptr;

	// 3D�I�u�W�F�N�g�̐���
	Instance = new CEnemyBonus;

	// �C���X�^���X�������ł��Ȃ�������
	if (Instance == nullptr) return nullptr;

	// ����������
	Instance->Init();
	Instance->SetPosition(Pos);

	// ���f����ǂݍ���
	Instance->LoadModel("enemy_score.x");

	// �C���X�^���X��Ԃ�
	return Instance;
}