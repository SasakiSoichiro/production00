//**************************************
//
// ランク処理 [rank.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RANK_H_ // このマクロ定義がされていなかったら
#define _RANK_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// ランククラス
//********************
class CRank :public CObjectX
{
public:
	CRank(int nPriority = 4);	// コンストラクタ
	~CRank();					// デストラクタ
	static CRank* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetRank(void);				// Xmodelの設定
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	D3DXVECTOR3 GetRot(void);		// 向き情報取得
private:
	int m_nIdxXFile[4];				// 使っているXファイルの番号
};
#endif