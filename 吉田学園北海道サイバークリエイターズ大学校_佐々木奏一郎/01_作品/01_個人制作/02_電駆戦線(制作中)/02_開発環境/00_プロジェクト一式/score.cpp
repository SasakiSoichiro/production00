//**********************************
//
// スコア処理 [score.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "score.h"
#include "manager.h"

// 静的メンバ変数
CNumber* CScore::m_apNumber[MAX_DIGIT] = {};
int CScore::m_nScore = 0;
//=================
// コンストラクタ
//=================
CScore::CScore(int nPriority) :CObject(nPriority)
{
	m_pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_nIdxTexture = 0;
}

//=================
// デストラクタ
//=================
CScore::~CScore()
{
}

//=================
// 初期化処理
//=================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		m_apNumber[nCntD]->Init();
		m_apNumber[nCntD]->SetNumber(0);
		m_apNumber[nCntD]->SetSize(D3DXVECTOR2(40.0f, 60.0f));
		m_apNumber[nCntD]->SetPos(D3DXVECTOR3(1250.0f-40.0f*nCntD, 30.0f, 0.0f));
	}
	CTexture* pTexture = CManager::GetCTexture();

	return S_OK;
}

//=================
// 終了処理
//=================
void CScore::Uninit(void)
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
void CScore::Update(void)
{
	int nData[2];
	nData[0] = 10; nData[1] = 1;
	for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
	{
		m_apNumber[nCntD]->SetNumber((m_nScore%nData[0])/nData[1]);
		nData[0] *= 10;
		nData[1] *= 10;
	}
}

//=================
// 描画処理
//=================
void CScore::Draw(void)
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
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pScore = new CScore;
		for (int nCntD = 0; nCntD < MAX_DIGIT; nCntD++)
		{
			if (m_apNumber[nCntD] == NULL)
			{
				m_apNumber[nCntD] = new CNumber;
			}
		}
		pScore->Init(pos);
		pScore->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\number000.png");

		return pScore;
	}
	return NULL;
}

void CScore::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CScore::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}
void CScore::Add(int nValue)
{
	m_nScore += nValue;
}
int CScore::Digit(int nScore)
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