//=============================================================================
//
//	�C���v�b�g���� [input.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput= NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̑O��̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];				//�L�[�{�[�h�̃v���X���
XINPUT_STATE g_oldjoykeyState;				//�W���C�p�b�h�̑O��̃v���X���
XINPUT_STATE g_joykeyState;					//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_joykeyStateTrigger;			//�g���K�[

//====================================================================================
//======================
//�L�[�{�[�h�̏���������
//======================
HRESULT  InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�̃I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
}

//=====================
//�L�[�{�[�h�̏I������
//=====================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=======================
// �L�[�{�[�h�̍X�V����
//=======================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��

	for (int nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
	{
		g_aOldState[nCntkey] = g_aKeyState[nCntkey];
	}
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//=======================
// �L�[�{�[�h��������
//=======================


//�L�[�{�[�h��������Ă���Ƃ������Ɣ���
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] &0x80) ? true : false;
}

//�L�[�{�[�h��������Ă���Ƃ����̂ݔ���
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger=true;
	}
	return Trigger;
}

//�L�[�{�[�h���͂Ȃ��ꂽ�Ƃ�����
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//============================================================================================
//=========================
//�W���C�p�b�h�̏���������
//=========================
HRESULT  InitJoypad(void)
{
	//�������̃N���A
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_oldjoykeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(true);
	return S_OK;
}

//========================
//�W���C�p�b�h�̏I������
//========================
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(false);
}

//=======================
//�W���C�p�b�h�̍X�V����
//=======================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̓��͏���
	g_oldjoykeyState = g_joykeyState;
	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joykeyState.Gamepad.wButtons;

		g_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		g_joykeyState = joykeyState;//�W���C�p�b�h�̃v���X����ۑ�
	}
}

//=======================
//�W���C�p�b�h�̉�������
//=======================


//�{�^����������Ă���Ƃ������Ɣ���
bool GetJoypadPress(JOYKEY key)
{
	return(g_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true: false;
}

//�{�^����������Ă���Ƃ�1��̂ݔ���
bool JoyPadTrigger(JOYKEY key)
{
	return (g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

XINPUT_STATE* GetJoypad(void)
{
	return &g_joykeyState;
}