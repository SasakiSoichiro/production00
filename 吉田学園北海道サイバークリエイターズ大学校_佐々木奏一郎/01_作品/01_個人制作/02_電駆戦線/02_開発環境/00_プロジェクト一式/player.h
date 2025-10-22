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
#include "state.h"


class CPlayerStateBase;
class COrbit;
class CLifeUI;
class CShadowS;
class CMotion;
class CModel;
class CItemManager;

//********************
// プレイヤークラス
//********************
class CPlayer :public CObject
{
public:
	// 状態
	typedef enum
	{
		STATE_NONE = 0,		// 何もなし
		STATE_JUMP,			// ジャンプ
		STATE_RAIL,			// レール
		STATE_RAILCHANGE,	// レール乗り換え
		STATE_LANDING,		// 着地
		STATE_INOPERABLE,	// 操作不能状態
	}STATE;

	// モーション
	typedef enum
	{
		MOTION_NUETORAL=0,	// 通常
		MOTION_FLONT,		// 前
		MOTION_BACK,		// 後ろ
		MOTION_LF,			// 左前
		MOTION_LB,			// 左後ろ
		MOTION_RF,			// 右前
		MOTION_RB,			// 右後ろ
		MOTION_FB,			// 左回転
		MOTION_BF,			// 右回転
		MOTION_DIE,			// 死
		MOTION_RAILL,		// レール時のモーション(左)
		MOTION_RAILR,		// レール時のモーション(右)
		MOTION_RAILJUMP,	// レール時のジャンプ
		MOTION_JUMP,		// レール時のジャンプ
		MOTION_ELECJUMP		// 強化時のジャンプ
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
	void SetMove(D3DXVECTOR3 move);	// 速度
	void SetState(STATE state) { m_State = state; }		// 状態の設定
	void SetLife(float fLife) { m_fLife = fLife; }		// ライフの設定
	void SetAngle(float fAngle) { m_fAngle = fAngle; }	// 向きの設定
	void SetStan(int nStan) { m_nStanTime = nStan; }	// スタンする時間の設定
	void SetElec(bool bElec) { m_bElec = bElec; }		// 強化状態の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// 位置情報取得
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }	// 前フレームの位置情報取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// 向き情報取得
	D3DXVECTOR3 GetMove(void) { return m_move; }		// 動き情報取得
	D3DXVECTOR3 GetVecU(void) { return m_vecU; }		// 上ベクトル情報取得
	STATE GetState(void) { return m_State; }			// 状態情報取得
	CMotion*GetMotion(void) { return m_pMotion; }		// モーションのポインタ取得
	CItemManager* GetItemManager(void) { return m_pItemManager; }// モーションのポインタ取得
	static float GetLife(void) { return m_fLife; }		// ライフ情報の取得
	float GetAngle(void) { return m_fAngle; }			// 向き情報取得
	int GetStan(void) { return m_nStanTime; }			// スタン時間情報取得
	int GetStanCnt(void) { return m_nStanCnt; }			// スタンカウント情報取得
	bool GetReverse(void) { return m_bReverse; }		// 操作反転情報取得
	bool GetElec(void) { return m_bElec; }				// 強化情報取得
	float GetSpeed(void) { return m_fSpeed; }			// 速さ情報取得
	void Posture(void);									// 姿勢制御
	void JumpPosture(void);								// ジャンプ中姿勢制御
	void LoadMotion(const char* pMotionScript);			// モーションの読み込み
	void AngleVelocity(float speed,float omega);		// 進む方向の制御
	void Decay(void);									// 徐々に止まらせる
	void SpeedUp(void);									// 徐々に加速する
	void SpeedDown(void);									// 徐々に加速する
	void ChangeState(CPlayerStateBase*pState);			// 状態を変える
	void SetBoostTime(int nBoost) { m_nBoostTime = nBoost; }// ブースト時間設定
	int GetBoostTime(void) { return m_nBoostTime; }		// ブースト時間情報取得
	void PutOutRail(void);								// レールを出す
	void AddStanCnt(void) { m_nStanCnt++; }				// スタン時間を追加
	void SetATK(int nATK) { m_nATK = nATK; }			// 攻撃力設定
	int GetATK(void);									// 攻撃力情報取得
	void SwitchReverse(void) { m_bReverse = !m_bReverse; }// 操作反転切替
private:
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_oldPos;	// 前フレームの位置
	D3DXVECTOR3 m_move;		// 動く
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	D3DXVECTOR3 m_vecF;		// 前ベクトル
	D3DXVECTOR3 m_vecR;		// 右ベクトル
	D3DXVECTOR3 m_vecU;		// 上ベクトル
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_fAngle;			// 向き
	static float m_fLife;	// ライフ
	int m_nIdxXFile;		// 使うXファイルの番号
	STATE m_State;			// 状態
	CMotion* m_pMotion;		// モーションへのポインタ
	CModel* m_apModel[18];	// パーツへのポインタ
	int m_nNumModel;		// パーツ数
	CStateMachine*m_Machine;// ステートマシンへのポインタ
	CShadowS* m_pShadow;	// 影のポインタ
	CLifeUI* m_pLifeUI;		// ライフUIへのポインタ
	COrbit* m_pOrbit[2];	// 軌跡へのポインタ
	CItemManager* m_pItemManager;// アイテムマネージャーへのポインタ
	int m_nBoostTime;		// ブースト時間
	int m_nStanTime;		// スタン時間
	int m_nStanCnt;			// スタンカウント
	float m_fSpeed;			// 現在の速度
	int m_nATK;				// 攻撃力
	bool m_bReverse;		// 操作反転
	bool m_bElec;			// 強化中
	static constexpr float Acceleration = 0.08f;// 加速度
};

