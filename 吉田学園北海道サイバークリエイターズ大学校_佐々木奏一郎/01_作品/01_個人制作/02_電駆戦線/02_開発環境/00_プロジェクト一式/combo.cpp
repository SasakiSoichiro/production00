//**********************************
//
// コンボ処理 [combo.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "combo.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "numbermulti.h"

//**********************
// 静的メンバ変数初期化
//**********************
CNumberMulti* CCombo::m_pNumberMulti[2]={};
int CCombo::m_nCurrent = 0;
int CCombo::m_nTime = 0;
int CCombo::m_nScore = 0;
const D3DXCOLOR CCombo::COMBO_ON = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR CCombo::COMBO_OFF = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

//*****************
// コンストラクタ
//*****************
CCombo::CCombo(int nPriority) :CObject(nPriority)
{
}

//*****************
// デストラクタ
//*****************
CCombo::~CCombo()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CCombo::Init(D3DXVECTOR3 pos)
{
	// 数字の位置と色初期化
	m_pNumberMulti[0]->SetPos(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f));
	m_pNumberMulti[1]->SetPos(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f));
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumberMulti[nCnt]->SetCol(COMBO_OFF);
	}
	m_nCurrent = 0;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CCombo::Uninit(void)
{
	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CCombo::Update(void)
{
	// コンボ終了時のリセット
	Reset();

	// コンボ数の表示
	Set();

	// タイマーを減らす
	m_nTime--;
}

//*****************
// 描画処理
//*****************
void CCombo::Draw(void)
{

}

//******************
// インスタンス生成
//******************
CCombo* CCombo::Create(D3DXVECTOR3 pos)
{
	CCombo* TitleUI;
	// テクスチャ情報取得
	CTexture* pTexture = CManager::GetCTexture();	

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		TitleUI = new CCombo;
		// テクスチャ
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			TitleUI->m_pNumberMulti[nCnt] = CNumberMulti::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));
		}

		// 初期化
		TitleUI->Init(pos);

		return TitleUI;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CCombo::SetPos(D3DXVECTOR3 pos)
{
	m_pNumberMulti[0]->SetPos(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f));
	m_pNumberMulti[1]->SetPos(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f));
}

//*****************
// 向き設定
//*****************
void CCombo::SetRot(D3DXVECTOR3 rot)
{
	m_pNumberMulti[0]->SetRot(rot);
	m_pNumberMulti[1]->SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CCombo::GetPos(void)
{
	return NONE;
}

//*****************
// 桁数を返す
//*****************
int CCombo::Digit(int nScore)
{
	int nNum = nScore;
	int nKeepNum = 0;

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

	return nKeepNum;
}

//*************
// コンボ加算
//*************
void CCombo::Add(int nScore)
{
	// サウンド情報の取得とSE再生
	CSound* pSound = CManager::GetCSound();
	pSound->Play(CSound::LABEL_SE07);

	// コンボ数加算
	m_nCurrent++;
	m_nTime = maxTime;
	m_nScore += nScore;
}

//****************
// コンボ数の表示
//****************
void CCombo::Set(void)
{
	int nData[2], nTime;

	// 初期化
	nData[0] = 10;
	nData[1] = 1;
	nTime = m_nTime / (maxTime/100);

	// ナンバーに値を設定
	for (int nCntD = 0; nCntD < 2; nCntD++)
	{
		// 計算して値を1桁ずつ設定
		m_pNumberMulti[nCntD]->SetNumber((m_nCurrent % nData[0]) / nData[1]);
		m_pNumberMulti[nCntD]->SetGauge(nTime);
		nData[0] *= 10;
		nData[1] *= 10;
		m_pNumberMulti[nCntD]->SetCol(COMBO_OFF);
	}

	// ナンバー桁数分描画
	if (m_nCurrent >= 1)
	{
		for (int nCntD = 0; nCntD < Digit(m_nCurrent); nCntD++)
		{
			m_pNumberMulti[nCntD]->SetCol(COMBO_ON);
		}
	}
}

//*************
// コンボ終了
//*************
void CCombo::Reset(void)
{
	// ゲーム状態の取得
	CGame::STATE state = CGame::GetState();
	if (m_nTime <= 0|| state==CGame::STATE_END)
	{// 時間経過orゲーム終了したら

		// コンボ数に応じてスコア加算
		int nFinishCombo = m_nCurrent;
		CScore::Add(m_nScore * nFinishCombo);

		// 初期化
		m_nCurrent = 0;
		m_nTime = 0;
		m_nScore = 0;
	}
	
}