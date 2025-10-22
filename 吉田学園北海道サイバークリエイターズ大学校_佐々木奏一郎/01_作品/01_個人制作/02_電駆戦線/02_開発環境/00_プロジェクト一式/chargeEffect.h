//=============================================================================
//
// 充電エフェクト処理 [chargeEffect.h]
// Author Sasaki Soichiro
//
//=============================================================================
#ifndef _CHARGEEFFECT_H_// このマクロ定義がされていなかったら
#define _CHARGEEFFECT_H_// 2重インクルード防止のマクロ定義
//*******************
// インクルード
//*******************
#include "main.h"
#include "effect.h"

//**********************
// 充電エフェクトクラス
//**********************
class CChargeEffect :public CEffect
{
public:
	CChargeEffect(int nPriority = 4);	// コンストラクタ
	~CChargeEffect();					// デストラクタ
	static CChargeEffect* Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
private:
	static constexpr float dest = 0.01f;	// 遅延
	static constexpr float offsetY = 20.0f;	// オフセット
	static constexpr float speed = 4.0f;	// スピード
};
#endif