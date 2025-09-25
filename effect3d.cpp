//****************************************************************
//
// ３Dエフェクトの処理[effect3D.cpp]
// Author Kensaku Hatori
//
//****************************************************************

// インクルード
#include "effect3d.h"
#include "textureManager.h"
#include "manager.h"
#include "renderer.h"

// 名前空間
using namespace Const;

//*********************************************
// コンストラクタ
//*********************************************
CEffect3D::CEffect3D(const int Priority) : CObjectBillboard(Priority)
{
	// エフェクトの挙動を初期化
	m_Module.Move = VEC3_NULL;
	m_Module.nLife = NULL;
	m_Module.fAlphaDef = NULL;
	m_Module.fSizeDefX = NULL;
	m_Module.fSizeDefY = NULL;
}

//*********************************************
// デストラクタ
//*********************************************
CEffect3D::~CEffect3D()
{
}

//*********************************************
// 初期化処理
//*********************************************
HRESULT CEffect3D::Init(void)
{
	// テクスチャのインデックスを設定
	CObjectBillboard::SetTextureID(m_Module.FilePath);
	// 一フレームに下がるアルファ値とサイズを設定
	m_Module.fAlphaDef = m_Module.Col.a / m_Module.nLife;
	m_Module.fSizeDefX = CObjectBillboard::GetSize().x / m_Module.nLife;
	m_Module.fSizeDefY = CObjectBillboard::GetSize().y / m_Module.nLife;
	// ビルボードの初期化処理
	return CObjectBillboard::Init();
}

//*********************************************
// 終了処理
//*********************************************
void CEffect3D::Uninit(void)
{
	// ビルボードの終了処理(メモリを破棄)
	CObjectBillboard::Uninit();
}

//*********************************************
// 更新処理
//*********************************************
void CEffect3D::Update(void)
{
	// 寿命を減らす
	m_Module.nLife--;
	// 寿命が尽きたら
	if (m_Module.nLife < 0)
	{
		Uninit();
		return;
	}

	// 色とサイズを減らす
	D3DXCOLOR Col = m_Module.Col;
	Col.a -= m_Module.fAlphaDef;
	D3DXVECTOR2 Size = {m_Module.fSizeDefX,m_Module.fSizeDefY};
	Size.x -= m_Module.fSizeDefX;
	Size.y -= m_Module.fSizeDefY;
	// 位置を動かす
	D3DXVECTOR3 Pos = CObjectBillboard::GetPosition();
	m_Module.Move.y += m_Module.fGravity;
	Pos += m_Module.Move;
	// 設定
	CObjectBillboard::SetColor(Col);
	CObjectBillboard::SetSize(Size);
	CObjectBillboard::SetPosition(Pos);
	CObjectBillboard::Update();
}

//*********************************************
// 描画処理
//*********************************************
void CEffect3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ゼットテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	// aブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObjectBillboard::Draw();

	//ゼットテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	// aブレンディングをもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//*********************************************
// 生成
//*********************************************
CEffect3D* CEffect3D::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXCOLOR Col, D3DXVECTOR2 Size, float Gravity, int Life, const char* FilePath,const int Priority)
{
	CEffect3D* pEffect = NULL;
	// メモリ確保
	pEffect = new CEffect3D(Priority);
	// 情報を代入
	pEffect->m_Module.Move = Move;
	pEffect->m_Module.nLife = Life;
	pEffect->m_Module.Col = Col;
	pEffect->m_Module.fGravity = Gravity;
	pEffect->m_Module.FilePath = FilePath;
	pEffect->SetPosition(Pos);
	pEffect->SetSize(Size);
	// 初期化処理
	pEffect->Init();
	return pEffect;
}