//*************************************************
//
//	ビルボード処理 [objectBillboard.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _OBJECTBILLBOARD_H_//このマクロ定義がされていなかったら
#define _OBJECTBILLBOARD_H_//二重インクルード防止のマクロ定義

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
	static CObjectBillboard* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報
	D3DXVECTOR2 GetSize(void) { return m_size; }	// 大きさ情報
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR2 m_size;		// 大きさ
	D3DXMATRIX m_mtxWorld;	// マトリックス
	int m_nIdxTexture;		// テクスチャのインデックス
};

#endif