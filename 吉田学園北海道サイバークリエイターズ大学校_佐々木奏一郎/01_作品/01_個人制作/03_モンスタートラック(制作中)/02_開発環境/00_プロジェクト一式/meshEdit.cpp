//*****************************************
//
// ボルト処理 [bolt.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "meshEdit.h"
#include "manager.h"
#include "mesh.h"
#include "game.h"
#include "input.h"

//*****************
// コンストラクタ
//*****************
CMeshEdit::CMeshEdit(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// デストラクタ
//*****************
CMeshEdit::~CMeshEdit()
{
}

//******************
// インスタンス生成
//*******************
CMeshEdit* CMeshEdit::Create(D3DXVECTOR3 pos)
{
	CMeshEdit* pBlock;
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pBlock = new CMeshEdit;
		// 初期化
		pBlock->Init(pos);

		return pBlock;
	}

	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CMeshEdit::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\tire.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CMeshEdit::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CMeshEdit::Update(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// メッシュ取得
	CMesh* pMesh = CGame::GetCMesh();
	// 入力取得
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();

	if (pKeyboard->GetPress(DIK_0))
	{
		pMesh->MoveY(D3DXVECTOR3(pos));
	}

	if (pKeyboard->GetPress(DIK_UP))
	{
		pos.x += fSpeed;
	}
	if (pKeyboard->GetPress(DIK_DOWN))
	{
		pos.x -= fSpeed;
	}
	if (pKeyboard->GetPress(DIK_RIGHT))
	{
		pos.z += fSpeed;
	}
	if (pKeyboard->GetPress(DIK_LEFT))
	{
		pos.z -= fSpeed;
	}

	// 反映
	SetPos(pos);
}

//*****************
// 描画処理
//*****************
void CMeshEdit::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CMeshEdit::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CMeshEdit::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CMeshEdit::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// 向き情報の取得
//******************
D3DXVECTOR3 CMeshEdit::GetRot(void)
{
	return CObjectX::GetRot();
}