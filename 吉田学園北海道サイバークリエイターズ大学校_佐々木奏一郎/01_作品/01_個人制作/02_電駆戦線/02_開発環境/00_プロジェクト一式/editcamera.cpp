//**********************************
//
// �ҏW���̃J�������� [editcamera.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "editcamera.h"
#include "manager.h"
#include "camera.h"
#include "input.h"


//*****************
// �R���X�g���N�^
//*****************
CEditCamera::CEditCamera()
{
	m_state = STATE_NONE;
}

//*****************
// �f�X�g���N�^
//*****************
CEditCamera::~CEditCamera()
{

}

//*****************
// ����������
//*****************
HRESULT CEditCamera::Init(void)
{

	return S_OK;
}

//*****************
// �I������
//*****************
void CEditCamera::Uninit(void)
{
}

//*****************
// �X�V����
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