//******************************************
//
// タイマー処理 [timer.h]
// AuthorSasaki Soichiro
//
//******************************************
#ifndef _TIMER_H_ // このマクロ定義がされていなかったら
#define _TIMER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "number.h"

//********************
// タイマークラス
//********************
class CTimer :public CObject
{
public:
	CTimer(int nPriority = 5);	// コンストラクタ
	~CTimer();					// デストラクタ
	static CTimer* Create(D3DXVECTOR3 pos,int nTime);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);// 位置の設定
	void SetRot(D3DXVECTOR3 rot);// 向きの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置の設定
	D3DXVECTOR2 GetSize(void) { return m_size; };	// 大きさの設定
	static void SetTime(int nTime);				// タイマーの設定
	static void Add(int nTime);					// タイム加算
	static int GetTime(void) { return m_nTime; }// タイム情報の取得

private:
	int  m_nIdxTexture[2];		// テクスチャのインデックス
	static CNumber* m_apMin[2];	// ナンバーへのポインタ
	static CNumber* m_apSec[2];	// ナンバーへのポインタ
	static CSymbol* m_pSymbol;	// コロンへのポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR2 m_size;	// 大きさ
	static int m_nTime;	// タイム
	static int m_nFps;	// FPSカウント
};
#endif