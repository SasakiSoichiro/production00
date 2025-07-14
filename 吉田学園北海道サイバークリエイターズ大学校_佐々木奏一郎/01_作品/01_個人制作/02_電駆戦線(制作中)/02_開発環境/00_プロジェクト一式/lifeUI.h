//***************************************
// 
// ライフUI処理 [lifeUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _LIFEUI_H_ // このマクロ定義がされていなかったら
#define _LIFEUI_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "number.h"
#include "object2DMulti.h"

//********************
// ライフクラス
//********************
class CLifeUI :public CObject2DMulti
{
public:
	CLifeUI(int nPriority = 5);	// コンストラクタ
	~CLifeUI();					// デストラクタ
	static CLifeUI* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	void SetLife(float fLife) { m_fLife = fLife; }		// ライフの設定
	int Digit(int nScore);
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
private:
	int  m_nIdxTexture[4];			// テクスチャのインデックス
	static CNumber* m_apNumber[3];	// ナンバーへのポインタ
	static CSymbol* m_pSymbol;		// パーセントへのポインタ
	D3DXVECTOR2 m_size;				// 大きさ
	float m_fLife;					// ライフ
	int m_nDigit;					// 現在の桁
};

#endif