//**************************************
// プレイヤー専用のステートの基底クラス
//**************************************
class CPlayerStateBase :public CStateBase
{
public:
	CPlayerStateBase();				// コンストラクタ
	~CPlayerStateBase();			// デストラクタ
	void SetOwner(CPlayer* pPlayer);// プレイヤーのポインタ設定
protected:
	CPlayer* m_pPlayer;				// プレイヤーへのポインタ
};

//****************
// 地面にいるとき
//****************
class CRandState :public CPlayerStateBase
{
public:
	CRandState();		// コンストラクタ
	~CRandState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
	void Controll(void);// 操作
private:
	static constexpr float backSpeed = 0.3f;// 加速度
};

//****************
// 空中にいるとき
//****************
class CJumpState :public CPlayerStateBase
{
public:
	CJumpState();		// コンストラクタ
	~CJumpState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
	void Rotation(void);// 回転で充電
	void Controll(void);// 操作
private:
	float m_fAngleSum;	// 回転した合計
	float m_fAngle;		// 向き
};


//******************
// レールにいるとき
//******************
class CRailState :public CPlayerStateBase
{
public:
	CRailState();		// コンストラクタ
	~CRailState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
};


//************************
// レールチェンジするとき
//************************
class CRailChangeState :public CPlayerStateBase
{
public:
	CRailChangeState();		// コンストラクタ
	~CRailChangeState();	// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
};

//************************
// 着地するとき
//************************
class CLandingState :public CPlayerStateBase
{
public:
	CLandingState();	// コンストラクタ
	~CLandingState();	// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;			// 着地のカウント
	int m_nDirectionType;// 進む方向
	static constexpr float speedDivision = 2.0f;	// 回転半径 
	static constexpr float omegaRadius = 200.0f;	// 回転半径 
	static constexpr float  maxSpeed= -10.0f;	// 最大スピード
	static constexpr float  minSpeed= -3.0f;	// 最小スピード
};

//*********************
// 操作不能のとき
//*********************
class CInoperableState :public CPlayerStateBase
{
public:
	CInoperableState();		// コンストラクタ
	~CInoperableState();	// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;		// 時間カウント
	static constexpr int Cool = 30;// 操作不能解除までの時間
};


//******************
// 死んだいるとき
//******************
class CDieState :public CPlayerStateBase
{
public:
	CDieState();		// コンストラクタ
	~CDieState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
};

#endif