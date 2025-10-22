//**************************************
//
// アイテム効果処理 [itemskill.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ITEMSKILL_H_ // このマクロ定義がされていなかったら
#define _ITEMSKILL_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// アイテム効果クラス
//********************
class CItemSkill
{
public:
	CItemSkill();			// コンストラクタ
	virtual ~CItemSkill();	// デストラクタ
	static CItemSkill* Create(int nType);	// インスタンス生成
	virtual HRESULT Init(void)=0;			// 初期化
	virtual void Uninit(void)=0;			// 終了
	virtual void Update(void)=0;			// 更新
private:
};
#endif