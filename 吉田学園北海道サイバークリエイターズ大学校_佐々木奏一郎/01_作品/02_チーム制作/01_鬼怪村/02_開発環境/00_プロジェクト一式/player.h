//=============================================================================
//
//    プレイヤー処理 [player.h]
//    Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PLAYERH//このマクロ定義がされていなかったら
#define _PLAYERH//2銃インクルード防止のマクロ定義

//インクルードファイル
#include "main.h"
#include "model.h"
#include "motion.h"

//マクロ定義
#define GRAVI (0.05f)            //重力
#define OBJ_P (10.0f)
#define PARTS_MAX (20)
#define USEPARTS_MAX (20)
#define MAX_PLAYER (1)

typedef enum
{
    PLAYERSTATE_NORMAL = 0,
    PLAYERSTATE_MOVE,
    PLAYERSTATE_DASH,
    PLAYERSTATE_DAMAGE,
    PLAYERSTATE_DEATH,
    PLAYERSTATE_BREATH,
    PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 posOld;
    D3DXVECTOR3 size;
    D3DXVECTOR3 move;
    D3DXVECTOR3 rot;
    D3DXVECTOR3 rotDest;
    D3DXVECTOR3 Offpos;
    D3DXMATRIX mtxWorld;//ワールドマトリックス
    D3DXMATRIX SwordmtxWorld;
    int nLife;
    int nType;
    int nStamina;
    int nCountA;
    bool bAttack;
    bool bCaught;
    PLAYERSTATE pState;
    Motion motion;
    bool bEye;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetMatrix(void);
void SetMotion(int nType);
Player* GetPlayer(void);
void ReadScriptPlayer(int nType);
void HitPlayer(int nDamege);

#endif