//**********************************
//
// レンダラー処理 [renderer.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"

//===================
// コンストラクタ
//===================
CRenderer::CRenderer() 
{
	m_pD3D=NULL;			// Direct3Dオブジェクトへのポインタ
	m_pD3DDevice=NULL;		// Direct3Dデバイスへのポインタ
}
//===================
// デストラクタ
//===================
CRenderer::~CRenderer()
{
}
//=============
// 初期化処理
//=============
HRESULT CRenderer::Init(HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デブスバッファとステンシブルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デブスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行なう)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DirectX3Dデバイスの生成(描画処理はCPUで行なう)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//Direct3Dデバイスに生成(描画処理と頂点処理をCPUで行なう)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//======================
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// アルファブレンドの設定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//======================
	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャステージステート
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//テクスチャステージステート
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);

	return S_OK;
}

//===========
// 終了処理
//===========
void CRenderer::Uninit(void)
{
	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//============
// 更新処理
//============
void CRenderer::Update(void)
{
	// ポリゴンの更新
	CObject::UpdateAll();
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

//===========
// 描画処理
//===========
void CRenderer::Draw(void)
{

	// 画面のクリア(バックバッファ＆Zバッファのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(175, 223, 228, 255), 1.0f, 0);
	// 描画処理
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// 描画開始が成功した場合
	
		// ポリゴンの描画
		CObject::DrawAll();
		CDebugProc::Draw();
		// 描画終了
		m_pD3DDevice->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//*****************
// デバイスの取得
//*****************
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}