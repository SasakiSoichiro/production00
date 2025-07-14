//=============================================================================
//
//	入力処理 [input.cpp]
// Author : HRT ryuusei
//
//=============================================================================

// インクルードファイル
#include "input.h"
#include "player.h"

// マクロ定義
#define NUM_KEY_MAX (256)				//	キーの最大数
#define NUM_MAUSE_MAX (3)				//	マウスの最大数
#define MAX_PAD (2)						//	コントローラー

// グローバル変数宣言
XINPUT_STATE g_joyKeyState[PLAYER_MAX] = {};	        //ジョイパッドのプレス情報
XINPUT_STATE g_OldKeyState[PLAYER_MAX] = {};
XINPUT_STATE g_joyKeyStateTrigger[PLAYER_MAX] = {};		//ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRelease[PLAYER_MAX] = {};		//ジョイパッドのリリース情報

LPDIRECTINPUT8 g_pInput = NULL;				            //DeirectInputへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	            //入力デバイスへのポインタ
LPDIRECTINPUT8 g_pInputMause = NULL;				    //DeirectInputへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMause = NULL;	            //入力デバイスへのポインタ

BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldState[NUM_KEY_MAX];
BYTE g_aMauseState[NUM_MAUSE_MAX];
BYTE g_aOldMauseState[NUM_MAUSE_MAX];

DIMOUSESTATE g_CurrentMouseState;		                //!< マウスの現在の入力情報
DIMOUSESTATE g_PrevMouseState;			                //!< マウスの一フレーム前の入力情報
DIMOUSESTATE g_Oldpos;		                            //!< マウスの現在の入力情報

