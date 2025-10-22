//*****************************************
//
// ウェーブ処理 [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "wave.h"
#include "enemy.h"
#include <iostream>
#include <fstream>
#include "debugproc.h"
#include "texture.h"
#include "manager.h"
#include <cmath>
#include "game.h"
#include "number.h"
#include "renderer.h"
#include "sound.h"

//**********************
// 静的メンバ変数初期化
//**********************
int CWave::m_nCurrent = 0;
int CWave::m_nAll = 0;
CNumber* CWave::m_pNumber=NULL;



//*****************
// コンストラクタ
//*****************
CWave::CWave(int nPriority) :CObject2D(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;
	}
	m_nScreenTime = 0;
	m_bScreen = false;
	m_bGo = false;
	m_bStop = false;
	m_bEnd = false;
	m_fCnt = 0.0f;
}

//*****************
// デストラクタ
//*****************
CWave::~CWave()
{
}

//******************
// インスタンス生成
//******************
CWave* CWave::Create(D3DXVECTOR3 pos)
{
	CWave* pWave;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		pWave = new CWave;// インスタンス生成
		// テクスチャ
		pWave->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\wave.png");
		pWave->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\number017.png");
		pWave->m_pNumber = new CNumber;
		// 初期化
		pWave->Init(pos);

		// 情報を渡す
		return pWave;
	}

	// (失敗したら)NULLを返す
	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CWave::Init(D3DXVECTOR3 pos)
{
	m_nAll = 3;
	m_nCurrent = 0;
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]));

	CObject2D::Init(pos);						// 2Dの初期化

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// 大きさの設定
	CObject2D::SetSize(D3DXVECTOR2(300.0f, 70.0f));
	// 記号のポインタ初期化
	// 初期化
	m_pNumber->Init();
	// 大きさ
	m_pNumber->SetSize(D3DXVECTOR2(40.0f, 55.0f));
	m_pNumber->SetNumber(0);
	// 位置設定
	m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));


	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CWave::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	CObject2D::Uninit();						// 2Dの初期化
}

//*****************
// 更新処理
//*****************
void CWave::Update(void)
{
	int nNum=CEnemy::GetNumAll();
	CSound* pSound = CManager::GetCSound();
	CDebugProc::Print("現在のウェーブ:%d", m_nCurrent);
	if (nNum <= 0)
	{
		if (m_nAll > m_nCurrent)
		{
			
			Load(m_nCurrent);
			m_nCurrent++;
			m_nScreenTime = 60;
			m_bScreen = true;
			pSound->Play(CSound::LABEL_SE00);
		}
		else
		{
			CGame::SetState(CGame::STATE_END);
		}
	}
	Move();
	m_pNumber->SetNumber(m_nCurrent);
}
//*****************
// 描画処理
//*****************
void CWave::Draw(void)
{
	CObject2D::Draw();
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;						// デバイス
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ取得
	CRenderer* renderer = CManager::GetCRenderer();	// レンダラーのポインタ取得
	pDevice = renderer->GetDevice();				// デバイス取得
	// 記号描画
	// テクスチャ設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[1]));
	m_pNumber->Draw();
}


void CWave::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}
void CWave::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}
D3DXVECTOR3 CWave::GetPos(void)
{
	return CObject2D::GetPos();
}

void CWave::Load(int nWave)
{

	std::ifstream file(WAVE[nWave]);
	
	int nType = 0;
	int nCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (file.is_open() == false)
	{
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		int scan = sscanf(line.c_str(),
			"pos = %f %f %f : type %d",
			&pos.x, &pos.y, &pos.z,&nType);

		CEnemy::Create(pos, nType);
		nCnt++;
	}
	// ファイルを明示的に閉じる
	file.close();
}

void CWave::Move(void)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_bScreen == true)
	{
		SetPos(D3DXVECTOR3(-100.0f, 150.0f, 0.0f));
		m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
		m_bScreen = false;
		m_bGo = true;
		m_fCnt = 0.0f;
	}
	if (m_bGo == true)
	{
		if (m_fCnt < 1.0f)
		{
			pos.x = -100.0f + ((SCREEN_WIDTH/2.0f) + 100.0f) * (1.0f - std::pow(1.0f - m_fCnt, 5.0f));
			SetPos(D3DXVECTOR3(pos.x, 150.0f, 0.0f));
			m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
			m_fCnt += 0.01f;
		}
		else
		{
			m_bGo = false;
			m_bStop = true;
			m_fCnt = 0.0f;
		}
	}
	else if (m_bStop == true)
	{
		if (m_nScreenTime <= 0)
		{
			m_bEnd = true;
			m_bStop = false;
		}
		m_nScreenTime--;
	}
	else if (m_bEnd == true)
	{
		if (m_fCnt < 1.0f)
		{
			pos.x = (SCREEN_WIDTH / 2.0f) + (1500.0f - (SCREEN_WIDTH / 2.0f)) * (1.0f - std::pow(1.0f - m_fCnt, 5.0f));
			SetPos(D3DXVECTOR3(pos.x, 150.0f, 0.0f));
			m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
			m_fCnt += 0.01f;
		}
		else
		{
			m_bEnd = false;
			m_fCnt += 0.0f;
		}
	}

}