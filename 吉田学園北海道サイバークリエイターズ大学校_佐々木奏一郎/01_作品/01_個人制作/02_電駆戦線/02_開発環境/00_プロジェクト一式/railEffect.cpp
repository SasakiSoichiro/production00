//*********************************
//
// レールエフェクト処理 [railEffect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// インクルード
//*******************
#include "railEffect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "player.h"
#include "game.h"


//*******************
// マクロ定義
//*******************
#define EX_SIZE (30.0f)

//*****************
// コンストラクタ
//*****************
CRailEffect::CRailEffect(int nPriority) :CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;				// カウンターを初期化する
	m_nPatternAnim = 0;			// パターンNo.を初期化する
	m_nIdxTexture = 0;
	m_nLife = 0;
	m_bLife = false;
}

//***************
// デストラクタ
//***************
CRailEffect::~CRailEffect()
{
}

//*************
// 初期化処理
//*************
HRESULT CRailEffect::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\railThunder01.png");
	CObject3D::BindTexture(pTexture->GetAddres(m_nIdxTexture));
	CObject3D::Init(pos);
	// テクスチャを割り当てる
	CObject3D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.5f));
	m_nLife = 20;
	m_bLife = true;
	m_nPatternAnim = rand() % 4;
	return S_OK;
}

//************
// 終了処理
//************
void CRailEffect::Uninit(void)
{
	CObject3D::Uninit();
}

//***********
// 更新処理
//***********
void CRailEffect::Update(void)
{
	static float fData = 0.5f;
	CPlayer* pPlayer = CGame::GetCPlayer();

	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 rot = CObject3D::GetRot();
	CPlayer::STATE state = pPlayer->GetState();

	m_move.x = sinf(rot.y)*3.0f;
	m_move.z = cosf(rot.y)*3.0f;

	pos += m_move;
	SetPos(pos);

	//アニメーションカウント加算
	m_nCntAnim++;
	m_nLife--;

	if (m_nCntAnim >= 4)
	{//アニメーションカウントが7を超えたとき
		//アニメーションカウントを初期化する
		m_nCntAnim = 0;
		//アニメーションパターンを加算
		m_nPatternAnim++;
		SetTex(D3DXVECTOR2(m_nPatternAnim * fData, (m_nPatternAnim / 2) * fData),
			D3DXVECTOR2(m_nPatternAnim * fData+fData, (m_nPatternAnim / 2) * fData + fData));

		if (m_nPatternAnim >= 4)
		{// アニメーションパターンが4を超えた場合
			// アニメーションパターンを初期化する
			m_nPatternAnim = 0;
		}
	}
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//***********
// 描画処理
//***********
void CRailEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CObject3D::Draw();
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//******************
// インスタンス生成 
//******************
CRailEffect* CRailEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size)
{
	CRailEffect* pRailEffect;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pRailEffect = new CRailEffect;
		pRailEffect->Init(pos);
		pRailEffect->SetRot(rot);
		pRailEffect->SetSize(size);

		return pRailEffect;
	}
	return NULL;
}

//**************
// 位置を設定
//**************
void CRailEffect::SetPos(D3DXVECTOR3 pos)
{
	CObject3D::SetPos(pos);
}

//**************
// 色を設定
//**************
void CRailEffect::SetCol(D3DXCOLOR col)
{
	CObject3D::SetCol(col);
}

//**************
// 大きさを設定
//**************
void CRailEffect::SetSize(D3DXVECTOR2 size)
{
	CObject3D::SetSize(size);
}

//**************
// 位置情報取得
//**************
D3DXVECTOR3 CRailEffect::GetPos(void)
{
	D3DXVECTOR3 pos = CObject3D::GetPos();
	return pos;
}

//****************
// 大きさ情報取得
//****************
D3DXVECTOR2 CRailEffect::GetSize(void)
{
	return CObject3D::GetSize();
}