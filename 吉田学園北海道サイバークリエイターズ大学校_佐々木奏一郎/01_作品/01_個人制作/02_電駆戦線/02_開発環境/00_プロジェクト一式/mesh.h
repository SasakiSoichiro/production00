//******************************************
//
//	メッシュフィールド処理 [Meshfield.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _MESHFIELD_H_// このマクロ定義がされていなかったら
#define _MESHFIELD_H_// 2重インクルード防止のマクロ定義

//***********************
// インクルード
//***********************
#include "main.h"
#include "object.h"
#include <fstream>
#include <vector>

//**********************
// マクロ定義
//**********************
#define OBJ_X (500.0f)	// X方向の大きさ
#define OBJ_Z (500.0f)	// Z方向の大きさ
#define XMESH (100)		// X方向の分割数
#define ZMESH (100)		// Z方向の分割数
#define VTXCNT ((XMESH+1)*(ZMESH+1))				// 頂点数の計算
#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))		// ポリゴン数の計算
#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)	// インデックス数の計算

//**********************
// メッシュクラス
//**********************
class CMesh :public CObject
{
public:
	CMesh(int nPriority=2);	// コンストラクタ
	~CMesh();				// デストラクタ
	static CMesh* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報
	float GetHeight(D3DXVECTOR3 pos);				// 高さ情報取得
	D3DXVECTOR3 GetNormal(D3DXVECTOR3 pos);			// 法線情報の取得
	void MoveY(D3DXVECTOR3 pos);					// 高さを変える
	void Save(void);								// セーブ
	void Load(void);								// ロード
	void SetCaldera(float size);					// くぼみの大きさを設定
private:
	static D3DXVECTOR3 VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);// 法線計算用
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	float m_caldera;		// くぼみの大きさ
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	float m_Sum;			// 計算用
};

#endif