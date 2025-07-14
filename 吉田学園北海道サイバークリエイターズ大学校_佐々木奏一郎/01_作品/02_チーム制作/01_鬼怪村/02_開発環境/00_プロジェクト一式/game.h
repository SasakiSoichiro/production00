//=============================================================================
//
//	�Q�[������ [game.h]
// Author : Ryuusei Hirata
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//	�񋓌^
typedef enum
{
	GAMESTATE_NONE = 0,	// �������Ă��Ȃ����
	GAMESTATE_NORMAL,	// �ʏ���
	GAMESTATE_END,		// �I�����
	GAMESTATE_MAX
}GAMESTATE;

// �v���g�^�C�v
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(int nIdx);
void SetEnablePause(bool bPause);
void SetGameState(GAMESTATE state);
bool GetEditState(void);

#endif // !_GAME_H_
