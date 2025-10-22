//***************************************
// 
// ボーナス処理 [bonus.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _BONUS_H_ // このマクロ定義がされていなかったら
#define _BONUS_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"

//************************
// ボーナスクラス
//************************
class CBonus :public CObject2D
{
public:
	CBonus(int nPriority = 5);	// コンストラクタ
	~CBonus();					// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	void SetSize(D3DXVECTOR2 size);	// 大きさの設定
	void SetTexture(const char* pFileName);// 使うテクスチャの設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
private:
	int  m_nIdxTexture;			// テクスチャのインデックス
};
#endif