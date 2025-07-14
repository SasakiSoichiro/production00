//=============================================================================
//
//	アイテム持つの処理 [objective.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _OBJECTIVE_H_//このマクロ定義がされていなかったら
#define _OBJECTIVE_H_//2重インクルード防止のマクロ定義
#include "main.h"

typedef enum
{
	OBJECTIVETYPE_OBJECTIVE = 0,	//目的
	OBJECTIVETYPE_WAKU1,			//枠
	OBJECTIVETYPE_WAKU2,			//枠
	OBJECTIVETYPE_CHECK,			//チェック
	OBJECTIVETYPE_TEXT1,			//ミッション1
	OBJECTIVETYPE_TEXT2,			//ミッション2
	OBJECTIVETYPE_MAX
}OBJECTIVETYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//動き
	float fWidth;			//幅
	float fHeight;			//高さ
	OBJECTIVETYPE nType;	//ブロックのタイプ
	bool bUse;				//使用しているかどうか
	bool bText;				//テキストの使用確認
}OBJECTIVE;

static const char* OBJECTIVE_TEXTURE[OBJECTIVETYPE_MAX] =
{
	"data\\texture\\objective1.png",		//目的
	"data\\texture\\waku3.png",			//枠
	"data\\texture\\waku3.png",			//枠
	"data\\texture\\check.png",			//チェック
	"data\\texture\\text1.png",			//ミッション1
	"data\\texture\\text2.png",			//ミッション2
};

//プロトタイプ宣言
void InitObjective(void);
void UninitObjective(void);
void UpdateObjective(void);
void DrawObjective(void);
void SetObjective(D3DXVECTOR3 pos,float fWidth,float fHeight,OBJECTIVETYPE nType);
OBJECTIVE* GetObjective();
#endif