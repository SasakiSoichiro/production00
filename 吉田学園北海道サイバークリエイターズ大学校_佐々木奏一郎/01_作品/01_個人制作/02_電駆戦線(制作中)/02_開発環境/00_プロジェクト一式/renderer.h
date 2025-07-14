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
class CRenderer {
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画
	LPDIRECT3DDEVICE9 GetDevice(void);		// デバイスの取得
private:
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ
};
#endif