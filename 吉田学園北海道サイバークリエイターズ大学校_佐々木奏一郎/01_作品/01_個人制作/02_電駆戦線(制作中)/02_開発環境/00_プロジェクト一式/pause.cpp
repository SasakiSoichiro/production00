//**********************************
//
// ポーズ処理 [pause.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "pause.h"
#include "manager.h"

//*****************
// マクロ定義
//*****************
#define PAUSE_WIDTH (300.0f)
#define PAUSE_HEIGHT (100.0f)

//*****************
// 静的メンバ変数
//*****************
bool CPause::m_bPause = false;
//=================
// コンストラクタ
//=================
CPause::CPause(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;
}

//=================
// デストラクタ
//=================
CPause::~CPause()
{
}

//=================
// 初期化処理
//=================
HRESULT CPause::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	CObject2D::SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
	CTexture* pTexture = CManager::GetCTexture();

	return S_OK;

}

//=================
// 終了処理
//=================
void CPause::Uninit(void)
{
	CObject2D::Uninit();
}

//=================
// 更新処理
//=================
void CPause::Update(void)
{
}

//=================
// 描画処理
//=================
void CPause::Draw(void)
{
	if (m_bPause == true)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice;
		CTexture* pTexture = CManager::GetCTexture();
		CRenderer* renderer = CManager::GetCRenderer();
		pDevice = renderer->GetDevice();

		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
		CObject2D::Draw();
	}
}
CPause* CPause::Create(D3DXVECTOR3 pos)
{
	CPause* pPause;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pPause = new CPause;
		pPause->Init(pos);
		pPause->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\pause000.png");
		return pPause;
	}
	return NULL;
}
void CPause::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}
void CPause::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

D3DXVECTOR3 CPause::GetPos(void)
{
	return CObject2D::GetPos();
}
D3DXVECTOR2 CPause::GetSize(void)
{
	return CObject2D::GetSize();
}