//************************************
//
// チュートリアル処理 [tutorial.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _TUTORIAL_H_ // このマクロ定義がされていなかったら
#define _TUTORIAL_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "scene.h"
#include "state.h"

class CTutorialCheck;
class CTutorialStateBase;
class CMesh;
class CBlockManager;
class CTutorialPlayer;
class CTutorialRail;

//**********************
// チュートリアルクラス
//**********************
class CTutorial :public CScene
{
public:
	typedef enum
	{
		STATE_FLONTBACK=0,
		STATE_RIGHTLEFT,
		STATE_ROLL,
		STATE_JUMP,
		STATE_JUMPCANCEL,
		STATE_RAIL,
		STATE_ATTACK,
		STATE_FREE,
		STATE_MAX,
	}STATE;
	CTutorial();	// コンストラクタ
	~CTutorial();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化
	void Uninit(void);					// 終了
	void Update(void);					// 更新
	void Draw(void);					// 描画
	void SetPos(D3DXVECTOR3 pos) {};	// 位置
	void SetRot(D3DXVECTOR3 rot) {};	// 向き
	D3DXVECTOR3 GetPos(void) { return NONE; }	// 位置情報
	void TaskClear(void);				// クリア
	void ChangeState(CTutorialStateBase* pState);
	static CMesh*GetCMesh(void) { return m_pMesh; }
	static CBlockManager* GetCBlockManager(void) { return m_pBlockManager; }
	static CTutorialPlayer* GetCPlayer(void) { return m_pPlayer; }


private:
	STATE m_State;				// 状態
	CStateMachine* m_Machine;	// ステートマシンへのポインタ
	CTutorialCheck* m_pTutorialCheck;
	static CMesh* m_pMesh;					// メッシュへのポインタ
	static CBlockManager* m_pBlockManager;	// ブロックマネージャーへのポインタ
	static CTutorialPlayer* m_pPlayer;		// ブロックマネージャーへのポインタ
	static CTutorialRail* m_pRail;			// レールへのポインタ
};

//******************************************
// チュートリアル専用のステートの基底クラス
//******************************************
class CTutorialStateBase :public CStateBase
{
public:
	CTutorialStateBase();				// コンストラクタ
	~CTutorialStateBase();				// デストラクタ
	void SetOwner(CTutorial* pTutorial);// チュートリアルのポインタ設定
protected:
	CTutorial* m_pTutorial;				// チュートリアルへのポインタ
};

//****************
// 前後の操作
//****************
class CFlontBackState :public CTutorialStateBase
{
public:
	CFlontBackState();		// コンストラクタ
	~CFlontBackState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 180;
	
};

//****************
// 左右の操作
//****************
class CRightLeftState :public CTutorialStateBase
{
public:
	CRightLeftState();		// コンストラクタ
	~CRightLeftState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 60;
};

//****************
// 回転の操作
//****************
class CRollState :public CTutorialStateBase
{
public:
	CRollState();		// コンストラクタ
	~CRollState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 60;
};


//****************
// ジャンプの操作
//****************
class CJumpCState :public CTutorialStateBase
{
public:
	CJumpCState();		// コンストラクタ
	~CJumpCState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 1;
};

//****************
// ジャンプの操作
//****************
class CJumpCancelState :public CTutorialStateBase
{
public:
	CJumpCancelState();		// コンストラクタ
	~CJumpCancelState();	// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 1;
};

//********************
// レールに乗るの操作
//********************
class CRailCState :public CTutorialStateBase
{
public:
	CRailCState();		// コンストラクタ
	~CRailCState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
};

//********************
// アタック操作
//********************
class CAttackCState :public CTutorialStateBase
{
public:
	CAttackCState();		// コンストラクタ
	~CAttackCState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 180;
};

//********************
// フリー操作
//********************
class CFreeState :public CTutorialStateBase
{
public:
	CFreeState();		// コンストラクタ
	~CFreeState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
	int m_nCnt;
	bool m_nClear;
};





#endif