//*****************************************
//
// パーティクル処理 [particle.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _PARTICLE_H_ // このマクロ定義がされていなかったら
#define _PARTICLE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//********************
// パーティクルクラス
//********************
class CParticle :public CObject
{
public:
	CParticle(int nPriority=3);	// コンストラクタ
	~CParticle();				// デストラクタ
	static CParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR col);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新		
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定	
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	void SetCol(D3DXCOLOR col);		// 色の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置情報の取得
	D3DXVECTOR2 GetSize(void){ return m_size; }	// 大きさ情報の設定
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR2 m_size;	// 大きさ
	D3DXCOLOR m_col;	// 色
	float m_fLength;	// 移動距離
	float m_fRad;		// 半径
	int m_nAngle;		// 向き
	int m_nLife;		// 寿命
};
#endif