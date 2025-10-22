//**********************************
//
//	煙処理 [smoke.h]
// Author Sasaki Soichiro
//
//**********************************
#ifndef _SMOKE_H_//このマクロ定義がされていなかったら
#define _SMOKE_H_//2重インクルード防止のマクロ定義
//*******************
// インクルード
//*******************
#include "main.h"
#include "objectBillboard.h"

//************************
// 煙クラス
//************************
class CSmoke :public CObjectBillboard
{
public:
	CSmoke(int nPriority = 4);	// コンストラクタ
	~CSmoke();					// デストラクタ

	static CSmoke* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// インスタンス生成

	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetCol(D3DXCOLOR col);		// 色の設定
	void SetSize(D3DXVECTOR2 size);	// 大きさの設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	D3DXVECTOR2 GetSize(void);		// 大きさ情報取得
private:
	int  m_nIdxTexture;			// 使っているテクスチャの番号
	D3DXVECTOR3 m_move;			// 移動量
	int m_nLife;				// 寿命
};
#endif