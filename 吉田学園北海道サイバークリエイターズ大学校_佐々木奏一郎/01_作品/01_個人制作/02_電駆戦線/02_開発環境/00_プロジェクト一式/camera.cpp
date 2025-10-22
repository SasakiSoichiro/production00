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
#include "renderer.h"

//********************
// コンストラクタ
//********************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_mtxProjection = {};					
	m_mtxView = {};							
	m_fDistance = 0.0f;						
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_nShakeTime = 0;
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
	m_posV = D3DXVECTOR3(0.0f, ofsetV, 0.0f);
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
	// 注視点のスムージング追従計算(DESTで遅延調整)
	m_posR.x += (m_posRDest.x - m_posR.x) * dest;
	m_posR.y += (m_posRDest.y - m_posR.y) * dest;
	m_posR.z += (m_posRDest.z - m_posR.z) * dest;

	// 視点のスムージング追従計算(DESTで遅延調整)
	m_posV.x += (m_posVDest.x - m_posV.x) * dest;
	m_posV.y += (m_posVDest.y - m_posV.y) * dest;
	m_posV.z += (m_posVDest.z - m_posV.z) * dest;

	// カメラを揺らす
	Shake();
	// タイマーを減らす
	m_nShakeTime--;
}

//**************
// 描画処理
//**************
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	// 視点
		&m_posR,	// 注視点
		&m_vecU);	// 上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(FOV),							// 視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// アスペクト比
		nearScreen,									// ニア(どこまで近くを映すか)
		farScreen);									// ファー(どこまで遠くを映すか)

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//****************
// プレイヤー追従
//****************
void CCamera::Target(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// プレイヤー情報取得
	D3DXVECTOR3 Ppos = pos;
	D3DXVECTOR3 Prot = rot;

	// 注視点をプレイヤーの位置に設定
	m_posRDest.x = Ppos.x;
	m_posRDest.y = Ppos.y + ofsetR;
	m_posRDest.z = Ppos.z;

	// 視点をプレイヤーの後ろ側に設定(初期設定の距離に離れる)
	m_posVDest.x = Ppos.x + sinf(Prot.y) * m_fDistance;
	m_posVDest.y = Ppos.y + ofsetV;
	m_posVDest.z = Ppos.z + cosf(Prot.y) * m_fDistance;
}

//************************
// 後ろ向きプレイヤー追従
//************************
void CCamera::BackTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 注視点をプレイヤーの位置に設定
	m_posRDest.x = pos.x + sinf(rot.y) * ofsetR;
	m_posRDest.y = pos.y + ofsetR;
	m_posRDest.z = pos.z + cosf(rot.y) * ofsetR;

	// 視点をプレイヤーの後ろ側に設定(初期設定の距離に離れる)
	m_posVDest.x = pos.x + sinf(rot.y) * m_fDistance;
	m_posVDest.y = pos.y + ofsetBackV;
	m_posVDest.z = pos.z + cosf(rot.y) * m_fDistance;

}

//**********************
// カメラの位置の初期化
//**********************
void CCamera::InitTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 注視点をプレイヤーの位置に設定
	m_posR.x = pos.x;
	m_posR.y = pos.y + ofsetR;
	m_posR.z = pos.z;

	// 視点をプレイヤーの後ろ側に設定(初期設定の距離に離れる)
	m_posV.x = pos.x + sinf(rot.y) * m_fDistance;
	m_posV.y = pos.y + ofsetV;
	m_posV.z = pos.z + cosf(rot.y) * m_fDistance;

	// 遅延をなくす
	m_posVDest = m_posV;
	m_posRDest = m_posR;
}

