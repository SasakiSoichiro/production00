//**************************************
//
// 散るエフェクト処理 [sparkEffect.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// インクルード
//*******************
#include "sparkEffect.h"
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
#define EX_SIZE (10.0f)

//=================
// コンストラクタ
//=================
CSparkEffect::CSparkEffect(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_nLife = 0;
}

//=================
// デストラクタ
//=================
CSparkEffect::~CSparkEffect()
{
}

//=================
// 初期化処理
//=================
HRESULT CSparkEffect::Init(D3DXVECTOR3 pos)
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
void CSparkEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=================
// 更新処理
//=================
void CSparkEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerPosOld = pPlayer->GetPos();
	D3DXVECTOR3 vec;

	vec.x = (playerPos.x - pos.x);
	vec.y = (playerPos.y + 25.0f - pos.y);
	vec.z = (playerPos.z - pos.z);

	//pos = playerPos + vec;

	pos += m_move;

	SetPos(pos);
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//=================
// 描画処理
//=================
void CSparkEffect::Draw(void)
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
CSparkEffect* CSparkEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	CSparkEffect* pSmoke;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pSmoke = new CSparkEffect;
		pSmoke->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\effect000.jpg");
		pSmoke->Init(pos);
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
void CSparkEffect::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}
void CSparkEffect::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}
void CSparkEffect::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}
D3DXVECTOR3 CSparkEffect::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

D3DXVECTOR2 CSparkEffect::GetSize(void)
{
	return CObjectBillboard::GetSize();
}