//=============================================================================
//
//	ギミック処理 [gimmick.h]
// author chikada shouya
//
//=============================================================================

#ifndef _GIMMICK_H_
#define _GIMMICK_H_


#include "main.h"
#include "player.h"

#define MAX_DOOR (2)				//ドアの最大数

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き
	D3DXVECTOR3 move;				// 移動
	D3DXVECTOR3 size;				// サイズ
	D3DXVECTOR3 vtxMin, vtxMax;		// 頂点の最小最大
	D3DXMATRIX mtxWorld;			// マトリックス
	LPD3DXMESH pMesh;				   
	LPD3DXBUFFER pBuffMat;
	DWORD dwNumMat;
	bool bLanding;
	bool bUse;
	//bool bGoal;
	bool bMove;
}GIMMICK;

// 構造体
typedef struct
{
	int nHoldCount;
	int NoTouch;
	int HolTime;
	int count;
	bool bClear;
	bool bPush;
	bool bNoPush;
}HOLD;

// プロトタイプ宣言
void InitGimmick(void);
void UninitGimmick(void);
void UpdateGimmick(void);
void DrawGimmick(void);
void CollisionGimmick(D3DXVECTOR3* pPos,D3DXVECTOR3* pPosOld);
void SetGimmick(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
GIMMICK* GetGimmick(void);
bool IsGoal();
bool IsBill();
void IsHold(void);
HOLD* GetHold(void);

#endif