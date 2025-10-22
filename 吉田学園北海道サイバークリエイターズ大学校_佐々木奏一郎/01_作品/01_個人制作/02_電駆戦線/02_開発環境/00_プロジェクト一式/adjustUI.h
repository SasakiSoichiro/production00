//***************************************
// 
// 充電調節UI処理 [lifeUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _ADJUSTUI_H_ // このマクロ定義がされていなかったら
#define _ADJUSTUI_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "object2DMulti.h"

//********************
// 充電量調節クラス
//********************
class CAdjustUI :public CObject2DMulti
{
public:
	CAdjustUI(int nPriority = 5);	// コンストラクタ
	~CAdjustUI();					// デストラクタ
	static CAdjustUI* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	void SetLife(float fLife) { m_fLife = fLife; }
	float GetLife(void) { return m_fLife; }
private:
	// 種類
	typedef enum
	{
		TYPE_SHAPE = 0,	// 形状のテクスチャ
		TYPE_COLOR,		// 色のテクスチャ
		TYPE_MAX
	}TYPE;
	int  m_nIdxTexture[TYPE_MAX];	// テクスチャのインデックス
	D3DXVECTOR2 m_size;				// 大きさ
	float m_fLife;					// ライフ
	static constexpr float maxLife = 150.0f;// 変化量の最大値
	static constexpr float texOffset = 0.5f;// テクスチャ座標のオフセット
	static const D3DXVECTOR3 SIZE;			// 大きさ
};

#endif