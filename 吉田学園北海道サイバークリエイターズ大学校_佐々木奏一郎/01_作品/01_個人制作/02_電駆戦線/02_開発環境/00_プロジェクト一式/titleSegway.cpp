//*****************************************
//
// タイトルのセグウェイ処理 [titleSegway.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "titleSegway.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************
// コンストラクタ
//*****************
CTitleSegway::CTitleSegway(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// デストラクタ
//*****************
CTitleSegway::~CTitleSegway()
{
}

//******************
// インスタンス生成
//*******************
CTitleSegway* CTitleSegway::Create(D3DXVECTOR3 pos)
{
	CTitleSegway* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CTitleSegway;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CTitleSegway::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\segwayTitle.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CTitleSegway::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CTitleSegway::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
	pCamera->Target(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************
// 描画処理
//*****************
void CTitleSegway::Draw(void)
{
	CObjectX::Draw();// 描画
}

//******************
// 位置の設定
//******************
void CTitleSegway::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CTitleSegway::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CTitleSegway::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CTitleSegway::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}