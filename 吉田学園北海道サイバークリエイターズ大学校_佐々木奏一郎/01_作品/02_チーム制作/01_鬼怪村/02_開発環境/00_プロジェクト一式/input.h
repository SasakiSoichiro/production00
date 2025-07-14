//=============================================================================
//
//	入力処理 [input.h]
// Author : HRT ryuusei
//
//=============================================================================
#ifndef _INPUT_H_// このマクロ定義がされていなかったら
#define _INPUT_H_// 2重インクルード防止のマクロ定義

//======================
// インクルードファイル
//======================
#include "main.h"

//================
//	キーの種類
//================
typedef enum
{
	JOYKEY_UP = 0,	//	十字キー(↑)
	JOYKEY_DOWN,	//	十字キー(↓)
	JOYKEY_LEFT,	//	十字キー(←)
	JOYKEY_RIGHT,	//	十字キー(→)
	JOYKEY_START,	//	スタート
	JOYKEY_BACK,	//	バック
	JOYKEY_LPUSH,	//	スティック押し込み	左
	JOYKEY_RPUSH,	//	スティック押し込み	右
	JOYKEY_LB,		//	L1
	JOYKEY_RB,		//	R1
	JOYKEY_LT,		//	L2
	JOYKEY_RT,		//	R2
	JOYKEY_A,		//	Aボタン
	JOYKEY_B,		//	Bボタン
	JOYKEY_X,		//	Xボタン
	JOYKEY_Y,		//	Yボタン
	JOYKEY_MAX
}JOYKEY;

//======================
// マウスの種類
//======================
typedef enum
{
	MOUSE_L = 0, // マウス左
	MOUSE_R,     // マウス右
	MOUSE_H,     // マウスホイール
	MOUSE_MAX
}MouseButton;

//======================
// プレイヤーの種類
//======================
typedef enum
{
	PLAYER_1 = 0, // プレイヤー1
	PLAYER_2,     // プレイヤー2
	PLAYER_MAX
}PLAYER;

//======================
// パッドの種類
//======================
typedef enum
{
	DX_INPUT_KEY_PAD1 = 0, // キー入力とパッド１
	DX_INPUT_PAD1,         // パッド１
	DX_INPUT_PAD2,         // パッド２
	DX_INPUT_KEY,          // キー入力
	DX_INPUT_MAX
}InputType;

//=========================
//振動状態を管理する構造体
//=========================
typedef struct
{
	int contorollerID;
	WORD leftMoter;
	WORD rightMoter;
	DWORD startTime;
	DWORD duration;
}VibrationState;

//==================
// プロトタイプ宣言
//==================
// キーボード
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeybordTrigger(int nKey);
bool KeybordRelease(int nKey);
bool KeybordRepeat(int nKey);

// ジョイパッド
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
bool JoyPadRelease(JOYKEY key);
bool GetJoyStick(int player);
XINPUT_STATE* GetJoyStickAngle(void);
XINPUT_STATE* GetState(void);
int GetJoypadInputState(int InputType);
void VibrateController(int ContorollerID, WORD leftMoter, WORD rightMoter);
void UpdateVibration(VibrationState* vibrationState);
void StartVibration(VibrationState* vibrationState, int VibrationTime, int leftMoter, int rightMoter);

// マウス
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd);
void UninitMausu(void);
void UpdateMausu(void);
bool OnMouseDown(MouseButton button_type);
bool OnMouseUp(MouseButton button_type);
D3DXVECTOR2 GetMouseVelocity();
D3DXVECTOR2 GetMouseVelocityOld();

#endif