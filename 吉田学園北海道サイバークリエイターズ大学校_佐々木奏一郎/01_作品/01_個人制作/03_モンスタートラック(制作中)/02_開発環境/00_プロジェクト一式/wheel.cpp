//*****************************************
//
// 電気柵処理 [fence.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "wheel.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sound.h"
#include "mesh.h"
#include "carBody.h"

//******************
// マクロ定義
//******************
#define DISTANCE (150.0f)	// 支柱の距離
#define RADIUS (90.0f)		// 攻撃の半径

//*****************
// コンストラクタ
//*****************
CWheel::CWheel(int nPriority)
{
	m_fOffset = 0.0f;
	m_fSuspension = 0.0f;
	m_fSuspensionOld = 0.0f;
	m_fDeltaHeight = 0.0f;
	m_fAttachY = 0.0f;
	m_pCarBody = nullptr;
}

//*****************
// デストラクタ
//*****************
CWheel::~CWheel()
{
}

//******************
// インスタンス生成
//*******************
CWheel* CWheel::Create(D3DXVECTOR3 pos, const char* pFileName)
{
	// 自身のポインタ
	CWheel* pWheel;
	// XModel取得
	CXModel* pXModel = CManager::GetCXModel();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pWheel = new CWheel;

		pWheel->SetIdxXFile(pXModel->Register(pFileName));
		// 初期化
		pWheel->Init(pos);

		return pWheel;
	}

	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CWheel::Init(D3DXVECTOR3 pos)
{
	CModel::Init(pos);
	m_fSuspension = fSusRest;
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CWheel::Uninit(void)
{
	CModel::Uninit();
}

//*****************
// 更新処理
//*****************
void CWheel::Update(void)
{
	// メッシュとの当たり判定
	CollisionMesh();
}

//*****************
// 描画処理
//*****************
void CWheel::Draw(void)
{
	CModel ::Draw();
}

//*****************
// 位置の設定
//*****************
void CWheel::SetPosion(D3DXVECTOR3 pos)
{

}

//******************
// 位置の設定
//******************
void CWheel::SetPos(D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CWheel::SetRot(D3DXVECTOR3 rot)
{
	CModel::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CWheel::GetPos(void)
{
	return CModel::GetPos();
}

//******************
// 向き情報の取得
//******************
D3DXVECTOR3 CWheel::GetRot(void)
{
	return CModel::GetRot();
}

//************************
// メッシュとのあたり判定
//************************
void CWheel::CollisionMesh(void)
{
	D3DXMATRIX mtx = GetMtxWorld();

	if (m_pCarBody == nullptr)
	{
		return;
	}
	D3DXMATRIX carMtx = m_pCarBody->GetMtxWorld();
	// 逆行列作成
	D3DXMATRIX invCarMtx;

	D3DXMatrixInverse(&invCarMtx,nullptr,&carMtx);

	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// メッシュ情報取得
	CMesh* pMesh = CGame::GetCMesh();

	// 地面の高さ
	float meshHeight = pMesh->GetHeight(D3DXVECTOR3(mtx._41, mtx._42, mtx._43));

	// タイヤの高さ
	mtx._42 = meshHeight + fRadius;

	m_fSuspensionOld = m_fSuspension;
	// サスペンションの長さ
	m_fSuspension = m_fAttachY - mtx._42;

	float Spring = (fSusRest - m_fSuspension)* fSpringK;

	float Danper = -(m_fSuspension - m_fSuspensionOld)* fDanperC;

	m_fDeltaHeight = Spring + Danper;
	m_fDeltaHeight = m_fDeltaHeight*0.04f;

	//if (m_fSuspension > fSusMax)
	//{// 最大の長さを超えたら
	//	m_fDeltaHeight = m_fSuspension - fSusMax;
	//}
	//else if (m_fSuspension < fSusMin)
	//{// 最小の長さを超えたら
	//	m_fDeltaHeight = m_fSuspension - fSusMin;
	//}
	//else
	//{
	//	m_fDeltaHeight = 0.0f;
	//}

	pos.y = meshHeight - fRadius;

	D3DXVECTOR3 wldPos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
	D3DXVECTOR3 lclPos;

	D3DXVec3TransformCoord(&lclPos, &wldPos, &invCarMtx);

	// 位置を反映
	SetPos(D3DXVECTOR3(pos.x,lclPos.y,pos.z));
}