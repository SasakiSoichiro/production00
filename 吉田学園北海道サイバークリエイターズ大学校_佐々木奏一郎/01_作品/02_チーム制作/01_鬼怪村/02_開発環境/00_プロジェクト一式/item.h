//=============================================================================
//
// アイテム処理 [item.h]
// Author : HRT ryuusei
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// マクロ定義
#define MAX_ITEM (6)

// 種類の列挙型
typedef enum
{
    ITEMTYPE_ONE = 0,    // 鍵の上部
    ITEMTYPE_TWO,        // 鍵の下部
    ITEMTYPE_THREE,      // 懐中時計
    ITEMTYPE_FOUR,       // なぎなた
    ITEMTYPE_FIVE,       // 救急箱
    ITEMTYPE_SIX,        // 懐中電灯
    ITEMTYPE_MAX
}ITEMTYPE;

// モデル列挙型
static const char* ITEM_MODEL[ITEMTYPE_MAX] =
{
    "data\\model\\key_top.x",
    "data\\model\\key_bottom.x",
    "data\\model\\pocketwatch000.x",
    "data\\model\\naginata.x",
    "data\\model\\recovery.x",
    "data\\model\\flashlight.x",
};

typedef struct
{
    LPD3DXMESH pMesh;                   //  頂点情報のポインター
    LPDIRECT3DTEXTURE9 pTexture[128];   //  テクスチャのポインター
    LPD3DXBUFFER pBufferMat;            //  マテリアルのポインター
    DWORD dwNuMat;                      //  マテリアルの数
}ITEMINFO;

// アイテム構造体
typedef struct
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    D3DXMATRIX mtxWorld;
    int nType;
    bool bUse;
    bool bHave;
    bool bOldHave;
    bool bHold;
    int nIdxUI;
}ITEM;

// プロトタイプ宣言
void Inititem(void);
void Uninititem(void);
void Updateitem(void);
void Drawitem(void);
ITEM* Getitem(void);
void Setitem(D3DXVECTOR3 pos, int nType);
bool IsNeed();

#endif // !_ITEM_H_