//**********************************
//
// 敵の体力UI処理 [enemyLifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "enemyLifeUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//*****************
// コンストラクタ
//*****************
CEnemyLifeUI::CEnemyLifeUI(int nPriority) :CObjectBillboard(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;
	}
	m_nIdx = 0;
	m_nUseTexture = 0;
}

//*****************
// デストラクタ
//*****************
CEnemyLifeUI::~CEnemyLifeUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CEnemyLifeUI::Init(D3DXVECTOR3 pos)
{
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();

	CObjectBillboard::Init(pos);

	// テクスチャ座標の設定
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// 大きさの設定
	CObjectBillboard::SetSize(D3DXVECTOR2(5.0f, 5.0f));
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CEnemyLifeUI::Uninit(void)
{
	// 終了処理
	CObjectBillboard::Uninit();
}

//*****************
// 更新処理
//*****************
void CEnemyLifeUI::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CEnemyLifeUI::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[m_nUseTexture]));
	pDevice->SetTexture(1,NULL);

	CObjectBillboard::Draw();
}

//******************
// インスタンス生成
//******************
CEnemyLifeUI* CEnemyLifeUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 offset,int nIdx)
{
	CEnemyLifeUI* pEnemyUI;
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();	

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		pEnemyUI = new CEnemyLifeUI;
		// テクスチャ
		pEnemyUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\memori.png");
		// テクスチャ
		pEnemyUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\memori01.png");
		// 初期化
		pEnemyUI->Init(pos);

		pEnemyUI->m_nIdx=nIdx;

		pEnemyUI->SetOffset(offset);

		return pEnemyUI;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CEnemyLifeUI::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CEnemyLifeUI::SetRot(D3DXVECTOR3 rot)
{
	CObjectBillboard::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CEnemyLifeUI::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//*****************
// UI表示の設定
//*****************
void CEnemyLifeUI::SetLife(int nLife)
{
	// テクスチャを入れ替える
	if (m_nIdx > nLife)
	{
		m_nUseTexture = 1;
	}
}