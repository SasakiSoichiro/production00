//***************************************
// 
// レールマネージャー処理 [railManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _RAILMANAGER_H_ // このマクロ定義がされていなかったら
#define _RAILMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

class CRail;

//**************************
// レールマネージャークラス
//**************************
class CRailManager
{
public:
	CRailManager();	// コンストラクタ
	~CRailManager();	// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:
	static CRail* m_pRail[2];	// レールへのポインタ
};
#endif