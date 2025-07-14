//=============================================================================
//
//	メッシュウォール処理 [meshwall.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MESHWALL_H_//このマクロ定義がされていなかったら
#define _MESHWALL_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#define OBJ_V (250.0f)
#define OBJ_H (400.0f)
#define VMESH (30)
#define HMESH (30)
#define VTXCNT ((VMESH+1)*(HMESH+1))
#define POLYCNT ((2*VMESH*HMESH)+4*(VMESH-1))
#define IDXCNT (((VMESH+1)*2*HMESH)+(HMESH-1)*4)
#define RADIUS (1000)
//#define IDXCNT (POLYCNT+2)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 VtxPos[VTXCNT];
	D3DXMATRIX mtxWorld;
}MeshWall;
//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void CollisionCyrynder(void);

#endif