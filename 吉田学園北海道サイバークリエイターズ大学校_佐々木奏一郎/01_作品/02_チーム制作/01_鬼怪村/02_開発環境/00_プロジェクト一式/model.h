//=============================================================================
//
//	モデル処理 [model.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MODEL_H_//このマクロ定義がされていなかったら
#define _MODEL_H_//2銃インクルード防止のマクロ定義
#include "main.h"

//マクロ定義
#define MAX_MODEL (128)

typedef enum
{
	MODELTYPE_0,
	MODELTYPE_1,
	MODELTYPE_2,
	MODELTYPE_MAX
}Mtype;

static const char* MODEL[MODELTYPE_MAX] =
{
	"data\\model\\house000.x",
	"data\\model\\flashlight.x",
};

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルへのポインタ
	DWORD dwNumMat;//マテリアルの数
	int nIdxModelParent;//親モデルのインデックス
	D3DXVECTOR3 pos;//位置(オフセット)
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 posFirst;//位置(オフセット)
	D3DXVECTOR3 rotFirst;//向き
	D3DXVECTOR3 vtxMin, vtxMax;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	LPDIRECT3DTEXTURE9 apTexture[256];
	D3DCOLORVALUE Diffuse, firstDiffuse;
	bool bUse;
	int nType;

}Model;

////プロトタイプ宣言
//void InitModel(void);
//void UninitModel(void);
//void UpdateModel(void);
//void DrawModel(void);
//void SetModel(D3DXVECTOR3 pos,int nType);

#endif