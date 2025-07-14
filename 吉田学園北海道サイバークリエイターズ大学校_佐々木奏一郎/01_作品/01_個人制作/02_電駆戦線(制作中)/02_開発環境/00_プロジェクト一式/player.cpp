//*****************************************
//
// プレイヤー処理 [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"

//*******************
// マクロ定義
//*******************
#define SPEED (8.0f)	// プレイヤーの移動速度
#define DEST (0.3f)

//*****************
// 静的メンバ変数
//*****************
int CPlayer::m_nLife = NULL;

//*****************
// コンストラクタ
//*****************
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_nLife = 0;
	m_State = STATE_NONE;
	m_pMotion = NULL;
}

//*****************
// デストラクタ
//*****************
CPlayer::~CPlayer()
{
}

//******************
// インスタンス生成
//*******************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer;// プレイヤーのポインタ
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();
	// 現在のオブジェクトの総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pPlayer = new CPlayer;		// インスタンス生成
		pPlayer->Init(pos);			// 初期化
		CCamera::SetPlayer(pPlayer);// カメラのターゲットに設定

		// 情報を渡す
		return pPlayer;				
	}

	// オブジェクトが最大数に達していた場合
	// NULLを返す
	return NULL;	
}

//*****************
// 初期化処理
//*****************
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;// 位置初期設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 向き初期設定
	// モデルの生成(パーツ分)
	if (m_pMotion == NULL)
	{// NULLだったら
		// インスタンス生成
		m_pMotion = CMotion::Create("data\\MOTION\\segway.txt");
	}
	m_nLife = 3;// ライフ初期設定

	// 初期化成功
	return S_OK;		
}

//*****************
// 終了処理
//*****************
void CPlayer::Uninit(void)
{
	m_pMotion->Uninit();
	delete m_pMotion;
	m_pMotion = NULL;
	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = m_pos;// 現在の位置を代入
	m_oldPos = m_pos;
	CDebugProc::Print("\nプレイヤーの位置 X:%f Y:%f Z:%f\n",pos.x,pos.y,pos.z);
	// キーボードの取得
	CInputKeyboard* pInputKeyboard;
	CInputJoypad* pInputJoypad;
	pInputKeyboard = CManager::GetCInputKeyboard();
	pInputJoypad = CManager::GetCInputJoypad();
	float RightSpeed=0.0f, LeftSpeed=0.0f;
	bool bLeftback = pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true;	// 左:後
	bool bRightback = pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_A) == true;	// 右:後
	bool bLeftflont = pInputKeyboard->GetPress(DIK_Q) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_UP) == true;	// 左:前
	bool bRightflont = pInputKeyboard->GetPress(DIK_E) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == true;	// 右:前
	switch (m_State)
	{
	case CPlayer::STATE_NONE:

		if (bLeftback == true)
		{// 左側が後ろ方向に進むとき
			if (bRightback == true)
			{// 右側が後ろ方向のとき
				RightSpeed = SPEED;
				m_pMotion->SetMotion(MOTION_BACK);
			}
			else if (bRightflont == true)
			{// 右側が前方向のとき
				RightSpeed = -SPEED;
				m_pMotion->SetMotion(MOTION_BF);
			}
			else
			{
				m_pMotion->SetMotion(MOTION_LB);
			}
			LeftSpeed = SPEED;
		}
		else if (bLeftflont == true)
		{// 左側が前方向に進むとき
			if (bRightback == true)
			{// 右側が後ろ方向のとき
				RightSpeed = SPEED;
				m_pMotion->SetMotion(MOTION_FB);

			}
			else if (bRightflont == true)
			{// 右側が前方向のとき
				RightSpeed = -SPEED;
				m_pMotion->SetMotion(MOTION_FLONT);
			}
			else
			{
				m_pMotion->SetMotion(MOTION_LF);
			}
			LeftSpeed = -SPEED;
		}
		else if (bRightback == true)
		{// 右側が後ろ方向のとき
			RightSpeed = SPEED;
			m_pMotion->SetMotion(MOTION_RB);
		}
		else if (bRightflont == true)
		{// 右側が前方向のとき
			RightSpeed = -SPEED;
			m_pMotion->SetMotion(MOTION_RF);
		}
		else
		{
			m_pMotion->SetMotion(MOTION_NUETORAL);
		}
		if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputJoypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{// Dまたは右ボタン
			pos.y += SPEED;
		}
		if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == true)
		{// Dまたは右ボタン
			pos.y += -SPEED;
		}

		float speed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // 回転成分（角速度）
		m_move.x = sinf(m_fAngle) * speed;
		m_move.z = cosf(m_fAngle) * speed;
		m_fAngle += omega;
		// 徐々に止まる
		m_move.x += (0.0f - m_move.x) * 0.5f;
		m_move.z += (0.0f - m_move.z) * 0.5f;

		pos += m_move;	// 現在の位置にmove値を足す

		CMesh* pMesh = CManager::GetCMesh();
		if (pInputKeyboard->GetPress(DIK_N) == true)
		{
			pMesh->MoveY(pos);
		}

		if (pInputKeyboard->Trigger(DIK_K) == true)
		{
			std::vector<int> p = { 19 };
			pMesh->Save(p, "data\\JSON\\j.json");
		}

		pos.y = pMesh->GetHeight(pos);
	}
	SetPos(pos);	// 位置を設定
	SetRot(D3DXVECTOR3(0.0f, m_fAngle, 0.0f));
	m_pMotion->Update();
}

