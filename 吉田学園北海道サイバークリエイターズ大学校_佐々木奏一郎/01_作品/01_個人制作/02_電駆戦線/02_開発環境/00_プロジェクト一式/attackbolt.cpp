//*****************************************
//
// ブロック処理 [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "attackbolt.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"

//**********************
// 静的メンバ変数初期化
//**********************
const D3DXVECTOR3 CAttackBolt::ROT_MOVE = D3DXVECTOR3(0.08f, 0.05f, 0.1f);

//*****************
// コンストラクタ
//*****************
CAttackBolt::CAttackBolt(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_move = NONE;
	m_fAngle = 0.0f;
	m_nLife = 0;
	SetType(TYPE_BOLT);
}

//*****************
// デストラクタ
//*****************
CAttackBolt::~CAttackBolt()
{
}

//******************
// インスタンス生成
//*******************
CAttackBolt* CAttackBolt::Create(D3DXVECTOR3 pos,float fAngle)
{
	CAttackBolt* pAttackBolt;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pAttackBolt = new CAttackBolt;	
		pAttackBolt->Init(pos);			
		pAttackBolt->SetAngle(fAngle);

		return pAttackBolt;				
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CAttackBolt::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\bolt.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);
	m_move.y = jump;
	m_nLife = maxLife;

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CAttackBolt::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CAttackBolt::Update(void)
{
	// 情報取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// ムーブ値を求める
	m_move.x = sinf(m_fAngle) * speed;
	m_move.y -= horizon;
	m_move.z = cosf(m_fAngle) * speed;

	// 位置更新
	pos += m_move;
	rot += ROT_MOVE;

	// 値を反映
	SetRot(rot);
	SetPos(pos);

	// 寿命で終了
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CAttackBolt::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CAttackBolt::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CAttackBolt::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CAttackBolt::GetPos(void)
{
	return CObjectX::GetPos();
}
D3DXVECTOR3 CAttackBolt::GetRot(void)
{
	return CObjectX::GetRot();
}