//=============================================================================
//
//	敵の処理 [enemy.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _ENEMY_H_//このマクロ定義がされていなかったら
#define _ENEMY_H_//2銃インクルード防止のマクロ定義

#include "main.h"
#include "model.h"

// マクロ定義
#define GRAVI (0.05f)			// 重力
#define JUMP (2.0f)
#define OBJ_E (20.0f)
#define EPARTS_MAX (16)
#define EUSEPARTS_MAX (16)
#define POINT_MAX (10)
#define EBLEND_FRAME (10)
#define MAX_ENEMY (1)

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		// 徘徊
	ENEMYSTATE_CHASE,			// 追いかける
	ENEMYSTATE_DAMAGE,			// スタン
	ENEMYSTATE_ACTION,			// 攻撃
	ENEMYSTATE_MAX

}ENEMYSTATE;

//モーションの種類
typedef enum
{
	EMOTIONTYPE_NEUTRAL = 0,	// 着地
	EMOTIONTYPE_MOVE,			// ダッシュ
	EMOTIONTYPE_ACTION,			// アクション
	EMOTIONTYPE_JUMP,			// ジャンプ
	EMOTIONTYPE_LANDING,		// 着地
	EMOTIONTYPE_MAX

}EMOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;				// 位置
	float fPosY;
	float fPosZ;
	float fRotX;				// 向き
	float fRotY;
	float fRotZ;

}EKEY;

//キー情報の構造体
typedef struct
{
	int nFlame;					// 再生フレーム
	EKEY aKey[EPARTS_MAX];		// パーツの最大数を入れる//キー情報

}EKEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;					// ループするかどうか
	int nNumKey;				// キーの総数
	EKEY_INFO aKeyInfo[10];		// キーの最大数//キー情報
}EMOTION_INFO;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posVec[2];		// 視野用ベクトル
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nLife;
	int nType;
	int State;
	int OldState;
	float fRad;
	bool bUse;

	Model aModel[EPARTS_MAX];	// モデルのパーツ数
	int nNumModel;				// モデルのパーツ総数

	EMOTION_INFO aMotionInfo[8];// モーションの最大数
	int nNumMotion;				// モーションの総数
	EMOTIONTYPE motionType;		// モーションの種類
	bool bLoopMotion;			// ループするかどうか
	int nNumKey;				// キーの総数
	int nKey;					// 現在のキーNo.
	int nCntMotion;				// モーションカウンター

	bool bFinishMotion;			// 現在のモーションが終了しているかどうか
	bool bBlendMotion;			// ブレンドモーションがあるかどうか
	EMOTIONTYPE motionTypeBlend;// モーションの種類
	int nNumKeyBlend;			// キーの総数
	int nKeyBlend;				// 現在のキーNo.
	int nCntMotionBlend;		// モーションカウンター
	int nFrameBlend;			// ブレンドのフレーム数
	int nCntBlend;				// ブレンドカウンター

	int nIdxLife;				// ライフバーのIdx
	int IdxShadow;
	int nCount;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void LoadEnemy(int nType);
void CollisionEnemy(void);
void HitEnemy(int nCnt, int nDamage);
void CollisionEnemytoEnemy(int nCnt);
void LoiterEnemy(void);
Enemy*GetEnemy(void);
int GetNumEnemy();
bool IsRange();
void SetMotionType(EMOTIONTYPE MotionType, bool bBlendMotion, int nFrameBlend,int nCnt);
void SetEnemyDistance(float fDistance);

static const char* EPARTS_FILE[EPARTS_MAX] =
{
	"data\\model\\redcar000.x",//胴
	"data\\model\\spear.x",		//頭
};
//-------------------
//敵の足音管理
//-------------------
//void SetEnemyDistance(float fDistance)
//{
//	if (fDistance < 200.0f)
//	{
//		SetVolume()
//	}
//}

#endif