//=============================================================================
//
// サウンド処理 [sound.h]
// Author : yabuki yukito
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM = 0,
	SOUND_LABEL_BGM2,
	SOUND_LABEL_BGM3,
	SOUND_LABEL_SE,
	SOUND_LABEL_SE1,
	SOUND_LABEL_SE2,
	SOUND_LABEL_SE3,
	SOUND_LABEL_SE4,
	SOUND_LABEL_SE5,
	SOUND_LABEL_SE6,
	SOUND_LABEL_SE7,
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void SetVolume(SOUND_LABEL label,float volume);

#endif
