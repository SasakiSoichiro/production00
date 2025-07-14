//**********************************
//
// 体力UI処理 [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "lifeUI.h"
#include "manager.h"

//*****************
// 静的メンバ変数
//*****************
CNumber* CLifeUI::m_apNumber[3] = {};	// ナンバーへのポインタ
CSymbol* CLifeUI::m_pSymbol = NULL;		// コロンへのポインタ

//*****************
// コンストラクタ
//*****************
CLifeUI::CLifeUI(int nPriority) :CObject2DMulti(nPriority)
{
	// テクスチャ枚数分
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	// インデックス
	}

	m_size = D3DXVECTOR2(0.0f, 0.0f);	// 大きさ
	m_fLife = 100.0f;					// 体力
	m_nDigit = 0;						// 桁数
}

//*****************
// デストラクタ
//*****************
CLifeUI::~CLifeUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CLifeUI::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ取得
	CObject2DMulti::Init(pos);						// 2Dの初期化
	// テクスチャを割り当てる
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]), pTexture->GetAddres(m_nIdxTexture[1]));

	// UVの設定
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// テクスチャの緑部分が移るように設定
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.5f, 1.0f));

	// 大きさの設定
	CObject2DMulti::SetSize(D3DXVECTOR2(170.0f, 100.0f));

	// ナンバーのポインタ初期化
	for (int nCntD = 0; nCntD < 3; nCntD++)
	{
		// 初期化
		m_apNumber[nCntD]->Init();
		// ナンバー設定
		m_apNumber[nCntD]->SetNumber(0);											
		// 大きさ設定
		m_apNumber[nCntD]->SetSize(D3DXVECTOR2(20.0f, 30.0f));
		// 位置設定(スクリーン右上)
		m_apNumber[nCntD]->SetPos(D3DXVECTOR3((pos.x-115.0f) - 20.0f * nCntD, pos.y, 0.0f));	
	}

	// 記号のポインタ初期化
	// 初期化
	m_pSymbol->Init();
	// 大きさ
	m_pSymbol->SetSize(D3DXVECTOR2(20.0f, 30.0f));		
	// 位置設定
	m_pSymbol->SetPos(D3DXVECTOR3((pos.x - 95.0f), pos.y, 0.0f));	
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CLifeUI::Uninit(void)
{
	// ナンバーのポインタ終了処理
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULLじゃなかったら

			// 終了処理
			m_apNumber[nCnt]->Uninit();
			// 解放
			delete m_apNumber[nCnt];
			// NULLを代入
			m_apNumber[nCnt] = NULL;
		}
	}

	// 記号のポインタ終了処理
	if (m_pSymbol != NULL)
	{// NULLじゃなかったら

		// 終了処理
		m_pSymbol->Uninit();
		// 解放
		delete m_pSymbol;
		// NULLを代入
		m_pSymbol = NULL;	
	}

	// 終了処理
	CObject2DMulti::Uninit();
}

//*****************
// 更新処理
//*****************
void CLifeUI::Update(void)
{
	m_fLife -= 0.01f;				// ライフを減らす
	float fLife = 100.0f - m_fLife;	// 計算用
	float p = fLife / 100.0f;		// 1から100の値に直す

	// UV座標(割合に応じて色が変わるように計算)
	CObject2DMulti::SetTex2(D3DXVECTOR2(p * 0.5f, 0.0f),
		D3DXVECTOR2(0.5f + p * 0.5f, 0.0f),
		D3DXVECTOR2(p * 0.5f, 1.0f),
		D3DXVECTOR2(0.5f + p * 0.5f, 1.0f));

	int nData[2];	// 計算用

	// 計算用の値を代入
	nData[0] = 10; 
	nData[1] = 1;

	// ナンバーに値を設定
	for (int nCntD = 0; nCntD < 3; nCntD++)
	{
		// 計算して値を1桁ずつ設定
		m_apNumber[nCntD]->SetNumber(((int)m_fLife % nData[0]) / nData[1]);
		nData[0] *= 10;
		nData[1] *= 10;
	}
}

//*****************
// 描画処理
//*****************
void CLifeUI::Draw(void)
{
	// 描画処理
	CObject2DMulti::Draw();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;						// デバイス
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ取得
	CRenderer* renderer = CManager::GetCRenderer();	// レンダラーのポインタ取得
	pDevice = renderer->GetDevice();				// デバイス取得

	// ナンバー桁数分描画
	for (int nCntD = 0; nCntD < Digit((int)m_fLife); nCntD++)
	{
		// テクスチャ設定
		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[2]));
		// 描画
		m_apNumber[nCntD]->Draw();
	}
	// 記号描画
	// テクスチャ設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[3]));
	// 描画
	m_pSymbol->Draw();
}

//******************
// インスタンス生成
//******************
CLifeUI* CLifeUI::Create(D3DXVECTOR3 pos)
{
	CLifeUI* pLifeUI;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		pLifeUI = new CLifeUI;// インスタンス生成
		// マルチテクスチャ1枚目(電池の画像)
		pLifeUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\enegy.png");
		// マルチテクスチャ2枚目(緑・白の二色の画像)
		pLifeUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\green001.jpg");
		// 数字テクスチャ
		pLifeUI->m_nIdxTexture[2] = pTexture->Register("data\\TEXTURE\\number000.png");
		// 記号テクスチャ(%の画像)
		pLifeUI->m_nIdxTexture[3] = pTexture->Register("data\\TEXTURE\\percent000.png");

		// ナンバーのインスタンス生成
		for (int nCntD = 0; nCntD < 3; nCntD++)
		{
			if (m_apNumber[nCntD] == NULL)
			{// NULLだったら
				m_apNumber[nCntD] = new CNumber;	// インスタンス生成
			}
		}
		// 記号のインスタンス生成
		if (m_pSymbol == NULL)
		{// NULLだったら
			m_pSymbol = new CSymbol;	// インスタンス生成
		}

		// 初期化
		pLifeUI->Init(pos);

		// 情報を渡す
		return pLifeUI;
	}

	// (失敗したら)NULLを返す
	return NULL;
}

//*****************
// 位置設定
//*****************
void CLifeUI::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2DMulti::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CLifeUI::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2DMulti::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CLifeUI::GetPos(void)
{
	// 位置情報取得
	return CObject2DMulti::GetPos();
}

//*****************
// 桁数を返す
//*****************
int CLifeUI::Digit(int nScore)
{
	int nNum = nScore;	// スコアの0の部分をカウント
	int nKeepNum = 0;	// スコアの桁数

	// 割り切れなくなるまで繰り返す
	while (nNum != 0)	
	{
		nNum /= 10;// 10で割る
		nKeepNum++;// 桁数を加算
	}
	if (nScore == 0)
	{
		nKeepNum = 1;// 1桁目が０の時
	}

	// 現在の桁を返す
	return nKeepNum;
}