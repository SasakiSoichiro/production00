//**************************************
//
// 軌跡処理 [orbit.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ORBIT_H_// このマクロ定義がされていなかったら
#define _ORBIT_H_// 2重インクルード防止のマクロ定義

//***********************
// インクルード
//***********************
#include "main.h"
#include "object.h"

//********************
// マクロ定義
//********************
#define MAX_ORBITVTX (30)


//*********************
// 軌跡クラス
//*********************
class COrbit :public CObject
{
public:
	COrbit(int nPriority = 2);	// コンストラクタ
	~COrbit();					// デストラクタ
	static COrbit* Create(D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);			// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };		// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		// 向きの設定
	void SetPosS(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);	// 2点の位置設定
	D3DXVECTOR3 GetPos(void) { return m_pos; };			// 位置情報
private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// インデックスへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	int m_Time;									// 時間
	int m_Frame;								// フレーム
	D3DXVECTOR3 m_FPos, m_SPos;					// 二点の位置
	D3DXVECTOR3 m_oldFPos[MAX_ORBITVTX / 2 - 1], m_oldSPos[MAX_ORBITVTX / 2 - 1];// 二点の前フレームの位置
};

#endif