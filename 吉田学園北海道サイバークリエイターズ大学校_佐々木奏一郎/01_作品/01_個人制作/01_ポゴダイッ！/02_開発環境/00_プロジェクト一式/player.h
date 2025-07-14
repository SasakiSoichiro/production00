//=============================================================================
//
//	プレイヤー処理 [player.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PLAYER_H_				//このマクロ定義がされていなかったら
#define _PLAYER_H_				//2重インクルード防止のマクロ定義
#define GRAVI (0.15f)			//重力
#define JUMP (8.0f)				//ジャンプ力
#define SLIMEJUMP (4.0f)
#define TRANPORINJUMP (12.0f)
#define MOVE_X (3.0f)			//X軸移動量
#define MAX_POSCIRCLE (15.0f)	//サークル半径
#define MAX_PGPOS (15.0f)		//ポゴの当たり判定座標
#define MAX_PYPOS (45.0f)		//プレイヤーの当たり判定座標
#include "block.h"


//プレイヤー状態の種類
typedef enum
{
	PLAYERSTATE_APPEAR=0,	//出現状態（点滅）
	PLAYERSTATE_NORMAL,		//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;
//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 posPGCircle;	//ポゴ当たり判定用の位置
	D3DXVECTOR3 posPYCircle;	//プレイヤー当たり判定用の位置
	D3DXVECTOR3 posPGOld;		//前回のポゴ当たり判定用の位置
	D3DXVECTOR3 posPYOld;		//前回のプレイヤー当たり判定用の位置
	D3DXVECTOR3 move;			//移動量
	PLAYERSTATE state;			//プレイヤーの状態
	int nCntState;				//状態管理カウンター
	int nLife;					//体力
	bool bDisp;					//表示するかしないか
	D3DXVECTOR3 rot;			//向き
	float fLength;				//対角線の長さ
	float fAngle;				//対角線の角度
	int nCounterAnim;			//カウンター
	int nPatternAnim;			//パターンNo.
	bool bJump;					//ジャンプしているかしてないか
	bool bRightMove;			//右か左か
	bool bMove;					//動いているかとまっているか
	Block* pBlock;				//対象ブロックへのポインタ
	bool bUse;					//使っているかどうか
}Player;
//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
#endif