//***************************************
// 
// 障害物マネージャー処理 [snagManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _SNAGMANAGER_H_ // このマクロ定義がされていなかったら
#define _SNAGMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

//************************
// 障害物マネージャークラス
//************************
class CSnagManager
{
public:
	CSnagManager();	// コンストラクタ
	~CSnagManager();// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:
	int m_nFenceTime;	// 柵の出現時間
	int m_nJemTime;		// 宝石の出現時間
	static constexpr int FenceCool = 1600;	// クールタイム
	static constexpr int JemCool = 500;		// クールタイム
};
#endif