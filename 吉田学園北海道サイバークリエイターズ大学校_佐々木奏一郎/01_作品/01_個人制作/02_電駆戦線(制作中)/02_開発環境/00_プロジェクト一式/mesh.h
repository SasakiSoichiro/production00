//=============================================================================
//
//	メッシュフィールド処理 [Meshfield.h]
// Author:Sasaki Soichiro
//
//=============================================================================
#ifndef _MESHFIELD_H_// このマクロ定義がされていなかったら
#define _MESHFIELD_H_// 2重インクルード防止のマクロ定義
#include "main.h"
#include "object.h"
#include <fstream>
#include <vector>
#define OBJ_X (600.0f)
#define OBJ_Z (600.0f)
#define XMESH (100)
#define ZMESH (100)
#define VTXCNT ((XMESH+1)*(ZMESH+1))
#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))
#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)

class CMesh :public CObject
{
public:
	CMesh(int nPriority=3);	// コンストラクタ
	~CMesh();
	static CMesh* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// 位置
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報
	float GetHeight(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetNormal(D3DXVECTOR3 pos);
	void MoveY(D3DXVECTOR3 pos);
	void Save(const std::vector<int>& nNum,const std::string& FileName);
	void Load(void);
private:
	static D3DXVECTOR3 VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);// 法線計算用
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
};

#endif