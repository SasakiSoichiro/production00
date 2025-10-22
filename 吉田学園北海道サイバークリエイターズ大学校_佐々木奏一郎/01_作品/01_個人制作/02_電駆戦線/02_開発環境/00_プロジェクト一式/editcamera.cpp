//**********************************
//
// 編集中のカメラ処理 [editcamera.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "editcamera.h"
#include "manager.h"
#include "camera.h"
#include "input.h"


//*****************
// コンストラクタ
//*****************
CEditCamera::CEditCamera()
{
	m_state = STATE_NONE;
}

//*****************
// デストラクタ
//*****************
CEditCamera::~CEditCamera()
{

}

//*****************
// 初期化処理
//*****************
HRESULT CEditCamera::Init(void)
{

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CEditCamera::Uninit(void)
{
}

//*****************
// 更新処理
//*****************
void CEditCamera::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	CInputMouse* pInputMouse = CManager::GetCInputMouse();
	switch (m_state)
	{
	case STATE_NONE:
		if (pInputMouse->GetDown(CInputMouse::MOUSE_R) == true)
		{
			m_state = STATE_R;
		}
		else if (pInputMouse->GetDown(CInputMouse::MOUSE_L) == true)
		{
			m_state = STATE_V;
		}
		break;
	case STATE_R:
		pCamera->MoveMouseR();
		if (pInputMouse->GetUp(CInputMouse::MOUSE_R) == true)
		{
			m_state = STATE_NONE;
		}
		break;
	case STATE_V:
		pCamera->MoveMouseV();
		if (pInputMouse->GetUp(CInputMouse::MOUSE_L) == true)
		{
			m_state = STATE_NONE;
		}
		break;
	}
	pCamera->SetVandR();
}