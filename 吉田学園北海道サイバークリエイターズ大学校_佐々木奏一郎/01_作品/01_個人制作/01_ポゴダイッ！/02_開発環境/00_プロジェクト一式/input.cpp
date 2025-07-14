//=============================================================================
//
//	インプット処理 [input.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput= NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];				//キーボードの前回のプレス情報
BYTE g_aOldState[NUM_KEY_MAX];				//キーボードのプレス情報
XINPUT_STATE g_oldjoykeyState;				//ジョイパッドの前回のプレス情報
XINPUT_STATE g_joykeyState;					//ジョイパッドのプレス情報
XINPUT_STATE g_joykeyStateTrigger;			//トリガー

//====================================================================================
//======================
//キーボードの初期化処理
//======================
HRESULT  InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputのオブジェクトの生成
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
//キーボードの終了処理
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
// キーボードの更新処理
//=======================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報

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
// キーボード押下処理
//=======================


//キーボードが押されているときずっと反応
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] &0x80) ? true : false;
}

//キーボードが押されているとき一回のみ反応
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger=true;
	}
	return Trigger;
}

//キーボードがはなされたとき反応
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
//ジョイパッドの初期化処理
//=========================
HRESULT  InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_oldjoykeyState, 0, sizeof(XINPUT_STATE));
	memset(&g_joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInputのステートを設定
	XInputEnable(true);
	return S_OK;
}

//========================
//ジョイパッドの終了処理
//========================
void UninitJoypad(void)
{
	//XInputのステートを設定
	XInputEnable(false);
}

//=======================
//ジョイパッドの更新処理
//=======================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//ジョイパッドの入力処理
	g_oldjoykeyState = g_joykeyState;
	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joykeyState.Gamepad.wButtons;

		g_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		g_joykeyState = joykeyState;//ジョイパッドのプレス情報を保存
	}
}

//=======================
//ジョイパッドの押下処理
//=======================


//ボタンが押されているときずっと反応
bool GetJoypadPress(JOYKEY key)
{
	return(g_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true: false;
}

//ボタンが押されているとき1回のみ反応
bool JoyPadTrigger(JOYKEY key)
{
	return (g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

XINPUT_STATE* GetJoypad(void)
{
	return &g_joykeyState;
}