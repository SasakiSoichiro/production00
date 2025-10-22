//**************************************
//
// 充電量調節処理 [adjust.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ADJUST_H_ // このマクロ定義がされていなかったら
#define _ADJUST_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "itemskill.h"

class CAdjustUI;

//********************
// 充電量調節クラス
//********************
class CAdjust :public CItemSkill
{
public:
	CAdjust();	// コンストラクタ
	~CAdjust();	// デストラクタ
	HRESULT Init(void);			// 初期化
	void Uninit(void);			// 終了
	void Update(void);			// 更新
private:
	float m_fSum;			// 合計変化量
	CAdjustUI* m_pAdjustUI;	// UIへのポインタ
	static constexpr int thereshold = 10000;// スティックのデッドゾーン
	static constexpr float maxSum = 150.0f;	// 変化量の最大値
	static constexpr float frameLife = 0.5f;// 1フレームの変化量
	static const D3DXVECTOR3 POS_UI;		// UIの位置
};
#endif