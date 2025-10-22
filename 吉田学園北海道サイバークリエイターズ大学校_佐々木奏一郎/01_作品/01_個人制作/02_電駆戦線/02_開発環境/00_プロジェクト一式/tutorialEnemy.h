//**************************************
//
// エネミー処理 [enemy.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _TUTORIALENEMY_H_ // このマクロ定義がされていなかったら
#define _TUTORIALENEMY_H_ // 二重インクルード防止のマクロ定義

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
class CTutorialEnemy :public CObject
{
public:
	CTutorialEnemy(int nPriority = 4);				// コンストラクタ
	~CTutorialEnemy();								// デストラクタ
	static CTutorialEnemy* Create(D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetLife(int nLife) { m_nLife = nLife; }		// ライフの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// 位置情報の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// 向き情報の取得
	CMotion* GetMotion(void) { return m_pMotion; }		// モーション情報の取得
	CModel* GetModel(int nIdx) { return m_apModel[nIdx]; }// モデル情報の取得
	int GetLife(void) { return m_nLife; }				// ライフ情報の取得
	static int GetNumAll(void) { return m_nNumAll; }	// 現在の総数の取得
	void LoadMotion(const char* pMotionScript);			// モーションテキストを読み込む
	void SetMotion(int nType) { m_pMotion->SetMotion(nType); }// モーションの設定
	static void EnemyUpdate(void);
private:
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_oldPos;	// 前フレームの位置
	D3DXVECTOR3 m_move;		// 動く方向
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_fAngle;			// 向き
	int m_nLife;			// ライフ
	int m_nIdxXFile;		// 使うモデルの番号
	CMotion* m_pMotion;		// モーションへのポインタ
	CModel* m_apModel[15];	// モデル(パーツ)へのポインタ
	int m_nNumModel;		// 使っているモデル数
	int m_nHitCool;
	static int m_nNumAll;	// 現在の総数
	CEnemyLifeManager* m_pLifeManager;// ライフのマネージャー
	static constexpr int initLife = 4;// 体力の初期化
	static constexpr float SPEED = 1.0f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 55.0f;

};

#endif