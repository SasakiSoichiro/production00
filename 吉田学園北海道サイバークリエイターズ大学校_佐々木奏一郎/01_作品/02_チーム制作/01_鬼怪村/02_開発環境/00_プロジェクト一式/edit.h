//=============================================================================
//
//	エディット処理 [edit.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _EDIT_H_//このマクロ定義がされていなかったら
#define _EDIT_H_//2銃インクルード防止のマクロ定義

#include "main.h"

//マクロ定義
#define NUM_EDIT (200)
#define EDITTEXTURE (128)	// テクスチャの最大数
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"

// 家の種類
typedef enum
{
	// 家2
	EDIT_HOUSE000_L = 0,
	EDIT_HOUSE000_r,

	// 家3
	EDIT_HOUSE01_L,
	EDIT_HOUSE01_R,

	// 家3
	EDIT_HOUSE04_L,
	EDIT_HOUSE04_R,

	// 慰霊碑
	EDIT_IREIHI,

	// 看板
	EDIT_KANBAN,

	// 蔵
	EDIT_KURA,

	// クモとクモの巣
	EDIT_KUMO,
	EDIT_KUMONOSU,

	// 鳥小屋
	EDIT_TORIGOYA,

	// 井戸
	EDIT_WELL,

	// 電柱(木製)
	EDIT_WTPOLE,

	// 枯れてる木
	EDIT_DEADTREE,

	// スピーカー
	EDIT_SPEACAR,

	// 鍵
	EDIT_KEY,
	EDIT_KEYBOTTOM,
	EDIT_KEYTOP,

	// 壁
	EDIT_WALL00,
	EDIT_WALL01,
	EDIT_MAX

}EDITTYPE;

// テクスチャの構造体
typedef struct
{
	LPD3DXMESH pMesh;							// メッシュ（頂点情報)へのポインタ
	LPDIRECT3DTEXTURE9 apTexture[EDITTEXTURE];	// テクスチャへのポインタ
	LPD3DXBUFFER pBuffMat;						// マテリアルへのポインタ
	DWORD dwNumMat;								// マテリアルの数
}EDITTEX;

// 構造体
typedef struct
{
	EDITTEX tex[EDIT_MAX];				// テクスチャ情報
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 move;					// 移動
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3 vtxMin, vtxMax;			// モデルの最小値,最大値
	int nType;							// 種類
	bool bUse;							// 使用しているか

}EDITINFO;

static const char* X_EDIT[EDIT_MAX] =
{
	// 家2個目
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
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveEdit(void);
void LoadEdit(void);
void ReloadEdit(void);
#endif