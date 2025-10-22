//**************************************
//
// エネミー処理 [enemy.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMY_H_ // このマクロ定義がされていなかったら
#define _ENEMY_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"
#include "motion.h"
#include "enemyState.h"
#include "state.h"

class CEnemyLifeManager;

//********************
// エネミークラス
//********************
class CEnemy :public CObject
{
public:
	// 敵の種類
	typedef enum
	{
		TYPE_SPIDER=0,	// 蜘蛛型
		TYPE_FANMOTOR,	// 扇風機型
		TYPE_CRAWLER,	// クローラー型
		TYPE_MAX
	}TYPE;

	// 状態
	typedef enum
	{
		STATE_NONE=0,	// 何もなし
		STATE_MAX
	}STATE;

	// モーション
	typedef enum
	{
		MOTION_NUETORAL = 0,// 通常状態
		MOTION_MOVE,		// 動いている状態
		MOTION_ACTION1,		// 攻撃状態1
		MOTION_ACTION2,		// 攻撃状態2
		MOTION_DIE,			// 死ぬ状態
		MOTION_MAX
	}MOTION;

	CEnemy(int nPriority = 4);				// コンストラクタ
	~CEnemy();								// デストラクタ
	static CEnemy* Create(D3DXVECTOR3 pos,int nType);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetSpeed(float speed) { m_speed = speed; }		// 速度
	void SetState(STATE state) { m_State = state; }		// 状態の設定
	void SetLife(int nLife) { m_nLife = nLife; }		// ライフの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// 位置情報の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// 向き情報の取得
	float GetSpeed(void) { return m_speed; }			// 速度情報の取得
	STATE GetState(void) { return m_State; }			// 状態情報の取得
	CMotion*GetMotion(void) { return m_pMotion; }		// モーション情報の取得
	CModel* GetModel(int nIdx) { return m_apModel[nIdx]; }// モデル情報の取得
	int GetLife(void) { return m_nLife; }				// ライフ情報の取得
	static int GetNumAll(void) { return m_nNumAll; }	// 現在の総数の取得
	void LoadMotion(const char* pMotionScript);			// モーションテキストを読み込む
	void ChangeState(CEnemyStateBase* pState);			// 状態を入れ替える
	void SetMotion(int nType) { m_pMotion->SetMotion(nType); }// モーションの設定
	bool Distance(float fDistance);// プレイヤーとの距離
	virtual bool Chase(void) = 0;		// チェイス状態への条件
	virtual bool Attack(void) = 0;		// 攻撃状態への条件
	virtual bool Nuetoral(void) = 0;	// 通常状態への条件
	virtual bool Hit(void) = 0;			// やられ状態への条件
	virtual bool AttackUpdate(void) = 0;// 攻撃の更新への条件
private:
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_oldPos;	// 前フレームの位置
	D3DXVECTOR3 m_move;		// 動く方向
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_vecF;		// 前ベクトル
	D3DXVECTOR3 m_vecR;		// 右ベクトル
	D3DXVECTOR3 m_vecU;		// 上ベクトル
	float m_speed;			// 速度
	float m_fAngle;			// 向き
	int m_nLife;			// ライフ
	int m_nIdxXFile;		// 使うモデルの番号
	STATE m_State;			// 状態
	CMotion* m_pMotion;		// モーションへのポインタ
	CModel* m_apModel[15];	// モデル(パーツ)へのポインタ
	int m_nNumModel;		// 使っているモデル数
	CStateMachine* m_Machine;// ステートマシンへのポインタ
	static int m_nNumAll;	// 現在の総数
	int m_nType;			// 種類
	CEnemyLifeManager* m_pLifeManager;// ライフのマネージャー
	static constexpr int initLife = 4;// 体力の初期化
};

#endif