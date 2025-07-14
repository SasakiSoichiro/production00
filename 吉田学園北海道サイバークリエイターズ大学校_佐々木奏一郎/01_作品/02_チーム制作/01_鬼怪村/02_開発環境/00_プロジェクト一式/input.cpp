//=============================================================================
//
//	���͏��� [input.cpp]
// Author : HRT ryuusei
//
//=============================================================================

// �C���N���[�h�t�@�C��
#include "input.h"
#include "player.h"

// �}�N����`
#define NUM_KEY_MAX (256)				//	�L�[�̍ő吔
#define NUM_MAUSE_MAX (3)				//	�}�E�X�̍ő吔
#define MAX_PAD (2)						//	�R���g���[���[

// �O���[�o���ϐ��錾
XINPUT_STATE g_joyKeyState[PLAYER_MAX] = {};	        //�W���C�p�b�h�̃v���X���
XINPUT_STATE g_OldKeyState[PLAYER_MAX] = {};
XINPUT_STATE g_joyKeyStateTrigger[PLAYER_MAX] = {};		//�W���C�p�b�h�̃g���K�[���
XINPUT_STATE g_joyKeyStateRelease[PLAYER_MAX] = {};		//�W���C�p�b�h�̃����[�X���

LPDIRECTINPUT8 g_pInput = NULL;				            //DeirectInput�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	            //���̓f�o�C�X�ւ̃|�C���^
LPDIRECTINPUT8 g_pInputMause = NULL;				    //DeirectInput�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevMause = NULL;	            //���̓f�o�C�X�ւ̃|�C���^

BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldState[NUM_KEY_MAX];
BYTE g_aMauseState[NUM_MAUSE_MAX];
BYTE g_aOldMauseState[NUM_MAUSE_MAX];

DIMOUSESTATE g_CurrentMouseState;		                //!< �}�E�X�̌��݂̓��͏��
DIMOUSESTATE g_PrevMouseState;			                //!< �}�E�X�̈�t���[���O�̓��͏��
DIMOUSESTATE g_Oldpos;		                            //!< �}�E�X�̌��݂̓��͏��

