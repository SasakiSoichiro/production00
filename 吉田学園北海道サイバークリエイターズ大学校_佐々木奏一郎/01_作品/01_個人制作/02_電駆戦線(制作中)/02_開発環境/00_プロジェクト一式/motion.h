//********************************************
//
//	モーション処理 [motion.h]
// Author:Sasaki Soichiro
//
//********************************************
#ifndef _MOTION_H_// このマクロ定義がされていなかったら
#define _MOTION_H_// 2重インクルード防止のマクロ定義

//*****************
// インクルード
//*****************
#include "main.h"
#include "model.h"

//*****************
// マクロ定義
//*****************
#define PARTS_MAX (20)
#define MAX_WORD (256)

//**************
// キーの構造体
//**************
typedef struct
{
	float fPosX;//位置
	float fPosY;
	float fPosZ;
	float fRotX;//向き
	float fRotY;
	float fRotZ;
}KEY;

//******************
// キー情報の構造体
//******************
typedef struct
{
	int nFlame;//再生フレーム
	KEY aKey[20];//パーツの最大数を入れる//キー情報

}KEY_INFO;

//***********************
//モーション情報の構造体
//***********************
typedef struct
{
	bool bLoop;//ループするかどうか
	int nNumKey;//キーの総数
	KEY_INFO aKeyInfo[30];//キーの最大数//キー情報
}MOTION_INFO;


//*******************
// モーションクラス
//*******************
class CMotion
{
public:
	CMotion();		// コンストラクタ
	~CMotion();		// デストラクタ
	static CMotion*Create(const char* pMotionScript);	// インスタンス生成
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	void SetMotion(int type);
	int GetType(void) { return m_type; };
	void ReadScript(const char* pMotionScript);
private:
	CModel* m_apModel[PARTS_MAX];	// モデルのポインタ
	int m_nNumModel;				// モデルのパーツ総数
	MOTION_INFO m_aInfo[15];		// モーションの最大数
	int m_nNum;						// モーションの総数
	int m_type;						// モーションの種類
	//TYPE m_typeOld;				// モーションの種類
	bool m_bLoop;					// ループするかどうか
	int m_nNumKey;					// キーの総数
	int m_nKey;						// 現在のキーNo.
	int m_nCnt;						// モーションカウンター
		
	bool m_bFinish;			// 現在のモーションが終了しているかどうか
	bool m_bBlend;			// ブレンドモーションがあるかどうか
	int m_typeBlend;		// モーションの種類
	int m_nNumKeyBlend;		// キーの総数
	int m_nKeyBlend;		// 現在のキーNo.
	int m_nCntBlend;		// モーションカウンター
	int m_nFrameBlend;		// ブレンドのフレーム数
	int m_nCntMotionBlend;	// モーションカウンター
};

#endif