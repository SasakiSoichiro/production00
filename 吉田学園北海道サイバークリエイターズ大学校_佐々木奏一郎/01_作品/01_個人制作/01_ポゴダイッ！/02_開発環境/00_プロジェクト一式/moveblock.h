//=============================================================================
//
//	ムーブブロック処理 [moveblock.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MOVEBLOCK_H_//このマクロ定義がされていなかったら
#define _MOVEBLOCK_H_//2重インクルード防止のマクロ定義
#include "main.h"
#define MAX_BLOCKHEIGHT (20.0f)
#define MAX_BLOCKWIDTH (20.0f)
#define MAX_BUTTONHEIGHT (10.0f)
#define MAX_WALLWIDTH (10.0f)


//ムーブブロックの状態
typedef enum
{
	BLOCK_BEFORE = 0,
	BLOCK_MOVE,
	BLOCK_AFTER,
	BLOCK_MOVEMAX
}MOVEBLOCK;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//ブロックのタイプ
	bool bUse;			//使用しているかどうか
}MoveBlock;

static const char* MOVEBLOCK_TEXTURE[BLOCK_MOVEMAX] =
{
	"data\\TEXTURE\\surinuke000.png",		//取る前
	"data\\TEXTURE\\surinuke001.png",		//動いてるとき
	"data\\TEXTURE\\surinuke002.png",		//使ったあと
};

//プロトタイプ宣言
void InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);
void SetMoveBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
bool CollisionMoveBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPYPos, D3DXVECTOR3* pPYPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
#endif