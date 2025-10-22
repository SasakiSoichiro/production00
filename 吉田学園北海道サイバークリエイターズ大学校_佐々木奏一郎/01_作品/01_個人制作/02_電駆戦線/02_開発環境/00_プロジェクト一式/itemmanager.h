//***************************************
// 
// アイテムマネージャー処理 [itemmanager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _ITEMMANAGER_H_ // このマクロ定義がされていなかったら
#define _ITEMMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

class CItemSkill;

//*****************************
// アイテムマネージャークラス
//*****************************
class CItemManager
{
public:
	CItemManager();	// コンストラクタ
	~CItemManager();// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void SetItem(CItemSkill* pItemSkill) { m_pItemSkill = pItemSkill; }
private:
	CItemSkill* m_pItemSkill;
};
#endif