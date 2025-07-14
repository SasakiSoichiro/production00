//**********************************
//
// タイマー処理 [timer.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "timer.h"
#include "manager.h"


//*****************
// 静的メンバ変数
//*****************
#define TIME_SIZEX (20.0f)
#define TIME_SIZEY (30.0f)
//*****************
// 静的メンバ変数
//*****************
CNumber* CTimer::m_apMin[2] = {};
CNumber* CTimer::m_apSec[2] = {};
CSymbol* CTimer::m_pSymbol = NULL;
int CTimer::m_nTime = 0;
int CTimer::m_nFps = 0;
//=================
// コンストラクタ
//=================
CTimer::CTimer(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;
	}
}

//=================
// デストラクタ
//=================
CTimer::~CTimer()
{
}

//=================
// 初期化処理
//=================
HRESULT CTimer::Init(D3DXVECTOR3 pos)
{
	for (int nCntTime = 0; nCntTime < 2; nCntTime++)
	{
		m_apMin[nCntTime]->Init();
		m_apMin[nCntTime]->SetNumber(0);
		m_apMin[nCntTime]->SetSize(D3DXVECTOR2(TIME_SIZEX, TIME_SIZEY));
		m_apMin[nCntTime]->SetPos(D3DXVECTOR3((pos.x-20.0f) - TIME_SIZEX * nCntTime, pos.y, 0.0f));

		m_apSec[nCntTime]->Init();
		m_apSec[nCntTime]->SetNumber(0);
		m_apSec[nCntTime]->SetSize(D3DXVECTOR2(TIME_SIZEX, TIME_SIZEY));
		m_apSec[nCntTime]->SetPos(D3DXVECTOR3((pos.x + 40.0f) - TIME_SIZEX * nCntTime, pos.y, 0.0f));
	}
	m_pSymbol->Init();
	m_pSymbol->SetSize(D3DXVECTOR2(TIME_SIZEX-10.0f, TIME_SIZEY - 10.0f));
	m_pSymbol->SetPos(D3DXVECTOR3(pos.x, pos.y, 0.0f));

	return S_OK;
}

//=================
// 終了処理
//=================
void CTimer::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < 2; nCntTime++)
	{
		if (m_apMin[nCntTime] != NULL)
		{
			m_apMin[nCntTime]->Uninit();
			delete m_apMin[nCntTime];
			m_apMin[nCntTime] = NULL;
		}
		if (m_apSec[nCntTime] != NULL)
		{
			m_apSec[nCntTime]->Uninit();
			delete m_apSec[nCntTime];
			m_apSec[nCntTime] = NULL;
		}
	}
	if (m_pSymbol != NULL)
	{
		m_pSymbol->Uninit();
		delete m_pSymbol;
		m_pSymbol = NULL;

	}
	CObject::Release();
}

//=================
// 更新処理
//=================
void CTimer::Update(void)
{
	m_nFps++;
	if (m_nFps >= 60&& m_nTime>=0)
	{
		m_nTime--;
		m_nFps = 0;
	}
	int nData[2];
	nData[0] = 10; nData[1] = 1;
	int nMin = 0, nSec = 0;
	nMin = m_nTime / 60;
	nSec = m_nTime % 60;
	for (int nCntD = 0; nCntD < 2; nCntD++)
	{
		m_apMin[nCntD]->SetNumber((nMin % nData[0]) / nData[1]);
		m_apSec[nCntD]->SetNumber((nSec % nData[0]) / nData[1]);

		nData[0] *= 10;
		nData[1] *= 10;
	}

}

//=================
// 描画処理
//=================
void CTimer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	for (int nCntTime = 0; nCntTime < 2; nCntTime++)
	{

		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[0]));
		m_apMin[nCntTime]->Draw();
		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[0]));
		m_apSec[nCntTime]->Draw();
	}
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[1]));
	m_pSymbol->Draw();

}
CTimer* CTimer::Create(D3DXVECTOR3 pos,int nTime)
{
	CTimer* pTimer;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pTimer = new CTimer;
		for (int nCntTime = 0; nCntTime < 2; nCntTime++)
		{
			m_apMin[nCntTime] = new CNumber;
			m_apSec[nCntTime] = new CNumber;
			pTimer->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\number004.png");

		}
		m_pSymbol = new CSymbol;
		pTimer->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\Colon.png");


		pTimer->Init(pos);
		m_nTime = nTime;
		return pTimer;
	}
	return NULL;
}

void CTimer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CTimer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CTimer::SetTime(int nTime)
{
	m_nTime = nTime;
}
void CTimer::Add(int nTime)
{
	m_nTime += nTime;
}