//****************
// ジャンプの追従
//****************
void CCamera::JumpTarget(D3DXVECTOR3 pos, float fAngle)
{
	// プレイヤー情報取得
	D3DXVECTOR3 Ppos = pos;

	// 注視点をプレイヤーの位置に設定
	m_posRDest.x = Ppos.x;
	m_posRDest.y = Ppos.y;
	m_posRDest.z = Ppos.z;

	// 視点をプレイヤーの後ろ側に設定(初期設定の距離に離れる)
	m_posVDest.x = Ppos.x + sinf(fAngle);
	m_posVDest.y = Ppos.y + ofsetBackV;
	m_posVDest.z = Ppos.z + cosf(fAngle);
}

//********************
// 視点と注視点の設定
//********************
void CCamera::SetVandR(void)
{
	// 入力取得
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();

	// カメラを動かす(視点と注視点同時)
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{// 前
		m_posR.x += sinf(m_rot.y + D3DX_PI) * speed;
		m_posR.z += cosf(m_rot.y + D3DX_PI) * speed;
		m_posV.x += sinf(m_rot.y + D3DX_PI) * speed;
		m_posV.z += cosf(m_rot.y + D3DX_PI) * speed;
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{// 後
		m_posR.x += sinf(m_rot.y) * speed;
		m_posR.z += cosf(m_rot.y) * speed;
		m_posV.x += sinf(m_rot.y) * speed;
		m_posV.z += cosf(m_rot.y) * speed;
	}
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{// 左
		m_posR.x += sinf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posR.z += cosf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posV.x += sinf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posV.z += cosf(m_rot.y + D3DX_PI * 0.5f) * speed;
	}
	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{// 右
		m_posR.x += sinf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posR.z += cosf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * speed;
	}

	// 遅延をなくす
	m_posRDest = m_posR;	
	m_posVDest = m_posV;	
}

//************************
// マウスで注視点を動かす
//************************
void CCamera::MoveMouseR(void)
{
	// マウス情報取得
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	// カーソル位置取得
	D3DXVECTOR2 cursorPos, cursorPosOld;
	cursorPos = pInputMouse->GetVelocity();
	cursorPosOld = pInputMouse->GetVelocityOld();

	// マウスが動いている方向を求める
	float DeltaX = (float)(cursorPos.x - cursorPosOld.x);
	float DeltaY = (float)(cursorPos.y - cursorPosOld.y);

	// マウス感度計算
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	// 向き計算
	m_rot.x += DeltaY;
	m_rot.y += DeltaX;

	// 注視点を動かす
	m_posR.x = m_posV.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posR.y = m_posV.y - sinf(m_rot.x) * m_fDistance;
	m_posR.z = m_posV.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	// 遅延をなくす
	m_posRDest = m_posR;
}

void CCamera::MoveMouseV(void)
{
	// マウス情報取得
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	// カーソル位置取得
	D3DXVECTOR2 cursorPos, cursorPosOld;
	cursorPos = pInputMouse->GetVelocity();
	cursorPosOld = pInputMouse->GetVelocityOld();

	// マウスが動いている方向を求める
	float DeltaX = (float)(cursorPos.x - cursorPosOld.x);
	float DeltaY = (float)(cursorPos.y - cursorPosOld.y);

	// マウス感度計算
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	// 向き計算
	m_rot.x += DeltaY;
	m_rot.y += DeltaX;

	// 注視点を動かす
	m_posV.x = m_posR.x + sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	// 遅延をなくす
	m_posVDest = m_posV;
}

//***************
// 振動
//***************
void CCamera::Shake(void)
{
	float fShakeX, fShakeY;

	// 揺れを計算
	fShakeX = sinf((float)m_nShakeTime) * shakeDistance;
	fShakeY = cosf((float)m_nShakeTime) * shakeDistance;

	// 視点と注視点を揺らす
	if (m_nShakeTime > 0)
	{
		m_posR.x += fShakeX;
		m_posR.y += fShakeY;
		m_posV.x += fShakeX;
		m_posV.y += fShakeY;
	}
}

//******************
// 揺らす時間を設定
//******************
void CCamera::SetShake(int nTime)
{
	if (m_nShakeTime <= 0)
	{// 時間が0以下だったら設定
		m_nShakeTime = nTime;
	}
}