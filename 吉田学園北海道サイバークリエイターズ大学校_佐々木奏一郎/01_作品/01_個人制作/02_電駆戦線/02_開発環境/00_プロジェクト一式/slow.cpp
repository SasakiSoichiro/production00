//**********************************
//
// コンボ処理 [combo.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "slow.h"

//****************
// マクロ定義
//****************
#define SLOW (4)

//*****************
// 静的メンバ変数
//*****************
float CSlow::m_fMulti=0.0f;
float CSlow::m_fDivi=0.0f;
int CSlow::m_nMulti=0;
int CSlow::m_nDivi=0;
int CSlow::m_nTime=0;



//*****************
// コンストラクタ
//*****************
CSlow::CSlow()
{
}

//*****************
// デストラクタ
//*****************
CSlow::~CSlow()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CSlow::Init(void)
{
	m_fMulti = 1.0f;
	m_fDivi = 1.0f;
	m_nMulti = 1;
	m_nDivi = 1;
	m_nTime = 0;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CSlow::Uninit(void)
{
}

//*****************
// 更新処理
//*****************
void CSlow::Update(void)
{
	if (m_nTime > 0)
	{
		m_fMulti = (int)SLOW;
		m_fDivi = 1.0 / SLOW;
		m_nMulti = SLOW;
	}
	else
	{
		m_fMulti = 1.0f;
		m_fDivi = 1.0f;
		m_nMulti = 1;
	}
	m_nTime--;
}

//*****************
// スロー発生処理
//*****************
void CSlow::Set(int nTime)
{
	m_nTime = nTime;
}