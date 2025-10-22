//**********************************
//
// ポーズ処理 [pause.h]
// Author:Sasaki Soichiro
//
//**********************************
#ifndef _PAUSE_H_ // このマクロ定義がされていなかったら
#define _PAUSE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"
#include "state.h"

//*********************
// マクロ定義
//*********************
#define MAX_SELECT (4)

class CPauseStateBase;

//********************
// ポーズクラス
//********************
class CPause:public CObject2D
{
public:
	typedef enum
	{
		TYPE_BACKGAME=0,
		TYPE_STARTGAME,
		TYPE_BACKTITLE,
		TYPE_REVERSE,
		TYPE_MAX
	}TYPE;
	CPause(int nPriority = 7);	// コンストラクタ
	~CPause();					// デストラクタ
	static CPause* Create(D3DXVECTOR3 pos,int nType);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	D3DXVECTOR2 GetSize(void);		// 大きさ情報取得
	void AnimSize(void);			// ポーズ中のアニメーション
	static bool GetPause(void) { return m_bPause; }			// ポーズ情報の取得
	static void SwitchPause(void) { m_bPause = !m_bPause; }	// ポーズ切り替え
	static int GetSelect(void) { return m_nSelect; }		// 選択
	static void SetSelect(int nSelect) { m_nSelect = nSelect; }	// 選択の設定

private:
	int  m_nIdxTexture;			// テクスチャのインデックス
	float m_nAnim;				// アニメーション用カウント
	static bool m_bPause;		// ポーズ切替用
	CObject2D* m_apObject2D[MAX_SELECT];	// CObject2Dへのポインタ
	static int m_nSelect;
};

//**********************
// ゲームに戻る
//**********************
class CBackGame :public CPause
{
public:
	CBackGame();
	~CBackGame();
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
};

//**********************
// 始めから
//**********************
class CStartGame :public CPause
{
public:

	CStartGame();
	~CStartGame();
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
};

//**********************
// タイトルに戻る
//**********************
class CBackTitle :public CPause
{
public:

	CBackTitle();
	~CBackTitle();
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
};

//**********************
// 操作方法
//**********************
class CReverse :public CPause
{
public:
	CReverse();
	~CReverse();
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
};




#endif