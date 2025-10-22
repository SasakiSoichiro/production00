//*******************************************
//
// タイトルのセグウェイ処理 [titleSegway.h]
// Author:Sasaki Soichiro
//
//*******************************************
#ifndef _TITLESEGWAY_H_ // このマクロ定義がされていなかったら
#define _TITLESEGWAY_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// プレイヤークラス
//********************
class CTitleSegway :public CObjectX
{
public:
	CTitleSegway(int nPriority = 4);	// コンストラクタ
	~CTitleSegway();					// デストラクタ
	static CTitleSegway* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);
private:
	int m_nIdxXFile;		// 使っているXファイルの番号
};
#endif