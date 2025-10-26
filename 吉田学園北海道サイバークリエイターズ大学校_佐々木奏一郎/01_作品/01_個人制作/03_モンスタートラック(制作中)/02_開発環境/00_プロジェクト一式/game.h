//************************************
//
// ゲームシーン処理 [game.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _GAME_H_ // このマクロ定義がされていなかったら
#define _GAME_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "scene.h"


class CBlockManager;
class CObject3D;			// object3Dへのポインタ
class CMesh;				// メッシュへのポインタ
class CPlayer;				// プレイヤーへのポインタ
class CWave;				// ウェーブへのポインタ
class CSlow;				// スローへのポインタ
class CSnagManager;			// 障害物マネージャーへのポインタ
class CPauseManager;		// ポーズマネージャーへのポインタ
class CRailManager;			// レールマネージャーへのポインタ


//********************
// ゲームシーンクラス
//********************
class CGame:public CScene
{
public:
	// 状態
	typedef enum
	{
		STATE_NONE=0,	// 何もなし
		STATE_NORMAL,	// 通常
		STATE_END,		// 終了
		STATE_MAX
	}STATE;
	CGame();		// コンストラクタ
	~CGame();		// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化
	void Uninit(void);					// 終了
	void Update(void);					// 更新
	void Draw(void);					// 描画
	void SetPos(D3DXVECTOR3 pos) {};	// 位置
	void SetRot(D3DXVECTOR3 rot) {};	// 向き
	D3DXVECTOR3 GetPos(void) { return NONE; }								// 位置情報取得
	static CObject3D* GetCObject3D(void) { return m_pObject3D; }			// 情報取得
	static CMesh* GetCMesh(void) { return m_pMesh; }						// 情報取得
	static CPlayer* GetCPlayer(void) { return m_pPlayer; }					// 情報取得
	static CSlow* GetCSlow(void) { return m_pSlow; }						// 情報取得
	static CBlockManager* GetCBlockManager(void) { return m_pBlockManager; }// 情報取得
	static CSnagManager* GetCSnagManager(void) { return m_pSnagManager; }	// 情報取得
	static void SetState(STATE state) { m_State = state; }					// 状態設定
	static STATE GetState(void) { return m_State; }							// 状態情報取得
private:
	static CObject3D* m_pObject3D;			// object3Dへのポインタ
	static CMesh* m_pMesh;					// メッシュへのポインタ
	static CPlayer* m_pPlayer;				// プレイヤーへのポインタ
	static CWave* m_pWave;					// ウェーブへのポインタ
	static CSlow* m_pSlow;					// スローへのポインタ
	static STATE m_State;					// 状態へのポインタ
	static CBlockManager* m_pBlockManager;	// ブロックマネージャへのポインタ
	static CSnagManager* m_pSnagManager;	// 障害物マネージャーへのポインタ
	static CPauseManager* m_pPauseManager;	// ポーズマネージャへのポインタ
	static CRailManager* m_pRailManager;	// ポーズマネージャへのポインタ
	int m_nCnt;
	D3DXVECTOR3 m_pos;
};
#endif