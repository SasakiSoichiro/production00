//=============================================================================
//
//	ブロック処理 [Block.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _BLOCK_H_//このマクロ定義がされていなかったら
#define _BLOCK_H_//2重インクルード防止のマクロ定義
#include "main.h"

//マクロ定義
#define MAX_BLOCKHEIGHT (40.0f)		//ノーマルブロックのテクスチャの高さ
#define MAX_BLOCKWIDTH (40.0f)		//ノーマルブロックのテクスチャの幅
#define MAX_BUTTONHEIGHT (10.0f)	//ボタンブロックの高さ
#define MAX_WALLWIDTH (10.0f)		//壁ブロックの幅
#define MAX_BLOCK (128)				//ブロックの最大数
#define MAX_NUMBLOCK (8)			//ブロックの種類
#define MAX_MOVE (1.0f)				//動く速さ

typedef enum
{
	BLOCK_NORMAL = 0,
	BLOCK_BUTTON,
	BLOCK_MOVEWALL,
	BLOCK_SLIME,
	BLOCK_TRANPORIN,
	BLOCK_GOAL,
	BLOCK_LR,
	BLOCK_UPDOWN,
	BLOCK_MAX
}BLOCK;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//動き
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//ブロックのタイプ
	bool bUse;			//使用しているかどうか
}Block;

static const char* BLOCK_TEXTURE[BLOCK_MAX] =
{
	"data\\TEXTURE\\block000.png",		//ブロック
	"data\\TEXTURE\\button000.png",		//ボタン
	"data\\TEXTURE\\door001.png",		//動く壁
	"data\\TEXTURE\\suraimu000.png",	//スライム
	"data\\TEXTURE\\kinoko000.png",		//トランポリン
	"data\\TEXTURE\\goal000.png",		//ゴール
	"data\\TEXTURE\\LR000.png",			//横に
	"data\\TEXTURE\\UpDown000.png"		//トランポリン
};

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight,int nType);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPYPos, D3DXVECTOR3* pPYPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight,Block**pBlock);
bool GetGoal(void);
bool GetButton(void);

#endif