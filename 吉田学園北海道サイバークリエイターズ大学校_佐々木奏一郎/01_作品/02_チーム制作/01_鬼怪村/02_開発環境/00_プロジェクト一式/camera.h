//=============================================================================
//
//	ブロック処理 [block.h]
// Author : 佐々木奏一郎
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

// マクロ定義
#define MAX_CAMERA (2)

// 構造体
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 rotDest;		// 目的の向き
	D3DXVECTOR3 posRDest;		// 目的の位置(右)
	D3DXVECTOR3 posVDest;		// 目的の位置(左)
	D3DVIEWPORT9 viewport;		// ビューポート
	float fDistance;			// 視点から注視点の距離
	float deltaX;				// デルタX
	float deltaY;				// デルタY
	POINT cursorPos;			// マウスカーソルの位置
	POINT prevCursorPos;		// カーソルの見える位置
}Camera;

// ぷろとたいぷ
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
void MouseWheel(int zDelta);
Camera* GetCamera(void);

#endif // !_CAMERA_H_