//*****************
// 描画処理
//*****************
void CPlayer::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);
	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fAngle, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	Posture();

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pMotion->Draw();
}

//******************
// 位置の設定
//*******************
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// 向きの設定
//*******************
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//***************
// 体勢の設定
//***************
void CPlayer::Posture(void)
{
	CMesh* pMesh = CManager::GetCMesh();

	// プレイヤーの上ベクトル
	D3DXVECTOR3 vecU = pMesh->GetNormal(m_pos);

	m_vecU += (vecU - m_vecU) * DEST;

	D3DXVECTOR3 vecF =-( m_pos - m_oldPos);

	D3DXVec3Normalize(&vecF, &vecF);

	if (D3DXVec3LengthSq(&vecF) > 0.001f)
	{
		m_vecF = vecF;
	}

	D3DXVECTOR3 baseForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotMtx;
	D3DXMatrixRotationAxis(&rotMtx, &vecU, m_fAngle);

	D3DXVec3TransformNormal(&m_vecF, &baseForward, &rotMtx);


	D3DXVECTOR3 vecR,vecFa;
	D3DXVec3Cross(&vecR, &vecU, &m_vecF);
	D3DXVec3Normalize(&vecR, &vecR);
	m_vecR += (vecR-m_vecR) * DEST;
	D3DXVec3Cross(&m_vecF, &vecR, &vecU);
	D3DXVec3Normalize(&vecFa, &m_vecF);
	m_vecF += (vecFa- m_vecF) * DEST;
	D3DXMatrixIdentity(&m_mtxWorld); 

	// ワールドマトリックスの更新
	m_mtxWorld._11 = m_vecR.x;
	m_mtxWorld._12 = m_vecR.y;
	m_mtxWorld._13 = m_vecR.z;
	m_mtxWorld._14 = 0;
	m_mtxWorld._21 = m_vecU.x;
	m_mtxWorld._22 = m_vecU.y;
	m_mtxWorld._23 = m_vecU.z;
	m_mtxWorld._24 = 0;
	m_mtxWorld._31 = m_vecF.x;
	m_mtxWorld._32 = m_vecF.y;
	m_mtxWorld._33 = m_vecF.z;
	m_mtxWorld._34 = 0;
	m_mtxWorld._41 = m_pos.x;
	m_mtxWorld._42 = m_pos.y;
	m_mtxWorld._43 = m_pos.z;
	m_mtxWorld._44 = 1;
}