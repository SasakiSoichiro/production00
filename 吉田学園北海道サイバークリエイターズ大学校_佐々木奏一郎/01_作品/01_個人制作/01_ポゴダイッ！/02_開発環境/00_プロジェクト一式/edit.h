//=============================================================================
//
//	編集処理 [edit.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _EDIT_H_//このマクロ定義がされていなかったら
#define _EDIT_H_//2重インクルード防止のマクロ定義

#include "main.h"
#include "block.h"

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void LoadEdit(void);
void SaveEdit(void);
int GetStage(void);

#endif