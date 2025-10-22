//**************************************
//
// 集まるエフェクト処理 [gatherEffect.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// インクルード
//*******************
#include "gatherEffect.h"
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

//******************
// コンストラクタ
//******************
CGatherEffect::CGatherEffect(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_nLife = 0;
}

//******************
// デストラクタ
//******************
CGatherEffect::~CGatherEffect()
{
}

//******************
// 初期化処理
//******************
HRESULT CGatherEffect::Init(D3DXVECTOR3 pos)
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

//******************
// 終了処理
//******************
void CGatherEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//******************
// 更新処理
//******************
void CGatherEffect::Update(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// プレイヤーの位置と前フレームの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerPosOld = pPlayer->GetPos();
	D3DXVECTOR3 vec;

	// プレイヤーへのベクトル
	vec.x = (playerPos.x - pos.x);
	vec.y = (playerPos.y + 25.0f - pos.y);
	vec.z = (playerPos.z - pos.z);

	// プレイヤーへ動く
	pos = playerPos + vec;
	m_move.x = (playerPos.x - pos.x) * 0.05f;
	m_move.y = (playerPos.y+25.0f - pos.y) * 0.05f;
	m_move.z = (playerPos.z - pos.z) * 0.05f;
	pos += m_move;

	// 反映
	SetPos(pos);

	// 寿命で消す
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//******************
// 描画処理
//******************
void CGatherEffect::Draw(void)
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

//******************
// インスタンス生成 
//******************
CGatherEffect* CGatherEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	// 自身のポインタ
	CGatherEffect* pSmoke;
	// テクスチャ取得
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// インスタンス生成
		pSmoke = new CGatherEffect;
		// テクスチャ
		pSmoke->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\effect000.jpg");
		// 初期化
		pSmoke->Init(pos);
		pSmoke->SetSize(size);
		pSmoke->SetCol(col);
		pSmoke->m_nLife = nLife;


		return pSmoke;
	}
	return NULL;
}

//******************
// 位置を設定
//******************
void CGatherEffect::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//******************
// 色を設定
//******************
void CGatherEffect::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}

//******************
// 大きさを設定
//******************
void CGatherEffect::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}

//******************
// 位置情報を取得
//******************
D3DXVECTOR3 CGatherEffect::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//******************
// 大きさ情報を取得
//******************
D3DXVECTOR2 CGatherEffect::GetSize(void)
{
	return CObjectBillboard::GetSize();
}