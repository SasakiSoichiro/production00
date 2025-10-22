//*********************************
//
// エフェクト処理 [effect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// インクルード
//*******************
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"

//****************
// コンストラクタ
//****************
CEffect::CEffect(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;				
	m_nPatternAnim = 0;
	m_nIdxTexture = 0;
	m_nLife = 0;
	m_bLife = false;
}

//****************
// デストラクタ
//****************
CEffect::~CEffect()
{
}

//*************
// 初期化処理
//*************
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObjectBillboard::Init(pos);
	// テクスチャを割り当てる
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(texOffset, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(texOffset, 1.0f));
	m_nLife = maxLife;
	m_bLife = true;

	return S_OK;
}

//************
// 終了処理
//************
void CEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//************
// 更新処理
//************
void CEffect::Update(void)
{
	// 位置と向きと大きさと色情報の取得
	D3DXVECTOR3 pos = CObjectBillboard::GetPos();
	D3DXVECTOR3 rot = CObjectBillboard::GetRot();
	D3DXVECTOR2 size = CObjectBillboard::GetSize();
	D3DXCOLOR col = CObjectBillboard::GetCol();

	// アニメーションカウント加算
	m_nCntAnim++;
	if (m_nCntAnim >= anim)
	{// アニメーションカウントが3を超えたとき
		// アニメーションカウントを初期化する
		m_nCntAnim = 0;
		// アニメーションパターンを加算
		m_nPatternAnim++;
		// テクスチャ座標反映
		SetTex(D3DXVECTOR2(m_nPatternAnim * texOffset, 0.0f),
			D3DXVECTOR2(texOffset + m_nPatternAnim * texOffset, 0.0f),
			D3DXVECTOR2(m_nPatternAnim * texOffset, 1.0f),
			D3DXVECTOR2(texOffset + m_nPatternAnim * texOffset, 1.0f));

		if (m_nPatternAnim >= patternAnim)
		{// アニメーションパターンが4を超えた場合
			// アニメーションパターンを初期化する
			m_nPatternAnim = 0;
		}
	}

	// 寿命で終了
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//************
// 描画処理
//************
void CEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();

	pDevice = renderer->GetDevice();
	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
	CObjectBillboard::Draw();
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//*******************
// インスタンス生成 
//*******************
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,D3DXVECTOR2 size, int nLife,D3DXCOLOR col)
{
	CEffect* pExplosion;
	// テクスチャ情報取得
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// インスタンス生成
		pExplosion = new CEffect;
		// テクスチャ割り当て
		pExplosion->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\thunder005.png");
		// 初期化
		pExplosion->Init(pos);
		pExplosion->SetRot(rot);
		pExplosion->SetSize(size);
		pExplosion->SetCol(col);
		pExplosion->m_move = move;
		pExplosion->m_nLife = nLife;
		
		return pExplosion;
	}
	return NULL;
}

//****************
// 位置を設定
//****************
void CEffect::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//****************
// 向きを設定
//****************
void CEffect::SetRot(D3DXVECTOR3 rot)
{
	CObjectBillboard::SetRot(rot);
}

//****************
// 色を設定
//****************
void CEffect::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}

//****************
// 大きさを設定
//****************
void CEffect::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}

//****************
// 位置情報取得
//****************
D3DXVECTOR3 CEffect::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//****************
// 大きさ情報取得
//****************
D3DXVECTOR2 CEffect::GetSize(void)
{
	return CObjectBillboard::GetSize();
}