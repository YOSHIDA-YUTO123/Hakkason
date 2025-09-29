//================================================
//
// ���ƕb�������^�C�}�[�̃N���X�̏��� [DualUnitTimer.cpp]
// Author:YUTO YOSHIDA
//
//=================================================

//*************************************************
// �C���N���[�h�t�@�C��
//*************************************************
#include "DualUnitTimer.h"
#include "object2D.h"

//*************************************************
// ���O���
//*************************************************
using namespace Const; // ���O���Const�̎g�p
using namespace std;   // ���O���std�̎g�p

//=================================================
// �R���X�g���N�^
//=================================================
CDualUnitTimer::CDualUnitTimer()
{
    m_nCounter = NULL;
    m_pMinute = nullptr;
}

//=================================================
// �f�X�g���N�^
//=================================================
CDualUnitTimer::~CDualUnitTimer()
{
}

//=================================================
// ����������
//=================================================
CDualUnitTimer* CDualUnitTimer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size, const int nTime)
{
    CDualUnitTimer* pTimer = new CDualUnitTimer;

    pTimer->SetPosition(pos);
    pTimer->SetSize(Size);
    pTimer->SetTime(nTime % FRAME);

    // �^�C�}�[�N���X�̐���
    pTimer->m_pMinute = new CTimer;

    // ���̐ݒ�
    pTimer->m_pMinute->SetTime(nTime / FRAME);

    // ����������
    if (FAILED(pTimer->Init()))
    {
        pTimer->Uninit();
        pTimer = nullptr;
        return nullptr;
    }

    return pTimer;
}

//=================================================
// ����������
//=================================================
HRESULT CDualUnitTimer::Init(void)
{
    // ����������
    if (FAILED(CTimer::Init()))
    {
        return E_FAIL;
    }

    // �e�N�X�`����ID�̐ݒ�
    CTimer::SetTexture("number000.png");

    // �傫���̎擾
    D3DXVECTOR2 Size = CTimer::GetSize();

    // �ʒu�̎擾
    D3DXVECTOR3 pos = CTimer::GetPosition();

    // �R�����̈ʒuX
    float fCoronOffPosX = pos.x - Size.x * 2.0f;

    // �R�����̐���
    CObject2D::Create(Size.x * 0.25f, Size.y, D3DXVECTOR3(fCoronOffPosX, pos.y, pos.z))->SetTextureID("unit/coron.png");

    // ���̉��̃I�t�Z�b�g�̈ʒu�����߂�
    float fMinuteOffPosX = pos.x - Size.x * 3.0f;

    if (m_pMinute != nullptr)
    {
        // �ʒu�̐ݒ�
        m_pMinute->SetPosition(D3DXVECTOR3(fMinuteOffPosX, pos.y, pos.z));
        m_pMinute->SetSize(Size);

        // ����������
        if (FAILED(m_pMinute->Init()))
        {
           m_pMinute->Uninit();
           m_pMinute = nullptr;

            return E_FAIL;
        }

        // �e�N�X�`����ID�̐ݒ�
        m_pMinute->SetTexture("number000.png");
    }

    return S_OK;
}

//=================================================
// �I������
//=================================================
void CDualUnitTimer::Uninit(void)
{
    // �I������
    CTimer::Uninit();
}

//=================================================
// �X�V����
//=================================================
void CDualUnitTimer::Update(void)
{
    if (m_pMinute == nullptr) return;
    
    m_nCounter++;
        
    // �b�̎擾
    int nSecond = CTimer::GetTime();

    // ���̎擾
    int nMinute = m_pMinute->GetTime();

    if (m_nCounter >= FRAME)
    {
        // �b��0����Ȃ�������
        if (nSecond > 0)
        {
            // �b�����炷
            nSecond--;
        }
        // ����0����Ȃ�������
        else if (nSecond <= 0 && nMinute != 0)
        {
            // �����������
            nSecond = FRAME - 1;

            // �������炷
            nMinute--;
        }
        m_nCounter = 0;
    }

    // 60�𒴂�����
    if (nSecond >= FRAME)
    {
        nMinute++; // ����1���₷

        // �]�肪0����Ȃ�������(60���ゾ������)
        if (nSecond % FRAME != 0)
        {
            int Time = nSecond % FRAME; // �]������߂�

            nSecond = 0; // 0�ɂ���
            nSecond += Time; // �]������Z����
        }
        else
        {
            nSecond = 0; // 0�ɂ���
        }
    }

    // �b�̐ݒ�
    CTimer::SetTime(nSecond);

    // ���̐ݒ�
    m_pMinute->SetTime(nMinute);

    // �X�V����
    m_pMinute->Update();
    
    // �X�V����
    CTimer::Update();
}

//=================================================
// �`�揈��
//=================================================
void CDualUnitTimer::Draw(void)
{
    // �`�揈��
    CTimer::Draw();

    // �`�揈��
    if (m_pMinute != nullptr)
    {
        m_pMinute->Draw();
    }
}
