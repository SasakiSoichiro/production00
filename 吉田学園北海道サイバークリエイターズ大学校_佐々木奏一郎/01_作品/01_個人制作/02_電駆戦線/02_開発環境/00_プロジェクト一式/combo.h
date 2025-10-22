//***************************************
// 
// コンボ処理 [combo.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _COMBO_H_ // このマクロ定義がされていなかったら
#define _COMBO_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "object2D.h"

class CNumberMulti;

//************************
// コンボクラス
//************************
class CCombo :public CObject
{
public:
	CCombo(int nPriority = 5);	// コンストラクタ
	~CCombo();					// デストラクタ
	static CCombo* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	int Digit(int nScore);			// 桁を返す
	static void Add(int nScore);	// コンボ加算
	static int GetCombo(void) { return m_nCurrent; }// 現在のコンボ数情報取得
private:
	void Set(void);					// マルチテクスチャの設定
	void Reset(void);				// コンボが途切れた時の設定
	static CNumberMulti* m_pNumberMulti[2];	// ナンバーへのポインタ
	static int m_nCurrent;					// 現在のコンボ数
	static int m_nTime;						// 継続時間
	static int m_nScore;					// 現在のスコア
	static constexpr int maxTime = 1400;	// 最大時間
	static constexpr float offsetX = 35.0f;	// オフセット
	static const D3DXCOLOR COMBO_ON;		// コンボ時の色
	static const D3DXCOLOR COMBO_OFF;		// コンボしてないときの色
};
#endif