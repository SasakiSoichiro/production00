//=============================================================================
//
//	モーション処理 [motion.h]
// Author : SasakiSoichiro
//
//=============================================================================
#ifndef _MOTION_H_//このマクロ定義がされていなかったら
#define _MOTION_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#include "model.h"
#define PARTS_MAX (20)
#define MAX_WORD (256)

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//着地
	MOTIONTYPE_MOVE,		//移動
	MOTIONTYPE_RUN,			//ダッシュ
	MOTIONTYPE_DAMAGE,		//ダメージ
	MOTIONTYPE_DEATH,		//死
	MOTIONTYPE_BREATH,		//疲労
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;//位置
	float fPosY;
	float fPosZ;
	float fRotX;//向き
	float fRotY;
	float fRotZ;
}KEY;

//キー情報の構造体
typedef struct
{
	int nFlame;//再生フレーム
	KEY aKey[20];//パーツの最大数を入れる//キー情報

}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;//ループするかどうか
	int nNumKey;//キーの総数
	KEY_INFO aKeyInfo[30];//キーの最大数//キー情報
}MOTION_INFO;




//プレイヤー構造体
typedef struct
{
	Model aModel[16];	//モデルのパーツ数
	int nNumModel;		//モデルのパーツ総数
	MOTION_INFO aMotionInfo[8];//モーションの最大数
	int nNumMotion;//モーションの総数
	MOTIONTYPE motionType;//モーションの種類
	MOTIONTYPE motionTypeOld;//モーションの種類
	bool bLoopMotion;//ループするかどうか
	int nNumKey;//キーの総数
	int nKey;//現在のキーNo.
	int nCntMotion;//モーションカウンター

}Motion;

//プロトタイプ宣言
void ReadScript(int nType);
void ReadModel(void);
//void CharacterSet(void);
//void ReadMotion(void);
//void ReadKey(void);
void UpdateMotion(void);
//void SetModel(void);
//void SetMotion(void);
//void SetKey(void);

#endif