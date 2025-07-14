//***************************************
//
//	オブジェクト3D処理 [object3D.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _OBJECT3D_H_// このマクロ定義がされていなかったら
#define _OBJECT3D_H_// 二重インクルード防止のマクロ定義
//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//**********************
// オブジェクト3Dクラス
//**********************
class CObject3D :public CObject
{
public:
	CObject3D(int nPriority = 4);	// コンストラクタ
	~CObject3D();					// デストラクタ
	static CObject3D* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2{ 0.0f,0.0f }; }		// 大きさ情報
	float GetHeight(D3DXVECTOR3 pos);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXMATRIX m_mtxWorld;	// マトリックス
};

#endif