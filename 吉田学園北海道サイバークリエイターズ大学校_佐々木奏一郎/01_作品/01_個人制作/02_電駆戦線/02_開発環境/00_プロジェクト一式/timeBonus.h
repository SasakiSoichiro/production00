//***************************************
// 
// タイムボーナス処理 [timeBonus.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _TIMEBONUS_H_ // このマクロ定義がされていなかったら
#define _TIMEBONUS_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "bonus.h"

class CNumber;

//************************
// ボーナスクラス
//************************
class CTimeBonus :public CBonus
{
public:
	CTimeBonus(int nPriority = 5);	// コンストラクタ
	~CTimeBonus();					// デストラクタ
	static CTimeBonus* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	void SetTime(int nTime) { m_nTime = nTime; }// 時間の設定
private:
	CNumber* m_pNumber[5];	// ナンバーへのポインタ
	static int m_nTime;		// 時間
};
#endif