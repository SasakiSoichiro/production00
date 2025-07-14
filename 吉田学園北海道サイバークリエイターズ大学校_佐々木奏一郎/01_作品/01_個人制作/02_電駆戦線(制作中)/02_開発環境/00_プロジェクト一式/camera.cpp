//**********************************
//
// カメラ処理 [camera.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "camera.h"
#include "input.h"
#include "manager.h"

//****************
// マクロ定義
//****************
#define OFFSET (80.0f)	// プレイヤーからカメラの距離
#define DEST (0.09f)	// 目標に到達するまでの倍率

//**********************
// 静的メンバ変数初期化
//**********************
CPlayer* CCamera::m_pPlayer = NULL;			// プレイヤーのポインタ


//********************
// コンストラクタ
//********************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 注視点
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_mtxProjection = {};					// プロジェクションマトリックス
	m_mtxView = {};							// ビューマトリックス
	m_fDistance = 0.0f;						// 視点と注視点の距離
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の視点
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の注視点
}

//********************
// デストラクタ
//********************
CCamera::~CCamera()
{
	// 処理なし
}

//**************
// 初期化処理
//**************
void CCamera::Init(void)
{
	// カメラの初期配置
	m_posV = D3DXVECTOR3(0.0f, OFFSET, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離計算
	float fDX = m_posV.x - m_posR.x;
	float fDY = m_posV.y - m_posR.y;
	float fDZ = m_posV.z - m_posR.z;
	m_fDistance = sqrtf((fDX * fDX) + (fDY * fDY) + (fDZ * fDZ));// ユークリッド距離

}

//**************
// 終了処理
//**************
void CCamera::Uninit(void)
{
	// 処理なし
}

//**************
// 更新処理
//**************
void CCamera::Update(void)
{
	// プレイヤー追従
	Target();

	// 注視点のスムージング追従計算(DESTで遅延調整)
	m_posR.x += (m_posRDest.x - m_posR.x) * DEST;
	m_posR.y += (m_posRDest.y - m_posR.y) * DEST;
	m_posR.z += (m_posRDest.z - m_posR.z) * DEST;

	// 視点のスムージング追従計算(DESTで遅延調整)
	m_posV.x += (m_posVDest.x - m_posV.x) * DEST;
	m_posV.y += (m_posVDest.y - m_posV.y) * DEST;
	m_posV.z += (m_posVDest.z - m_posV.z) * DEST;

}

//**************
// 設定処理
//**************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(	&m_mtxView,
						&m_posV,	// 視点
						&m_posR,	// 注視点
						&m_vecU);	// 上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(100.0f),						// 視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// アスペクト比
		10.0f,										// ニア(どこまで近くを映すか)
		1000.0f);									// ファー(どこまで遠くを映すか)

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//****************
// プレイヤー追従
//****************
void CCamera::Target(void)
{
	if (m_pPlayer != NULL)
	{// プレイヤーがいたら

		// プレイヤー情報取得
		D3DXVECTOR3 Ppos = m_pPlayer->GetPos();
		D3DXVECTOR3 Prot = m_pPlayer->GetRot();

		// 注視点をプレイヤーの位置に設定
		m_posRDest.x = Ppos.x;
		m_posRDest.y = Ppos.y+20.0f;
		m_posRDest.z = Ppos.z;

		// 視点をプレイヤーの後ろ側に設定(初期設定の距離に離れる)
		m_posVDest.x = Ppos.x + sinf(Prot.y) * m_fDistance;
		m_posVDest.y = Ppos.y + OFFSET;
		m_posVDest.z = Ppos.z + cosf(Prot.y) * m_fDistance;
	}
}

//****************
// 固定カメラ
//****************
void CCamera::Fixed(D3DXVECTOR3 pos)
{

}

void CCamera::SetPlayer(CPlayer* pPlayer)
{
	if (m_pPlayer == NULL)
	{
		m_pPlayer = pPlayer;
	}
}