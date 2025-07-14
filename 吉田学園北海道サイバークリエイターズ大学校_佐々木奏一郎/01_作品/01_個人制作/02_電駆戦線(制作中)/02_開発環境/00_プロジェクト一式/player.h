//**************************************
//
// プレイヤー処理 [player.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _PLAYER_H_ // このマクロ定義がされていなかったら
#define _PLAYER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "motion.h"

//********************
// プレイヤークラス
//********************
class CPlayer :public CObject
{
public:
	typedef enum
	{
		STATE_NONE = 0,
		STATE_RAIL
	}STATE;
	typedef enum
	{
		MOTION_NUETORAL=0,
		MOTION_FLONT,
		MOTION_BACK,
		MOTION_LF,
		MOTION_LB,
		MOTION_RF,
		MOTION_RB,
		MOTION_FB,
		MOTION_BF,
	}MOTION;
	CPlayer(int nPriority = 4);	// コンストラクタ
	~CPlayer();					// デストラクタ
	static CPlayer* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetState(STATE state) { m_State = state; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }	
	STATE GetState(void) { return m_State; }
	static int GetLife(void) { return m_nLife; }// ライフ情報の取得
	void Posture(void);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_oldPos;
	D3DXVECTOR3 m_move;	// 向き
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_vecF;
	D3DXVECTOR3 m_vecR;
	D3DXVECTOR3 m_vecU;
	D3DXMATRIX m_mtxWorld;
	float m_fAngle;
	static int m_nLife;
	int m_nIdxXFile;
	STATE m_State;
	CMotion* m_pMotion;		// モデル(パーツ)へのポインタ
};
#endif