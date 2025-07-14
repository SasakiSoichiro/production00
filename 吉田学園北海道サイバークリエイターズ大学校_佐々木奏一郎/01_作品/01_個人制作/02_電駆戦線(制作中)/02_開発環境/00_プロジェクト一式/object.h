//***************************************
//
// オブジェクト処理 [object.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _OBJECT_H_ // このマクロ定義がされていなかったら
#define _OBJECT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

//******************
// マクロ定義
//******************
#define MAX_OBJ (512)	// 描画順ごとのオブジェクトの最大数
#define MAX_PRI (8)		// 描画順の最大数

//********************
// オブジェクトクラス
//********************
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何もなし
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,		// 敵
		TYPE_EBULLET,	// 敵の弾
		TYPE_PBULLET,	// プレイヤーの弾
		TYPE_BG,		// 背景
		TYPE_MAX
	}TYPE;
	CObject(int nPriority=3);			// コンストラクタ
	virtual ~CObject();					// デストラクタ
	virtual HRESULT Init(D3DXVECTOR3 pos)=0;	// 初期化(純粋仮想関数)
	virtual void Uninit(void)=0;				// 終了(純粋仮想関数)
	virtual void Update(void)=0;				// 更新(純粋仮想関数)
	virtual void Draw(void)=0;					// 描画(純粋仮想関数)
	virtual void SetPos(D3DXVECTOR3 pos) = 0;	// 位置(純粋仮想関数)
	virtual void SetRot(D3DXVECTOR3 rot) = 0;	// 向き(純粋仮想関数)
	virtual D3DXVECTOR3 GetPos(void) = 0;		// 位置情報(純粋仮想関数)
	static void ReleaseAll(void);			// 全てのオブジェクト終了
	static void UpdateAll(void);			// 全てのオブジェクト更新
	static void DrawAll(void);				// 全てのオブジェクト描画
	void SetType(TYPE type);				// 種類設定
	TYPE GetType(void) { return m_type; }	// 種類の情報取得
	static CObject* GetObject(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; }	// オブジェクト情報取得
	static int GetNumAll(void) { return m_nNumAll; }											// 現在のオブジェクト数情報取得
	static int GetNumPriority(int nPriority) { return m_nNumPriority[nPriority]; }				// 描画順ごとのオブジェクト数情報取得
protected:
	void Release(void);// 1つの終了
private:
	static CObject* m_apObject[MAX_PRI][MAX_OBJ];	// オブジェクトのポインタ
	static int m_nNumAll;							// オブジェクトの総数
	static int m_nNumPriority[MAX_PRI];				// 描画順ごとの総数
	int m_nID;			// 自分自身のID
	TYPE m_type;		// 種類
	int m_nPriority;	// 優先順位の位置
};	
#endif