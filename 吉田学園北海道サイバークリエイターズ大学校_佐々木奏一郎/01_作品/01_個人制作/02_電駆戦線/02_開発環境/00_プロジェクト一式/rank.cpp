//*****************************************
//
// ランク処理 [rank.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "rank.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "score.h"

//*****************
// コンストラクタ
//*****************
CRank::CRank(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
}

//*****************
// デストラクタ
//*****************
CRank::~CRank()
{
}

//******************
// インスタンス生成
//*******************
CRank* CRank::Create(D3DXVECTOR3 pos)
{
	CRank* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CRank;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CRank::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\s.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\a.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\B.x");
	m_nIdxXFile[3] = pXModel->Register("data\\MODEL\\C.x");
	SetRank();
	// 初期化
	CObjectX::Init(pos);

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CRank::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CRank::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
	pCamera->Target(D3DXVECTOR3(0.0f, -30.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************
// 描画処理
//*****************
void CRank::Draw(void)
{
	CObjectX::Draw();// 描画
}

void CRank::SetRank(void)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	if (CScore::GetScore() > 45000)
	{
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[0]));
	}
	else if (CScore::GetScore() > 20000)
	{
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[1]));
	}
	else if (CScore::GetScore() > 3000)
	{
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));
	}
	else
	{
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[3]));
	}
}

//******************
// 位置の設定
//******************
void CRank::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CRank::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CRank::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CRank::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}