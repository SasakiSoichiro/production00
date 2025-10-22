//***************************************
// 
// スロー処理 [slow.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _SLOW_H_ // このマクロ定義がされていなかったら
#define _SLOW_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

//************************
// スロー管理クラス
//************************
class CSlow
{
public:
	CSlow();	// コンストラクタ
	~CSlow();	// デストラクタ
	HRESULT Init(void);			// 初期化
	void Uninit(void);			// 終了
	void Update(void);			// 更新
	static void Set(int nTime);	// 時間の設定
	float GetfMulti(void) { return m_fMulti; }	// 掛ける値情報取得
	int GetnMulti(void) { return m_nMulti; }	// 掛ける値情報取得
	float GetfDivi(void) { return m_fDivi; }	// 割る値情報取得
	int GetnDivi(void) { return m_nDivi; }		// 割る値情報取得
private:
	static float m_fMulti;	// 掛ける値
	static float m_fDivi;	// 割る値
	static int m_nMulti;	// 掛ける値
	static int m_nDivi;		// 割る値
	static int m_nTime;		// 時間
};
#endif