//=============================================================================
//
//	体力の処理 [stamina.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _STAMINA_H_//このマクロ定義がされていなかったら
#define _STAMINA_H_//2銃インクルード防止のマクロ定義
#include "main.h"

typedef enum
{
	STAMINA_GAUGE=0,
	STAMINA_FRAME,
	STAMINA_MAX
}STAMINA;

//プロトタイプ宣言
void InitStamina(void);
void UninitStamina(void);
void UpdateStamina(void);
void DrawStamina(void);
bool GetStamina(void);

#endif