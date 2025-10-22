//**************************************
//
// 宝石の破片処理 [jempiece.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _JEMPIECE_H_ // このマクロ定義がされていなかったら
#define _JEMPIECE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//************************
// 宝石の破片クラス
//************************
class CJemPiece :public CObjectX
{
public:
	CJemPiece(int nPriority = 3);	// コンストラクタ
	~CJemPiece();					// デストラクタ
	static CJemPiece* Create(D3DXVECTOR3 pos, float fAngle,int nType);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
private:
	int m_nIdxXFile;	// 使うテクスチャの番号
	D3DXVECTOR3 m_move;	// 動く距離
	float m_fAngle;		// 向き
	int m_nLife;		// ライフ
	int m_nType;		// 種類
};
#endif