//=============================================================================
//
//	ポーズ処理 [pause.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PAUSE__H_
#define _PAUSE_H_
#include "main.h"
//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE=0,//ゲームに戻る
	PAUSE_MENU_RETRY,//ゲームをやり直す
	PAUSE_MENU_QUIT,//タイトル画面に戻る
	PAUSE_MENU_MAX
}PAUSE_MENU;
//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif