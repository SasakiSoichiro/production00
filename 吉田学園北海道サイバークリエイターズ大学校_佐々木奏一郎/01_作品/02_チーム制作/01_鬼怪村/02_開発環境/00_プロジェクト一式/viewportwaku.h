//=============================================================================
//
//	敵視点のビューポートの枠の処理 [viewportwaku.h]
// Author : 近田尚也
//
//=============================================================================
#ifndef _VIEWPORTWAKU_H_//このマクロ定義がされていなかったら
#define _VIEWPORTWAKU_H_//2重インクルード防止のマクロ定義
#include "main.h"

//プロトタイプ宣言
void InitViewUI(void);
void UninitViewUI(void);
void UpdateViewUI(void);
void DrawViewUI(void);
#endif