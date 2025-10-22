//**************************************
//
// 煙処理 [smoke.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// インクルード
//*******************
#include "smoke.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"

//*******************
// マクロ定義
//*******************
#define EX_SIZE (30.0f)

//=================
// コンストラクタ
//=================
CSmoke::CSmoke(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_nLife = 0;
}

//=================
// デストラクタ
//=================
CSmoke::~CSmoke()
{
}

//=================
// 初期化処理
//=================
HRESULT CSmoke::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObjectBillboard::Init(pos);
	// テクスチャを割り当てる
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	m_nLife = 60;
	return S_OK;
}

//=================
// 終了処理
//=================
void CSmoke::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=================
// 更新処理
//=================
void CSmoke::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXCOLOR col = GetCol();
	pos += m_move;
	col.a -= 0.01f;
	SetPos(pos);
	SetCol(col);
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=================
// 描画処理
//=================
void CSmoke::Draw(void)
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
	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
	CObjectBillboard::Draw();
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==================
// インスタンス生成 
//==================
CSmoke* CSmoke::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	CSmoke* pSmoke;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pSmoke = new CSmoke;
		pSmoke->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\smoke.jpg");
		pSmoke->Init(pos);
		pSmoke->SetRot(rot);
		pSmoke->SetSize(size);
		pSmoke->SetCol(col);
		pSmoke->m_move = move;
		pSmoke->m_nLife = nLife;


		return pSmoke;
	}
	return NULL;
}

//===================
// 位置を設定
//===================
void CSmoke::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}
void CSmoke::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}
void CSmoke::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}
D3DXVECTOR3 CSmoke::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

D3DXVECTOR2 CSmoke::GetSize(void)
{
	return CObjectBillboard::GetSize();
}