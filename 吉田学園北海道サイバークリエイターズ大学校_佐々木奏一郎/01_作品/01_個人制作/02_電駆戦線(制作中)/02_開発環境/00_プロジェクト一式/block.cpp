//*****************************************
//
// ブロック処理 [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "block.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"

//**********************
// 静的メンバ変数初期化
//**********************
int CBlock::m_nNumAll = 0;

//*****************
// コンストラクタ
//*****************
CBlock::CBlock(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_nIdx = m_nNumAll; 
	m_State=STATE_NONE;
}

//*****************
// デストラクタ
//*****************
CBlock::~CBlock()
{
}

//******************
// インスタンス生成
//*******************
CBlock* CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock* pBlock;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CBlock;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CBlock::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\box002.x");
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
void CBlock::Uninit(void)
{
	// 終了処理
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CBlock::Update(void)
{
	// CInputMouseのポインタに情報を入れる
	CInputMouse* pInputMouse = CManager::GetCInputMouse();
	// CInputKeyboardのポインタに情報を入れる
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	
	bool bCursor = CollisionCursor();// カーソルが当たっているか
	switch (m_State)
	{
	case STATE_NONE:
		// 何もない状態
		if (bCursor==true&&pInputMouse->GetDown(CInputMouse::MOUSE_L)==true)
		{// 当たってるかつマウスがおされたとき
			CDebugProc::Print("\nカーソル当たってる%d", m_nIdx);

			m_State = STATE_DRAG;// つかんでる状態にする
		}
		break;
	case STATE_DRAG:
		// つかんでる状態

		// ブロックを動かす
		Drag();
		// 現在の位置取得
		D3DXVECTOR3 pos = GetPos();
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// 高さをあげる
			pos.y += 0.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// 高さを下げる
			pos.y -= 0.5f;
		}

		// 位置を設定
		SetPos(pos);
		if (pInputMouse->GetUp(CInputMouse::MOUSE_L) == true)
		{// マウスを離したら
			m_State = STATE_NONE;// 何もない状態にする
		}
		break;
	}
}

//*****************
// 描画処理
//*****************
void CBlock::Draw(void)
{
	CObjectX::Draw();// 描画
}

//******************
// 位置の設定
//******************
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CBlock::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CBlock::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CBlock::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}

bool CBlock::CollisionCursor(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	D3DXMATRIX matProj, matView,matWorld;
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 blockPos;
	D3DXVECTOR2 blockPos2D;
	D3DXVECTOR2 CursorPos = pInputMouse->GetVelocity();
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 pos = GetPos();
	D3DXVec3Project(&blockPos, &pos, &viewport, &matProj, &matView, &matWorld);
	float VecX, VecY;
	VecX = blockPos.x - CursorPos.x;
	VecY = blockPos.y - CursorPos.y;
	float fDistance = sqrtf((VecX*VecX) + (VecY - VecY));

	float fRad = 20.0f;

	if (fRad > fDistance)
	{
		return true;
	}

	return false;

}

void CBlock::Drag(void)
{
	CInputMouse* pInputMouse = CManager::GetCInputMouse();
	D3DXVECTOR2 CursorPos = pInputMouse->GetVelocity();
	D3DXVECTOR2 CursorPosOld = pInputMouse->GetVelocityOld();
	CPlayer* pPlayer = CManager::GetCPlayer();

	D3DXVECTOR3 rot = pPlayer->GetRot();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 Vec = CursorPos - CursorPosOld;
	Vec *= 0.3f;
	D3DXVECTOR3 move=D3DXVECTOR3(0.0f,0.0f,0.0f);
	move.x = cosf(rot.y) * Vec.x + sinf(rot.y) * Vec.y;
	move.z = -sinf(rot.y) * Vec.x - cosf(rot.y) * Vec.y;
	pos += move;

	SetPos(pos);
}