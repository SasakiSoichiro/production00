//**************************************
//
// レールの可視化処理 [railmesh.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RAILMESH_H_// このマクロ定義がされていなかったら
#define _RAILMESH_H_// 2重インクルード防止のマクロ定義

//***********************
// インクルード
//***********************
#include "main.h"
#include "object.h"

//*********************
// レールメッシュクラス
//*********************
class CRailMesh :public CObject
{
public:
	CRailMesh(int nPriority = 2);	// コンストラクタ
	~CRailMesh();					// デストラクタ
	static CRailMesh* Create(D3DXVECTOR3 pos,int nType);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);			// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };		// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		// 向きの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; };			// 位置情報
	void Add(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);		// メッシュの追加
	void SetVtxPos(D3DXVECTOR3 pos,int nCnt);			// 頂点の位置設定
private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// インデックスへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	int m_nNumVtx;								// 現在の頂点数
	int m_nNumIdx;								// 現在のインデックス数
	int m_nType;								// 種類
};

#endif