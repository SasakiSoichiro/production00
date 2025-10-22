//**********************************
//
// スコア処理 [score.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "resultScore.h"
#include "manager.h"
#include "score.h"
#include "number.h"
#include "renderer.h"
#include "texture.h"

//*******************
// マクロ定義
//*******************
#define SIZEX (80.0f)
#define SIZEY (120.0f)

//********************
// 静的メンバ変数宣言
//********************
CNumber* CResultScore::m_apNumber[MAX_DIGIT]{};

//=================
// コンストラクタ
//=================
CResultScore::CResultScore(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_nScore = 0;
}

//=================
// デストラクタ
//=================
CResultScore::~CResultScore()
{
}

//=================
// 初期化処理
//=================
HRESULT CResultScore::Init(D3DXVECTOR3 pos)
{
	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		m_apNumber[nCntD]->Init();
		m_apNumber[nCntD]->SetNumber(0);
		m_apNumber[nCntD]->SetSize(D3DXVECTOR2(SIZEX, SIZEY));
		m_apNumber[nCntD]->SetPos(D3DXVECTOR3(pos.x - SIZEX * nCntD, pos.y, 0.0f));
	}
	CTexture* pTexture = CManager::GetCTexture();
	m_nScore = CScore::GetScore();
	return S_OK;
}

//=================
// 終了処理
//=================
void CResultScore::Uninit(void)
{
	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		if (m_apNumber[nCntD] != NULL)
		{
			m_apNumber[nCntD]->Uninit();
			delete m_apNumber[nCntD];
			m_apNumber[nCntD] = NULL;
		}
	}
	CObject::Release();
}

//=================
// 更新処理
//=================
void CResultScore::Update(void)
{
	int nData[2];
	nData[0] = 10; nData[1] = 1;
	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		m_apNumber[nCntD]->SetNumber((m_nScore % nData[0]) / nData[1]);
		nData[0] *= 10;
		nData[1] *= 10;
	}
}

//=================
// 描画処理
//=================
void CResultScore::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
		m_apNumber[nCntD]->Draw();
	}
}
CResultScore* CResultScore::Create(D3DXVECTOR3 pos)
{
	CResultScore* pResultScore;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pResultScore = new CResultScore;
		for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
		{
			if (m_apNumber[nCntD] == NULL)
			{
				m_apNumber[nCntD] = new CNumber;
			}
		}
		pResultScore->Init(pos);
		pResultScore->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\number006.png");

		return pResultScore;
	}
	return NULL;
}

void CResultScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CResultScore::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
int CResultScore::Digit(int nScore)
{
	int nNum = nScore;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数
	while (nNum != 0)//割り切れなくなるまで繰り返す
	{
		nNum /= 10;//10で割る
		nKeepNum++;//桁数を加算
	}
	if (nScore == 0)
	{
		nKeepNum = 1;//一桁目が０の時
	}
	return nKeepNum;
}