//=============================================================================
//
//	敵視点のビューポートの枠の処理 [viewportwaku.h]
// Author : 近田尚也
//
//=============================================================================
#ifndef _UNLOCK_H_//このマクロ定義がされていなかったら
#define _UNLOCK_H_//2重インクルード防止のマクロ定義
#include "main.h"

//プロトタイプ宣言
void InitUnlock(void);
void UninitUnlock(void);
void UpdateUnlock(void);
void DrawUnlock(void);
#endif
