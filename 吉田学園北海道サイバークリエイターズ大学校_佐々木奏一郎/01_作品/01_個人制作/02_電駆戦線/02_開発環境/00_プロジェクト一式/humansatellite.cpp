//*****************************************
//
// 空の処理 [skydoom.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "humansatellite.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//******************
// マクロ定義
//******************
#define SPEED (0.0015f)

//*****************
// コンストラクタ
//*****************
CHumanSatellite::CHumanSatellite(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_fAngle = 0.0f;
}

//*****************
// デストラクタ
//*****************
CHumanSatellite::~CHumanSatellite()
{
}

//******************
// インスタンス生成
//*******************
CHumanSatellite* CHumanSatellite::Create(D3DXVECTOR3 pos)
{
	CHumanSatellite* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CHumanSatellite;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CHumanSatellite::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\satellite.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);

	SetRot(D3DXVECTOR3(0.2f, 0.5f, 0.3f));

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CHumanSatellite::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CHumanSatellite::Update(void)
{
	D3DXVECTOR3 pos = NONE;

	// ステージの周りを周る
	pos.x = sinf(m_fAngle) * 1200.0f;
	pos.y = 400.0f + cosf(m_fAngle) * 1200.0f;
	// 角度を進める
	m_fAngle += 0.005f;
	// 位置設定
	SetPos(pos);
}

//*****************
// 描画処理
//*****************
void CHumanSatellite::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CHumanSatellite::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CHumanSatellite::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CHumanSatellite::GetPos(void)
{
	return CObjectX::GetPos();
}
D3DXVECTOR3 CHumanSatellite::GetRot(void)
{
	return CObjectX::GetRot();
}