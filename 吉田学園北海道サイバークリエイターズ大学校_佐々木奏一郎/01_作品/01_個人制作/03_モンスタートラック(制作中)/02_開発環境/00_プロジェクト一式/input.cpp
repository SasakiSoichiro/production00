//**********************************
//
// ���͏��� [input.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "input.h"

//****************
// �ÓI�����o�ϐ�
//****************
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//****************
// �R���X�g���N�^
//****************
CInput::CInput()
{
	m_pDevice = NULL;
}

//****************
// �f�X�g���N�^
//****************
CInput::~CInput()
{
}

//****************
// ����������
//****************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�̃I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
		return S_OK;
	}
	return E_FAIL;
}

//****************
// �I������
//****************
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//================
// �R���X�g���N�^
//================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < 256;nCnt++)
	{
		m_aKeyState[nCnt]=NULL;				// �L�[�{�[�h�̑O��̃v���X���
		m_aOldState[nCnt]=NULL;				// �L�[�{�[�h�̃v���X���
	}
}

//=================
// �f�X�g���N�^
//=================
CInputKeyboard::~CInputKeyboard()
{

}

//=============
// ����������
//=============
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//****************
// �I������
//****************
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//****************
// �X�V����
//****************
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[256];//�L�[�{�[�h�̓��͏��

	for (int nCntkey = 0; nCntkey < 256; nCntkey++)
	{
		m_aOldState[nCntkey] = m_aKeyState[nCntkey];
	}
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntkey = 0; nCntkey < 256; nCntkey++)
		{
			m_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//****************
// �����Ă���Ƃ�
//****************
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//********************************
// ������Ă���Ƃ����̂ݔ���
//********************************
bool CInputKeyboard::Trigger(int nKey)
{
	bool Trigger = false;
	if (m_aKeyState[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//**********************
// �͂Ȃ��ꂽ�Ƃ�����
//**********************
bool CInputKeyboard::Release(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

bool CInputKeyboard::Repeat(int nKey)
{
	bool Trigger = false;
	if (m_aOldState[nKey] & 0x80 && !(m_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//****************
// �R���X�g���N�^
//****************
CInputMouse::CInputMouse()
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_aState[nCnt] = NULL;		// �}�E�X�̑O��̃v���X���
		m_aOldState[nCnt] = NULL;	// �}�E�X�̃v���X���
	}
	m_CurrentState = {};	// �}�E�X�̌��݂̓��͏��
	m_PrevState = {};		// �}�E�X��1�t���[���O�̓��͏��
	m_Oldpos = {};		    // �}�E�X�̌��݂̓��͏��
}

//****************
// �f�X�g���N�^
//****************
CInputMouse::~CInputMouse()
{
}

//****************
// ����������
//****************
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//****************
// �I������
//****************
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}
//****************
// �X�V����
//****************
void CInputMouse::Update(void)
{
	m_Oldpos = m_CurrentState;

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	m_PrevState = m_CurrentState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hr1 = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentState);

	if (FAILED(hr1))
	{
		m_pDevice->Acquire();
		hr1 = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentState);
	}

	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	m_CurrentState.lX = p.x;
	m_CurrentState.lY = p.y;
}
//******************
// �����ꂽ����
//******************
bool CInputMouse::GetDown(MOUSE button_type)
{
	if (!(m_PrevState.rgbButtons[button_type] & (0x80)) &&
		m_CurrentState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
//****************
// �����ꂽ����
//****************
bool CInputMouse::GetUp(MOUSE button_type)
{
	if (m_PrevState.rgbButtons[button_type] & 0x80 &&
		!(m_CurrentState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}

D3DXVECTOR2 CInputMouse::GetVelocity()
{
	return D3DXVECTOR2((float)m_CurrentState.lX, (float)m_CurrentState.lY);
}
D3DXVECTOR2 CInputMouse::GetVelocityOld()
{
	return D3DXVECTOR2((float)m_Oldpos.lX, (float)m_Oldpos.lY);
}

//****************
// �R���X�g���N�^
//****************
CInputJoypad::CInputJoypad()
{
	// �������̃N���A
	memset(&m_State, 0, sizeof(XINPUT_STATE));
	memset(&m_oldState, 0, sizeof(XINPUT_STATE));
	memset(&m_StateTrigger, 0, sizeof(XINPUT_STATE));
}

//****************
// �f�X�g���N�^
//****************
CInputJoypad::~CInputJoypad()
{

}

//****************
// ����������
//****************
HRESULT  CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(true);
	return S_OK;
}

//****************
// �I������
//****************
void CInputJoypad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(false);

	CInput::Uninit();
}

//****************
// �X�V����
//****************
void CInputJoypad::Update(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̓��͏���
	m_oldState = m_State;
	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_State.Gamepad.wButtons;

		m_StateTrigger.Gamepad.wButtons = Button & ~OldButton;

		m_State = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}
}

//************************************
// �{�^����������Ă���Ƃ������Ɣ���
//************************************
bool CInputJoypad::GetPress(JOYKEY key)
{
	return(m_State.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************
// �{�^����������Ă���Ƃ�1��̂ݔ���
//************************************
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return (m_StateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}