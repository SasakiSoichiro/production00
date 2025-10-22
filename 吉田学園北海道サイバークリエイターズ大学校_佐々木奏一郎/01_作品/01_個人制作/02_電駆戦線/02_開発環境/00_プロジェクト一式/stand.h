//**************************************
//
// スタンド処理 [stand.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _STAND_H_ // このマクロ定義がされていなかったら
#define _STAND_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// 台座クラス
//********************
class CStand :public CObjectX
{
public:
	CStand(int nPriority = 4);	// コンストラクタ
	~CStand();					// デストラクタ
	static CStand* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	D3DXVECTOR3 GetRot(void);		// 向き情報取得
private:
	int m_nIdxXFile;	// 使っているXファイルの番号
};
#endif