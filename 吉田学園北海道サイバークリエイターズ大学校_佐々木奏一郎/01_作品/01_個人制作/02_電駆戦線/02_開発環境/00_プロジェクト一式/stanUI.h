//***************************************
// 
// スタンUI処理 [titleUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _STANUI_H_ // このマクロ定義がされていなかったら
#define _STANUI_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"

//************************
// スタンUIクラス
//************************
class CStanUI :public CObject2D
{
public:
	CStanUI(int nPriority = 5);	// コンストラクタ
	~CStanUI();					// デストラクタ
	static CStanUI* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
private:
	int  m_nIdxTexture;			// テクスチャのインデックス
};
#endif