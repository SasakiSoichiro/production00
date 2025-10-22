//*****************************************
//
// スタンド処理 [stand.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "stand.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************
// コンストラクタ
//*****************
CStand::CStand(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// デストラクタ
//*****************
CStand::~CStand()
{
}

//******************
// インスタンス生成
//*******************
CStand* CStand::Create(D3DXVECTOR3 pos)
{
	CStand* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CStand;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CStand::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\stand.x");
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
void CStand::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CStand::Update(void)
{
}

//*****************
// 描画処理
//*****************
void CStand::Draw(void)
{
	CObjectX::Draw();// 描画
}

//******************
// 位置の設定
//******************
void CStand::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CStand::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CStand::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CStand::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}