//================================================
// �L�[�{�[�h�̏���������
//================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//	Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//	���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//	�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//	�������[�h
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//	�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//================================================
// �L�[�{�[�h�̏I������
//================================================
void UninitKeyboard(void)
{
	// ���̓f�o�C�X�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//================================================
// �L�[�{�[�h�̍X�V����
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  // �L�[�{�[�h�̓��͏��
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey]; // �L�[�{�[�h�v���X����ۑ�
	}

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; // �L�[�{�[�h�v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//================================================
// �L�[�{�[�h�̃v���X����
//================================================
bool GetKeyboardPress(int nKey)
{// ������Ă�L�[
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//================================================
// �L�[�{�[�h�̃g���K�[����
//================================================
bool KeybordTrigger(int nKey)
{// �������
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// �L�[�{�[�h�̃����[�X����
//================================================
bool KeybordRelease(int nKey)
{// ������
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// �L�[�{�[�h�̃��s�[�g����
//================================================
bool KeybordRepeat(int nKey)
{// ������Ă��
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// �W���C�p�b�h�̏���������
//================================================
HRESULT InitJoypad(void)
{
	for (int count = 0; count < PLAYER_MAX; count++)
	{
		// �������̃N���A
		memset(&g_joyKeyState[count], 0, sizeof(XINPUT_STATE));
	}
	
	// Xinput�̃X�e�[�g�̐ݒ�(�L���ɂ���
	XInputEnable(true);

	return S_OK;
}
//================================================
// �W���C�p�b�h�̏I������
//================================================
void UninitJoypad(void)
{
	//	Xinput�̃X�e�[�g�̐ݒ�(�����ɂ���
	XInputEnable(false);
}
//================================================
// �W���C�p�b�h�̍X�V����
//================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState[MAX_PAD]; // ���͏��

	for (int p = 0; p < PLAYER_MAX; p++)
	{
		g_OldKeyState[p] = g_joyKeyState[p]; // �L�[�{�[�h�v���X����ۑ�

		// �W���C�p�b�h�̏�Ԃ��擾
		if (XInputGetState(0, &joyKeyState[p]) == ERROR_SUCCESS)
		{
			WORD Button = joyKeyState[p].Gamepad.wButtons;
			WORD OldButton = g_joyKeyState[p].Gamepad.wButtons;

			g_joyKeyStateTrigger[p].Gamepad.wButtons = Button & ~OldButton;

			g_joyKeyStateRelease[p].Gamepad.wButtons = Button & ~OldButton;

			g_joyKeyState[p] = joyKeyState[p]; // �W���C�p�b�h�̃v���X����ۑ�
		}
	}
}
//================================
// �W���C�p�b�h�v���X�����擾
//================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//================================
// �W���C�p�b�h�g���K�[�����擾
//================================
bool JoyPadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//================================
// �W���C�p�b�h�����[�X�����擾
//================================
bool JoyPadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//================================
//�R���g���[���[�̐U������
//================================
void VibrateController(int ContorollerID, WORD leftMoter, WORD rightMoter)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = leftMoter;
	vibration.wRightMotorSpeed = rightMoter;

	//�U���J�n
	XInputSetState(ContorollerID, &vibration);
}
//====================================
// �Q�[�����ł̐U���������Ǘ�����֐�
//====================================
void UpdateVibration(VibrationState* vibrationState)
{
	DWORD currentTime = GetTickCount();
	Player* pPlayer = GetPlayer();

	if (pPlayer->nLife > 0)
	{
		if (currentTime - vibrationState->startTime < vibrationState->duration)
		{
			//�U����
			VibrateController(vibrationState->contorollerID, vibrationState->leftMoter, vibrationState->rightMoter);
		}
		else
		{
			//�U���I��
			VibrateController(vibrationState->contorollerID, 0, 0);
		}
	}
	else
	{
		//�U���I��
		VibrateController(vibrationState->contorollerID, 0, 0);
	}
}
//=================================
//�U�����I�������鏈��
//=================================
void StartVibration(VibrationState* vibrationState, int VibrationTime,int leftMoter,int rightMoter)
{
	vibrationState->contorollerID = 0;			//�R���g���[���[ID
	vibrationState->leftMoter = leftMoter;		//�ő�60000
	vibrationState->rightMoter = rightMoter;	//�ő�60000
	vibrationState->startTime = GetTickCount();	//�J�n����
	vibrationState->duration = VibrationTime;	//200�_�b
}

//================================
// �W���C�p�b�h�����擾
//================================
XINPUT_STATE* GetState(void)
{
	return &g_joyKeyStateTrigger[0];
}
//================================
// �W���C�p�b�h�̓��͏��擾
//================================
int GetJoypadInputState(int InputType)
{
	return S_OK;
}
//=================================
// �W���C�p�b�h�̃X�e�B�b�N����
//=================================
bool GetJoyStick(int player)
{
	bool joykey[PLAYER_MAX] = { false };
	int b = 0;

	// ���X�e�B�b�N
	if (g_joyKeyState[player].Gamepad.sThumbLX > 100 ||
		g_joyKeyState[player].Gamepad.sThumbLX < -100 ||
		g_joyKeyState[player].Gamepad.sThumbLY > 100 ||
		g_joyKeyState[player].Gamepad.sThumbLY < -100)
	{
		joykey[player] = true;
	}

	// �E�X�e�B�b�N
	if (g_joyKeyState[player].Gamepad.sThumbRX > 100 ||
		g_joyKeyState[player].Gamepad.sThumbRX < -100 ||
		g_joyKeyState[player].Gamepad.sThumbRY > 100 ||
		g_joyKeyState[player].Gamepad.sThumbRY < -100)
	{
		joykey[player] = true;
	}

	return joykey[player];
}
//=====================================
// �W���C�p�b�h�̃X�e�B�b�N�̏��擾
//=====================================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState[0];
}
//=====================================
// �}�E�X�̏���������
//=====================================
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd)
{
	// Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputMause, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMause, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevMause->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h
	if (FAILED(g_pDevMause->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevMause->Acquire();

	return S_OK;
}
//=====================================
// �}�E�X�̏I������
//=====================================
void UninitMausu(void)
{
	// ���̓f�o�C�X�̔j��
	if (g_pDevMause != NULL)
	{
		g_pDevMause->Unacquire(); // �L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevMause->Release();
		g_pDevMause = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInputMause != NULL)
	{
		g_pInputMause->Release();
		g_pInputMause = NULL;
	}
}
//=====================================
// �}�E�X�̍X�V����
//=====================================
void UpdateMausu(void)
{
	g_Oldpos = g_CurrentMouseState;

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	g_PrevMouseState = g_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);

	if (FAILED(hr1))
	{
		g_pDevMause->Acquire();
		hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}

	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	g_CurrentMouseState.lX = p.x;
	g_CurrentMouseState.lY = p.y;
}
//=====================================
// �}�E�X�������ꂽ����
//=====================================
bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & (0x80)) &&
		g_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
//=====================================
// �}�E�X�������ꂽ����
//=====================================
bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(g_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}

D3DXVECTOR2 GetMouseVelocity()
{
	return D3DXVECTOR2((float)g_CurrentMouseState.lX, (float)g_CurrentMouseState.lY);
}

D3DXVECTOR2 GetMouseVelocityOld()
{
	return D3DXVECTOR2((float)g_Oldpos.lX, (float)g_Oldpos.lY);
}