//***************************************
// 
// リザルトUI処理 [resultUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _TARGET_H_ // このマクロ定義がされていなかったら
#define _TARGET_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"

//************************
// リザルトUIクラス
//************************
class CTarget :public CObject2D
{
public:
	CTarget(int nPriority = 5);	// コンストラクタ
	~CTarget();					// デストラクタ
	static CTarget* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
private:
	int  m_nIdxTexture[3];			// テクスチャのインデックス
	int m_nCnt;
	int m_nType;
	static constexpr int cool = 180;
};
#endif