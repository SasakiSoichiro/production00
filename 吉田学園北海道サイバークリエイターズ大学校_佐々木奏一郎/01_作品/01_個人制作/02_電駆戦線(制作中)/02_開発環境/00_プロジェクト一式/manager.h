//************************************
//
// マネージャ処理 [manager.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _MANAGER_H_ // このマクロ定義がされていなかったら
#define _MANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "Xmodel.h"
#include "object3D.h"
#include "mesh.h"

class CRenderer;

//********************
// マネージャクラス
//********************
class CManager
{
public:
	CManager();		// コンストラクタ
	~CManager();	// デストラクタ
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);	// 初期化
	void Uninit(void);											// 終了
	void Update(void);											// 更新
	void Draw(void);											// 描画
	static CRenderer* GetCRenderer(void) { return m_pRenderer; }				// レンダラー情報取得
	static CInputKeyboard* GetCInputKeyboard(void) { return m_pInputKeyboard; }	// キーボード情報取得
	static CInputMouse* GetCInputMouse(void) { return m_pInputMouse; }			// マウス情報取得
	static CInputJoypad* GetCInputJoypad(void) { return m_pInputJoypad; }		// ジョイパッド情報取得
	static CSound* GetCSound(void) { return m_pSound; }							// サウンド情報取得
	static CDebugProc* GetCDebugProc(void) { return m_pDebugProc; }				// デバッグ表示情報取得
	static CTexture* GetCTexture(void) { return m_pTexture; }					// テクスチャ情報取得
	static CCamera* GetCCamera(void) { return m_pCamera; }						// カメラ情報取得
	static CLight* GetCLight(void) { return m_pLight; }							// ライト情報取得
	static CXModel* GetCXModel(void) { return m_pXModel; }
	static CObject3D* GetCObject3D(void) { return m_pObject3D; }
	static CMesh* GetCMesh(void) { return m_pMesh; }
	static CPlayer* GetCPlayer(void) { return m_pPlayer; }

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
	static CInputMouse* m_pInputMouse;
	static CInputJoypad* m_pInputJoypad;
	static CSound* m_pSound;
	static CDebugProc* m_pDebugProc;
	static CTexture* m_pTexture;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CXModel* m_pXModel;
	static CObject3D* m_pObject3D;
	static CMesh* m_pMesh;
	static CPlayer* m_pPlayer;
};
#endif