//**************************************
//
// エネミー状態処理 [enemyState.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYSTATE_H_ // このマクロ定義がされていなかったら
#define _ENEMYSTATE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "state.h"

class CEnemy;

//**************************************
// エネミー専用のステートの基底クラス
//**************************************
class CEnemyStateBase :public CStateBase
{
public:
	CEnemyStateBase();	// コンストラクタ
	~CEnemyStateBase();	// デストラクタ
	void SetOwner(CEnemy* pEnemy);// ポインタの設定
protected:
	CEnemy* m_pEnemy;// エネミーへのポインタ
};

//****************
// 待機状態
//****************
class CNuetoralState :public CEnemyStateBase
{
public:
	CNuetoralState();// コンストラクタ
	~CNuetoralState();// デストラクタ
	void Init(void);// 初期化
	void Update(void);// 更新
	void Uninit(void);// 終了
};

//******************
// 追従状態
//******************
class CChaseState :public CEnemyStateBase
{
public:
	CChaseState();		// コンストラクタ
	~CChaseState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
};

//******************
// 攻撃状態
//******************
class CAttackState :public CEnemyStateBase
{
public:
	CAttackState();		// コンストラクタ
	~CAttackState();	// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
};

//******************
// やられ状態
//******************
class CHitState :public CEnemyStateBase
{
public:
	CHitState();		// コンストラクタ
	~CHitState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
};

//******************
// 死んだ状態
//******************
class CDownState :public CEnemyStateBase
{
public:
	CDownState();		// コンストラクタ
	~CDownState();		// デストラクタ
	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Uninit(void);	// 終了
private:
};


#endif