//****************************************************************
//
// �^�C�g�����S�̏���[titlelogo.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// �C���N���[�h
#include "titlelogo.h"
#include "texmanager.h"
#include "titlemanager.h"
#include "math_T.h"

//***************************************
// �R���X�g���N�^
//***************************************
CTitleLogo::CTitleLogo() : CObject2D(5)
{
}

//***************************************
// �f�X�g���N�^
//***************************************
CTitleLogo::~CTitleLogo()
{
}

//***************************************
// ����������
//***************************************
HRESULT CTitleLogo::Init(void)
{
    CObject2D::Init();
    return S_OK;
}

//***************************************
// �I������
//***************************************
void CTitleLogo::Uninit(void)
{
    CObject2D::Uninit();
}

//***************************************
// �X�V����
//***************************************
void CTitleLogo::Update(void)
{
    // �J�E���^�[��i�߂�
    if (m_nFrameCounter < CTitleManager::Config::Logo::AnimFrame)
    {
        m_nFrameCounter++;
    }
    // �ݒ肷��ʒu�̕ϐ�
    D3DXVECTOR3 SetPos = {};
    // ���̃A�j���[�V�����̐i�s�������v�Z
    float Ratio = EaseOutBounce((float)m_nFrameCounter / CTitleManager::Config::Logo::AnimFrame);
    // �ŏI�n�_���珉���ʒu����̍���
    D3DXVECTOR3 Diff  = CTitleManager::Config::Logo::Dest - CTitleManager::Config::Logo::Apper;
    // ���̈ʒu���v�Z
    SetPos = CTitleManager::Config::Logo::Apper + Diff * Ratio;
    // �ݒ�
    CObject2D::SetPosition(SetPos);
    CObject2D::Update();
}

//***************************************
// �`�揈��
//***************************************
void CTitleLogo::Draw(void)
{
    CObject2D::Draw();
}

//***************************************
// ��ԉ��܂ō~��Ă��Ȃ������牺��
//***************************************
void CTitleLogo::Lower(void)
{
    if (m_nFrameCounter < CTitleManager::Config::Logo::AnimFrame)
    {
        m_nFrameCounter = CTitleManager::Config::Logo::AnimFrame;
    }
}

//***************************************
// ��ԉ��܂ō~��Ă��邩�ǂ���
//***************************************
bool CTitleLogo::GetLower(void)
{
    return m_nFrameCounter >= CTitleManager::Config::Logo::AnimFrame;
}

//***************************************
// ��������
//***************************************
CTitleLogo* CTitleLogo::Create(const D3DXVECTOR3 Pos, const D3DXVECTOR3 Rot, const D3DXVECTOR2 Size, const char* FilePath)
{
    // �|�C���^��錾
    CTitleLogo* pTitleLogo = NULL;
    // �������m��
    pTitleLogo = new CTitleLogo;
    // �e�폈��
    pTitleLogo->Init();
    pTitleLogo->SetPosition(Pos);
    pTitleLogo->SetRotaition(Rot);
    pTitleLogo->SetSize(Size);
    pTitleLogo->SetColor({ 1.0f,1.0f,1.0f,1.0f });
    pTitleLogo->SetTextureID(FilePath);
    // �Ԃ�
    return pTitleLogo;
}