//=============================================================================
//
//	ゲーム処理 [game.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
typedef enum
{
	GAMESTATE_NONE=0,//何もしていない状態
	GAMESTATE_NORMAL,//通常状態
	GAMESTATE_END,//終了処理
	GAMESTATE_MAX
}GAMESTATE;
//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetEnblePause(bool bPause);
#endif
