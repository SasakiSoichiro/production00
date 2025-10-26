//******************************************
//	オブジェクトX処理 [objectX.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _OBJECTX_H_// このマクロ定義がされていなかったら
#define _OBJECTX_H_// 2重インクルード防止のマクロ定義
//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "Xmodel.h"

//***********************
// Xファイルの表示クラス
//***********************
class CObjectX :public CObject
{
public:
	CObjectX(int nPriority = 4);	// コンストラクタ;
	~CObjectX();					// デストラクタ
	static CObjectX* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }					// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// 向きの設定
	void SetSize(D3DXVECTOR3 size) { m_size = size; }				// 大きさの設定
	void SetMatrix(D3DMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// マトリックスの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; };						// 位置情報
	D3DXVECTOR3 GetRot(void) { return m_rot; };						// 向き情報
	D3DXVECTOR3 GetSize(void) { return m_size; }					// 大きさ情報
	CXModel::XMODEL GetXModel(void){return m_XModel;}				// XModel情報
	void BindXFile(CXModel::XMODEL pXFile);							// Xファイルの割り当て
private:
	CXModel::XMODEL m_XModel;			// Xmodel情報
	D3DXMATRIX m_mtxWorld;				// マトリックス
	LPDIRECT3DTEXTURE9 m_apTextureModel;// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// 大きさ
	int  m_nIdxTexture[128];			// テクスチャのインデックス
};

#endif