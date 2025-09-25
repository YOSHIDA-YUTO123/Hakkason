//****************************************************************
//
// 3Dparticleの処理[particle3D.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// インクルード
#include "particle3d.h"
#include "effect3d.h"
#include "math.h"

// 名前空間
using namespace Const;
using namespace math;

//*********************************************
// コンストラクタ
//*********************************************
CParticle3D::CParticle3D()
{
	// パーティクルの情報を初期化
	m_ParticleInfo = {};
}

//*********************************************
// デストラクタ
//*********************************************
CParticle3D::~CParticle3D()
{
}

//*********************************************
// 初期化処理
//*********************************************
HRESULT CParticle3D::Init(void)
{
	return S_OK;
}

//*********************************************
// 終了処理
//*********************************************
void CParticle3D::Uninit(void)
{
	// 自分自身の破棄
	Release();
}

//*********************************************
// 更新処理
//*********************************************
void CParticle3D::Update(void)
{
	// カウンターを進める
	m_ParticleInfo.Bece.nCounter++;

	// クールダウンを超えたら
	if (m_ParticleInfo.Bece.nCounter > m_ParticleInfo.Bece.nCoolDown)
	{
		// 寿命が尽きていなかったら、ループする場合なら
		if (m_ParticleInfo.Bece.nLife > 0 || m_ParticleInfo.Bece.bLoop == true)
		{
			// 指定された個数分生成
			for (int nCount = 0; nCount < m_ParticleInfo.Bece.nNumEffect; nCount++)
			{
				// 情報をランダムで決める
				int Life = rand() % m_ParticleInfo.Bece.nMaxLife + m_ParticleInfo.Bece.nMinLife;

				float Speed = math::Randf(m_ParticleInfo.Bece.fMaxSpeed, m_ParticleInfo.Bece.fMinSpeed);

				float fRadius = math::Randf(m_ParticleInfo.MaxRadius, m_ParticleInfo.MinRadius);

				float Gravity = m_ParticleInfo.Bece.Gravity;

				// 移動量を計算
				D3DXVECTOR3 Move;
				Move = math::RandVec(m_ParticleInfo.Bece.MaxDir, m_ParticleInfo.Bece.MinDir);
				Move *= Speed;

				// プライオリティが不正な値だったらデフォルトに固定
				if (m_ParticleInfo.Bece.nPriority < 0 || m_ParticleInfo.Bece.nPriority > NUM_PRIORITY) m_ParticleInfo.Bece.nPriority = 3;

				// 生成
				CEffect3D::Create(m_ParticleInfo.Bece.Pos, Move, m_ParticleInfo.Bece.Col, D3DXVECTOR2(fRadius, fRadius), Gravity, Life, m_ParticleInfo.Bece.FilePath,m_ParticleInfo.Bece.nPriority);
			}
		}
		else
		{
			// 自分自身の破棄
			Uninit();
			// 処理の切り上げ
			return;
		}
		// カウンターをリセット、寿命を減らす
		m_ParticleInfo.Bece.nCounter = 0;
		m_ParticleInfo.Bece.nLife--;
	}
}

//*********************************************
// 生成
//*********************************************
CParticle3D* CParticle3D::Create(DefoultEffectInfo ParticleInfo)
{
	CParticle3D* pParticle = NULL;
	// メモリ確保
	pParticle = new CParticle3D;
	// 初期化処理
	pParticle->Init();
	// 情報の設定
	pParticle->m_ParticleInfo = ParticleInfo;
	pParticle->m_ParticleInfo.Bece.nCounter = ParticleInfo.Bece.nCoolDown;
	return pParticle;
}