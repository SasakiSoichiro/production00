//=============================================================================
//
// 回復の処理 [Recovery.h]
// Author : Hirata ryuusei
//
//=============================================================================
#ifndef _RECOVERY_H_
#define _RECOVERY_H_

#include "main.h"

// フェードの状態
typedef enum
{
	Recovery_NONE = 0,	// 何もしていない状態
	Recovery_IN,		// フェードイン状態
	Recovery_OUT,		// フェードアウト状態
	Recovery_DRAW,
	Recovery_MAX
}Recovery_MODE;

// 回復の構造体
typedef struct
{
	D3DXCOLOR col;
	Recovery_MODE ui;
	bool bUse;
	int count;
}Recovery;

// プロトタイプ宣言
void InitRecovery(void);
void UinitRecovery(void);
void UpdateRecovery(void);
void DrawRecovery(void);
void SetRecovery(int count);

#endif // !_Recovery_H_
