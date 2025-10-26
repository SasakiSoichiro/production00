//*************************************************
//
//	ビルボード処理 [objectBillboard.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _OBJECTBILLBOARD_H_// このマクロ定義がされていなかったら
#define _OBJECTBILLBOARD_H_// 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//*******************
// ビルボードクラス
//*******************
class CObjectBillboard:public CObject
{
public:
	CObjectBillboard(int nPriority = 4);// コンストラクタ;
	~CObjectBillboard();				// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);// テクスチャ座標の設定
	void SetCol(D3DXCOLOR col);					// 色の設定
	void SetSize(D3DXVECTOR2 size);				// 大きさの設定
	void SetOffset(D3DXVECTOR2 offset);			// オフセットの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置情報取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// 向き情報取得
	D3DXCOLOR GetCol(void) { return m_col; }	// 意図情報取得
	D3DXVECTOR2 GetSize(void) { return m_size; }// 大きさ情報取得
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR2 m_size;					// 大きさ
	D3DXVECTOR2 m_offset;				// オフセット
	D3DXCOLOR m_col;					// 色
	D3DXMATRIX m_mtxWorld;				// マトリックス
};

#endif