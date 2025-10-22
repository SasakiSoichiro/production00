//*****************************************
//
// ブロック処理 [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "jempiece.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"

//*****************
// マクロ定義
//*****************
#define HORIZON (0.08f)

//*****************
// コンストラクタ
//*****************
CJemPiece::CJemPiece(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_move = NONE;
	m_nLife = 0;
	m_nType = 0;
	m_fAngle = 0.0f;
}

//*****************
// デストラクタ
//*****************
CJemPiece::~CJemPiece()
{
}

//******************
// インスタンス生成
//*******************
CJemPiece* CJemPiece::Create(D3DXVECTOR3 pos, float fAngle,int nType)
{
	CJemPiece* pAttackBolt;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pAttackBolt = new CJemPiece;	// インスタンス生成
		pAttackBolt->m_nType = nType;	// 種類
		pAttackBolt->m_fAngle = fAngle;	// 向き
		pAttackBolt->Init(pos);			// 初期化
		return pAttackBolt;				// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CJemPiece::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	switch (m_nType)
	{
	case 0:
		// 使うモデルのインデックスを入れる
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece00.x");
		break;
	case 1:
		// 使うモデルのインデックスを入れる
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece01.x");
		break;
	case 2:
		// 使うモデルのインデックスを入れる
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece02.x");
		break;
	}
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);
	m_move.y = rand()%50*0.1f;
	m_nLife = 80;

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CJemPiece::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CJemPiece::Update(void)
{
	// 位置と大きさ取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// 動く値の設定
	m_move.x = sinf(m_fAngle) * 1.5f;
	m_move.y -= HORIZON;
	m_move.z = cosf(m_fAngle) * 1.5f;

	// 大きさを小さくする
	size *= 0.98f;

	pos += m_move;

	// 位置と大きさ設定
	SetPos(pos);
	SetSize(size);

	// 寿命を減らす
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CJemPiece::Draw(void)
{
	CObjectX::Draw();// 描画
}

//******************
// 位置の設定
//******************
void CJemPiece::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CJemPiece::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CJemPiece::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CJemPiece::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}