//================================================
// キーボードの初期化処理
//================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//	Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//	入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//	データフォーマットの設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//	協調モード
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//	キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//================================================
// キーボードの終了処理
//================================================
void UninitKeyboard(void)
{
	// 入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); //キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//================================================
// キーボードの更新処理
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  // キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey]; // キーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; // キーボードプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}
//================================================
// キーボードのプレス処理
//================================================
bool GetKeyboardPress(int nKey)
{// 押されてるキー
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//================================================
// キーボードのトリガー処理
//================================================
bool KeybordTrigger(int nKey)
{// 一歩だけ
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// キーボードのリリース処理
//================================================
bool KeybordRelease(int nKey)
{// 長押し
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// キーボードのリピート処理
//================================================
bool KeybordRepeat(int nKey)
{// 押されてる間
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================================
// ジョイパッドの初期化処理
//================================================
HRESULT InitJoypad(void)
{
	for (int count = 0; count < PLAYER_MAX; count++)
	{
		// メモリのクリア
		memset(&g_joyKeyState[count], 0, sizeof(XINPUT_STATE));
	}
	
	// Xinputのステートの設定(有効にする
	XInputEnable(true);

	return S_OK;
}
//================================================
// ジョイパッドの終了処理
//================================================
void UninitJoypad(void)
{
	//	Xinputのステートの設定(無効にする
	XInputEnable(false);
}
//================================================
// ジョイパッドの更新処理
//================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState[MAX_PAD]; // 入力情報

	for (int p = 0; p < PLAYER_MAX; p++)
	{
		g_OldKeyState[p] = g_joyKeyState[p]; // キーボードプレス情報を保存

		// ジョイパッドの状態を取得
		if (XInputGetState(0, &joyKeyState[p]) == ERROR_SUCCESS)
		{
			WORD Button = joyKeyState[p].Gamepad.wButtons;
			WORD OldButton = g_joyKeyState[p].Gamepad.wButtons;

			g_joyKeyStateTrigger[p].Gamepad.wButtons = Button & ~OldButton;

			g_joyKeyStateRelease[p].Gamepad.wButtons = Button & ~OldButton;

			g_joyKeyState[p] = joyKeyState[p]; // ジョイパッドのプレス情報を保存
		}
	}
}
//================================
// ジョイパッドプレス情報を取得
//================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//================================
// ジョイパッドトリガー情報を取得
//================================
bool JoyPadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//================================
// ジョイパッドリリース情報を取得
//================================
bool JoyPadRelease(JOYKEY key)
{
	return (g_joyKeyStateRelease[0].Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//================================
//コントローラーの振動処理
//================================
void VibrateController(int ContorollerID, WORD leftMoter, WORD rightMoter)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = leftMoter;
	vibration.wRightMotorSpeed = rightMoter;

	//振動開始
	XInputSetState(ContorollerID, &vibration);
}
//====================================
// ゲーム内での振動処理を管理する関数
//====================================
void UpdateVibration(VibrationState* vibrationState)
{
	DWORD currentTime = GetTickCount();
	Player* pPlayer = GetPlayer();

	if (pPlayer->nLife > 0)
	{
		if (currentTime - vibrationState->startTime < vibrationState->duration)
		{
			//振動中
			VibrateController(vibrationState->contorollerID, vibrationState->leftMoter, vibrationState->rightMoter);
		}
		else
		{
			//振動終了
			VibrateController(vibrationState->contorollerID, 0, 0);
		}
	}
	else
	{
		//振動終了
		VibrateController(vibrationState->contorollerID, 0, 0);
	}
}
//=================================
//振動を終了させる処理
//=================================
void StartVibration(VibrationState* vibrationState, int VibrationTime,int leftMoter,int rightMoter)
{
	vibrationState->contorollerID = 0;			//コントローラーID
	vibrationState->leftMoter = leftMoter;		//最大60000
	vibrationState->rightMoter = rightMoter;	//最大60000
	vibrationState->startTime = GetTickCount();	//開始時刻
	vibrationState->duration = VibrationTime;	//200㍉秒
}

//================================
// ジョイパッド情報を取得
//================================
XINPUT_STATE* GetState(void)
{
	return &g_joyKeyStateTrigger[0];
}
//================================
// ジョイパッドの入力情報取得
//================================
int GetJoypadInputState(int InputType)
{
	return S_OK;
}
//=================================
// ジョイパッドのスティック操作
//=================================
bool GetJoyStick(int player)
{
	bool joykey[PLAYER_MAX] = { false };
	int b = 0;

	// 左スティック
	if (g_joyKeyState[player].Gamepad.sThumbLX > 100 ||
		g_joyKeyState[player].Gamepad.sThumbLX < -100 ||
		g_joyKeyState[player].Gamepad.sThumbLY > 100 ||
		g_joyKeyState[player].Gamepad.sThumbLY < -100)
	{
		joykey[player] = true;
	}

	// 右スティック
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
// ジョイパッドのスティックの情報取得
//=====================================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState[0];
}
//=====================================
// マウスの初期化処理
//=====================================
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd)
{
	// Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputMause, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMause, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(g_pDevMause->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モード
	if (FAILED(g_pDevMause->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	g_pDevMause->Acquire();

	return S_OK;
}
//=====================================
// マウスの終了処理
//=====================================
void UninitMausu(void)
{
	// 入力デバイスの破棄
	if (g_pDevMause != NULL)
	{
		g_pDevMause->Unacquire(); // キーボードへのアクセス権を破棄
		g_pDevMause->Release();
		g_pDevMause = NULL;
	}

	// DirectInputオブジェクトの破棄
	if (g_pInputMause != NULL)
	{
		g_pInputMause->Release();
		g_pInputMause = NULL;
	}
}
//=====================================
// マウスの更新処理
//=====================================
void UpdateMausu(void)
{
	g_Oldpos = g_CurrentMouseState;

	// 更新前に最新マウス情報を保存する
	g_PrevMouseState = g_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);

	if (FAILED(hr1))
	{
		g_pDevMause->Acquire();
		hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}

	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	g_CurrentMouseState.lX = p.x;
	g_CurrentMouseState.lY = p.y;
}
//=====================================
// マウスが押された処理
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
// マウスが離された処理
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