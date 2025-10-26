//**************************************
//
// レンダリング処理 [renderer.h]
// Author:SasakiSoichiro
//
//**************************************
#ifndef _RENDERER_H_ // このマクロ定義がされていなかったら
#define _RENDERER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

//********************
// レンダリングクラス
//********************
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画
	LPDIRECT3DDEVICE9 GetDevice(void);		// デバイスの取得
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTextureMT[0]; }

private:
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ
	LPDIRECT3DTEXTURE9 m_pTextureMT[2];	// レンダリングターゲット用テクスチャ
	LPDIRECT3DSURFACE9 m_pRenderMT[2];	// テクスチャレンダリング用インターフェース
	LPDIRECT3DSURFACE9 m_pZBuffMT;		// テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9 m_viewportMT;			// テクスチャレンダリング用ビューポート
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuffMT;// フィードバック用ポリゴンの頂点バッファ

};
#endif