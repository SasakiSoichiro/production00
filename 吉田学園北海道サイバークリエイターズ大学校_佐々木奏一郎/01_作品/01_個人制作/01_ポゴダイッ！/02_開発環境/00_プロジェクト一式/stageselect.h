//=============================================================================
//
//	ステージ選択処理 [stageselect.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "main.h"
//ポーズメニュー
typedef enum
{
	STAGE_1=0,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_7,
	STAGE_8,
	STAGE_9,
	STAGE_10,
	STAGE_MAX
}STAGE;

typedef struct
{
	
};

static const char* STAGE_TEXTURE[STAGE_MAX] =
{
	"data\\TEXTURE\\001.png",
	"data\\TEXTURE\\002.png",
	"data\\TEXTURE\\003.png",
	"data\\TEXTURE\\004.png",
	"data\\TEXTURE\\005.png",
	"data\\TEXTURE\\006.png",
	"data\\TEXTURE\\007.png",
	"data\\TEXTURE\\008.png",
	"data\\TEXTURE\\009.png",
	"data\\TEXTURE\\010.png"
};
//プロトタイプ宣言
void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);
int GetStageSelect(void);
#endif