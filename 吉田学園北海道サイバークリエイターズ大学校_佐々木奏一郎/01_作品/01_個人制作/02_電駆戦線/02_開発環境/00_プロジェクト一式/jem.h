//**************************************
//
// 宝石処理 [jem.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _JEM_H_ // このマクロ定義がされていなかったら
#define _JEM_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// 宝石クラス
//********************
class CJem :public CObjectX
{
public:
	CJem(int nPriority = 4);	// コンストラクタ
	~CJem();					// デストラクタ
	static CJem* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
	void Shake(void);				// 揺れる
private:
	int m_nIdxXFile[3];	// 使うモデルの番号
	int m_nLife;		// 宝石の体力
	int m_nShake;		// 揺れる時間
	D3DXVECTOR3 m_OffsetPos;// 初期の位置
};
#endif