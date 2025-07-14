//====================================================
//
// 表示の処理 [UI.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _UI_H_
#define _UI_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_TIMEWIDTH (150)
#define MAX_TIMEHEIGHT (100)
#define MAX_TEX (2)

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitEyeUI();
void UninitEyeUI();
void UpdateEyeUI();
void DrawEyeUI();
//void SetUI();
//bool GetMinUI();


#endif