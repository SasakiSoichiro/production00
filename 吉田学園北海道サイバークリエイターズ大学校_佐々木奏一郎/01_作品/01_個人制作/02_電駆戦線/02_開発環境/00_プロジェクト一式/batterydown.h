//***************************************
// 
// バッテリー低下UI処理 [batterydown.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _BATTERYDOWN_H_ // このマクロ定義がされていなかったら
#define _BATTERYDOWN_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"

//************************
// バッテリー低下UIクラス
//************************
class CBatteryDown :public CObject2D
{
public:
	CBatteryDown(int nPriority = 5);	// コンストラクタ
	~CBatteryDown();					// デストラクタ
	static CBatteryDown* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
private:
	int  m_nIdxTexture;		// テクスチャのインデックス
	static constexpr float line = 20.0f;// 表示する体力のライン
	static const D3DXVECTOR2 SIZE;		// 大きさ
};
#endif