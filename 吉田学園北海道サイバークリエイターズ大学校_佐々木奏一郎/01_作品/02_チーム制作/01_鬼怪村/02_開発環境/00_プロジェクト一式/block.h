//=============================================================================
//
//	ブロック処理 [block.h]
// Author : 佐々木奏一郎
//
//=============================================================================

#ifndef _BLOCK_H_	// このマクロ定義がされていなかったら
#define _BLOCK_H_	// 2銃インクルード防止のマクロ定義

// インクルードファイル
#include "main.h"

// マクロ定義
#define BLOCK_TEXTURE (128) // ブロックのテクスチャの最大数
#define NUM_BLOCK (200)		// ブロックの最大数

// ブロックの種類の列挙型
typedef enum
{
	// 家2
	BLOCK_HOUSE000_L = 0,
	BLOCK_HOUSE000_r,

	// 家3
	BLOCK_HOUSE01_L,
	BLOCK_HOUSE01_R,

	// 家4
	BLOCK_HOUSE04_L,
	BLOCK_HOUSE04_R,

	// 慰霊碑
	BLOCK_IREIHI,

	// 看板
	BLOCK_KANBAN,

	// 蔵
	BLOCK_KURA,

	// クモとクモの巣
	BLOCK_KUMO,
	BLOCK_KUMONOSU,

	// 鳥小屋
	BLOCK_TORIGOYA,

	// 井戸
	BLOCK_WELL,

	// 電柱(木製)
	BLOCK_WTPOLE,

	// 枯れてる木
	BLOCK_DEADTREE,

	// スピーカー
	BLOCK_SPEACAR,

	// 鍵
	BLOCK_KEY,
	BLOCK_KEYBOTTOM,
	BLOCK_KEYTOP,

	// 壁
	BLOCK_WALL00,
	BLOCK_WALL01,
	BLOCK_MAX

}BLOCKTYPE;

// ブロックのテクスチャ構造体
typedef struct
{
	LPD3DXMESH pMesh;								// メッシュ（頂点情報)へのポインタ
	LPDIRECT3DTEXTURE9 apTexture[BLOCK_TEXTURE];	// テクスチャへのポインタ
	LPD3DXBUFFER pBuffMat;							// マテリアルへのポインタ
	DWORD dwNumMat;									// マテリアルの数
	D3DXVECTOR3 vtxMin, vtxMax;						// モデルの最小値,最大値

}BLOCKTEX;

// ブロックの構造体情報
typedef struct
{
	BLOCKTEX tex;						// テクスチャ情報
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	int nType;							// 種類
	bool bUse;							//使用しているかどうか

}BLOCK;

// xファイルの種類
static const char* X_BLOCK[BLOCK_MAX] =
{
	//　家2個目
	"data\\model\\house000_L.x",
	"data\\model\\house000_r.x",

	// 家3個目
	"data\\model\\house01_L.x",
	"data\\model\\house01_R.x",

	// 家4個目
	"data\\model\\house04_L.x",
	"data\\model\\house04_R.x",

	// 慰霊碑
	"data\\model\\ireihi.x",

	// 看板
	"data\\model\\kanban.x",

	// 蔵
	"data\\model\\kura.x",

	// クモ、クモの巣
	"data\\model\\kumo.x",
	"data\\model\\kumonosu.x",

	// 鳥小屋
	"data\\model\\torigoya.x",


	// 井戸
	"data\\model\\Well.x",

	// 電柱(木製)
	"data\\model\\WoodenTelephonePole.x",

	// 枯れてる木
	"data\\model\\deadtree000.x",

	// スピーカー
	"data\\model\\speacar.x",

	// 鍵
	"data\\model\\key.x",
	"data\\model\\key_bottom.x",
	"data\\model\\key_top.x",

	// 壁
	"data\\model\\wall00.x",
	"data\\model\\wall01.x",
};

// プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld);

#endif