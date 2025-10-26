//************************************
//
// ライト処理 [light.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _LIGHT_H_//このマクロ定義がされていなかったら
#define _LIGHT_H_//二重インクルード防止のマクロ定義

//*****************
//	インクルード
//*****************
#include "main.h"

//******************
// マクロ定義
//******************
#define MAX_LIGHT (3)

//******************
// ライトクラス
//******************
class CLight
{
public:
	CLight();	// コンストラクタ
	~CLight();	// デストラクタ
	void Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];// ライト
	D3DXVECTOR3 m_aVec[MAX_LIGHT];// ベクトル
};

#endif