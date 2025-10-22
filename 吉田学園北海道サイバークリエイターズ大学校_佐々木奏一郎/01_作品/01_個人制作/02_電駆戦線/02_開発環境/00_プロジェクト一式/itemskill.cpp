//*****************************************
//
// アイテム効果処理 [itemskill.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "itemskill.h"
#include "item.h"
#include "adjust.h"

//*****************
// コンストラクタ
//*****************
CItemSkill::CItemSkill() 
{
}

//*****************
// デストラクタ
//*****************
CItemSkill::~CItemSkill()
{
}

//******************
// インスタンス生成
//*******************
CItemSkill* CItemSkill::Create(int nType)
{
	CItemSkill* pItemSkill;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合
		switch (nType)
		{
		case CItem::ITEM_ADJUST:
			// インスタンス生成
			pItemSkill = new CAdjust;
			// 初期化
			pItemSkill->Init();		
			return pItemSkill;
			break;
		}
	}

	return NULL;
}
