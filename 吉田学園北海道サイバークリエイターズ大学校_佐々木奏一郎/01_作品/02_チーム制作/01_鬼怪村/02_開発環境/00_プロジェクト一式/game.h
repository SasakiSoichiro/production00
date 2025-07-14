//=============================================================================
//
//	ゲーム処理 [game.h]
// Author : Ryuusei Hirata
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//	列挙型
typedef enum
{
	GAMESTATE_NONE = 0,	// 何もしていない状態
	GAMESTATE_NORMAL,	// 通常状態
	GAMESTATE_END,		// 終了状態
	GAMESTATE_MAX
}GAMESTATE;

// プロトタイプ
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(int nIdx);
void SetEnablePause(bool bPause);
void SetGameState(GAMESTATE state);
bool GetEditState(void);

#endif // !_GAME_H_
