//**************************************
//
// 子エネミー処理 [enemychild.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYCHILD_H_ // このマクロ定義がされていなかったら
#define _ENEMYCHILD_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "enemy.h"

//********************
// 蜘蛛型の敵クラス
//********************
class CSpiderEnemy :public CEnemy
{
public:
	CSpiderEnemy();		// コンストラクタ
	~CSpiderEnemy();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	bool Chase(void);				// 追いかける条件
	bool Attack(void);				// 攻撃する条件
	bool Nuetoral(void);			// 待機する条件
	bool Hit(void);					// 攻撃条件
	bool AttackUpdate(void);		// 攻撃の更新
private:
	int m_fAttackFps;				// 攻撃する時間
	bool m_bAttackSound;			// サウンドを一回のみ鳴らす
	bool m_bAngle;					// 一周したか
	int m_nHitCool;					// 攻撃クールタイム

	static constexpr float SPEED = 1.0f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 55.0f;
};

//********************
// 扇風機型の敵クラス
//********************
class CFanmotorEnemy :public CEnemy
{
public:
	CFanmotorEnemy();	// コンストラクタ
	~CFanmotorEnemy();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	bool Chase(void);		// 追いかける条件
	bool Attack(void);		// 攻撃する条件
	bool Nuetoral(void);	// 待機する条件
	bool Hit(void);			// 攻撃条件
	bool AttackUpdate(void);// 攻撃の更新
private:
	int m_fAttackFps;		// 攻撃する時間
	bool m_bAttackSound;	// サウンドを一回のみ鳴らす
	int m_nHitCool;			// 攻撃クールタイム
	
	static constexpr float SPEED = 1.2f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 30.0f;
};
#endif