//=============================================================================
//
//	インプット処理 [input.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _INPUT_H_//このマクロ定義がされていなかったら
#define _INPUT_H_//２重インクルード防止のマクロ定義
#include "main.h"
//キーの種類
typedef enum
{
	JOYKEY_UP=0,		//十字キー(上)
	JOYKEY_DOWN,		//十字キー(下)
	JOYKEY_LEFT,		//十字キー(左)
	JOYKEY_RIGHT,		//十字キー(右)
	JOYKEY_START,		//スタートボタン
	JOYKEY_BACK,		//バックボタン
	JOYKEY_LEFTTHUMB,	//左スティックボタン押下
	JOYKEY_RIGHTTHUMB,	//右スティックボタン押下
	JOYKEY_LEFTS,		//LBボタン
	JOYKEY_RIGHTS,		//RBボタン
	JOYKEY_UNNOWN,		//使えない
	JOYKEY_NASHI,		//使えない
	JOYKEY_A,			//Aボタン
	JOYKEY_B,			//Bボタン
	JOYKEY_X,			//Xボタン
	JOYKEY_Y,			//Yボタン
	JOYKEY_N,			//なにこれ
	JOYKEY_W,			//なにこれ
	JOYKEY_MAX
}JOYKEY;

//プロトタイプ宣言
HRESULT  InitKeyboard(HINSTANCE hInstance,HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);
HRESULT  InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
XINPUT_STATE* GetJoypad(void);
#endif