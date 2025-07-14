//=============================================================================
//
//メイン処理 [main.cpp]
// Author : 佐々木奏一郎 
// 
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "fade.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
//#include "ranking.h"
#include "edit.h"
#include "stageselect.h"
#include "blockinfo.h"
//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;				//なにこれ
int g_nCntFPS = 0;						//FPSのカウント
bool g_Start = false;					//ゲームをスタート下かどうか
MODE g_mode = MODE_TITLE;				//現在のモード

//====================================
// メイン関数
//====================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hInstanceprev, _In_ LPSTR bCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;	//現在時刻
	DWORD dwExecLastTime;	//最後に処理した時刻
	DWORD dwFrameCnt;
	DWORD dwFPSLastTime;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return-1;
	}
	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	//ウィンドウの表示
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
	dwFrameCnt = 0;
	dwFPSLastTime = timeGetTime();
	//メッセージループ
	while(1)// (GetMessage(&msg, NULL, 0, 0) != 0)
	{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{//windowsの処理
				if(msg.message==WM_QUIT)
				{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
					break;
				}
			else
			{//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
			else
			{//DirectXの処理
				dwCurrentTime = timeGetTime();//現在時刻を取得
				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{
					g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					dwFrameCnt = 0;
				}
				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{//60分の1秒経過
					dwExecLastTime = dwCurrentTime;//処理開始時刻を保存
					//更新処理
					Update();
					//描画処理
					Draw();
					dwFrameCnt++;
				}
			
			}
	}
	//終了処理
	Uninit();
	timeEndPeriod(1);
	//ウィンドウの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//====================
//プロシージャ
//====================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
  	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//=======================
//デバイスの取得
//=======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================
//初期化処理
//=======================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount = 1;									//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						//デブスバッファとステンシブルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デブスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行なう)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3Dデバイスの生成(描画処理はCPUで行なう)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスに生成(描画処理と頂点処理をCPUで行なう)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//デバッグフォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &g_pFont);
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);          //======================
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    //アルファブレンドの設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//======================
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャステージステート
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//各種オブジェクトの初期化処理

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}


	InitSound(hWnd);

	SetMode(g_mode);

	InitFade(g_mode);



	return S_OK;
}
//==================
//終了処理
//==================
void Uninit(void)
{


	//デバッグ表示用のフォントを破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//各オブジェクトの終了処理

	//フェードの終了処理
	UninitFade();

	//サウンドの終了処理
	UninitSound();

	//キーボードの終了処理
	UninitKeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

//==================
//更新処理
//==================
void Update(void)
{
	XINPUT_STATE* pStick = GetJoypad();
	//各種オブジェクトの更新処理


	//キーボードの更新処理
	UpdateKeyboard();

	//ジョイパッドの更新処理
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面

		UpdateTitle();//タイトルの更新処理
		break;
	case MODE_TUTORIAL://チュートリアル画面

		UpdateTutorial();//チュートリアルの更新処理
		break;
	case MODE_GAME://ゲーム画面

		if (KeyboardTrigger(DIK_E) == true || KeyboardTrigger(DIK_Q) == true|| JoyPadTrigger(JOYKEY_LEFT)==true|| JoyPadTrigger(JOYKEY_RIGHT)==true||pStick->Gamepad.sThumbLX <= -20000 || pStick->Gamepad.sThumbLX >= 20000)
		{
			g_Start = true;
		}
		if(g_Start == true)
		{
			UpdateGame();//ゲームの更新処理
		}
		break;
	case MODE_RESULT://リザルト画面

		UpdateResult();//リザルトの更新処理
		break;
	case MODE_RANKING://ランキング画面

		break;

	case MODE_EDIT://エディット画面

		UpdateEdit();//エディットの更新処理
		break;
	case MODE_STAGESELECT://ステージ選択画面

		UpdateStageSelect();//ステージ選択の更新処理
		break;

	case MODE_BLOCKINFO://ステージ選択画面

		UpdateBlockInfo();//ステージ選択の更新処理
		break;
	}
	//フェードの更新処理
	UpdateFade();

}

//=========
//描画処理
//=========
void Draw(void)
{
	//画面のクリア(バックバッファ＆Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画処理
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面

			DrawTitle();//タイトルの描画処理
			break;
		case MODE_TUTORIAL://タイトル画面

			DrawTutorial();//チュートリアルの描画処理
			break;
		case MODE_GAME://ゲーム画面

			DrawGame();//ゲームの描画処理
			break;
		case MODE_RESULT://リザルト画面

			DrawResult();//リザルトの描画処理
			break;
		case MODE_RANKING://リザルト画面

			break;
		case MODE_EDIT://リザルト画面

			DrawEdit();//ランキングの描画処理
			break;
		case MODE_STAGESELECT://リザルト画面

			DrawStageSelect();//ランキングの描画処理
			break;
		case MODE_BLOCKINFO://ステージ選択画面

			DrawBlockInfo();//ステージ選択の更新処理
			break;
		}
		//フェードの描画処理
		DrawFade();

#ifdef _DEBUG//デバッグの場合
		
		////FPSの描画処理
		//DrawFPS();

		////プレイヤー座標の描画処理
		//DrawPos();

		////当たり判定座標の描画処理
		//DrawPosPGCircle();

		////アニメーションパターンの描画処理
		//DrawAnimPatten();

		////アニメーションパターンの描画処理
		//DrawPosPYCircle();

		////ムーブ値の描画処理
		//DrawMove();

		////現在のステージ
		//DrawStage();


#endif
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================
//モードの状態設定
//===================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面

		UninitTitle();//タイトルの終了処理
		break;
	case MODE_TUTORIAL://チュートリアル画面

		UninitTutorial();//チュートリアルの終了処理
		break;
	case MODE_GAME://ゲーム画面

		UninitGame();//ゲームの終了処理
		break;
	case MODE_RESULT://リザルト画面

		UninitResult();//リザルトの終了処理
		break;
	case MODE_RANKING://ランキング画面

		break;
	case MODE_EDIT://リザルト画面

		UninitEdit();//ランキングの描画処理
		break;
	case MODE_STAGESELECT://リザルト画面

		UninitStageSelect();//ランキングの描画処理
		break;
	case MODE_BLOCKINFO://ステージ選択画面

		UninitBlockInfo();//ステージ選択の更新処理
		break;
	}
	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面

		InitTitle();//タイトルの初期化処理
		break;
	case MODE_TUTORIAL://チュートリアル画面

		InitTutorial();//チュートリアルの初期化処理
		break;
	case MODE_GAME://ゲーム画面

		InitGame();//ゲームの初期化処理
		g_Start = false;
		break;
	case MODE_RESULT://リザルト画面

		InitResult();//リザルトの初期化処理
		break;
	case MODE_RANKING://リザルト画面

		break;
	case MODE_EDIT://リザルト画面

		InitEdit();//ランキングの描画処理
		break;
	case MODE_STAGESELECT:
		InitStageSelect();
		break;
	case MODE_BLOCKINFO://ステージ選択画面

		InitBlockInfo();//ステージ選択の更新処理
		break;
	}
	g_mode = mode;//現在の画面を切り替える
}
//==================
//モードの取得
//==================
MODE GetMode(void)
{
	return g_mode;
}

//===============
// FPSの描画処理
//===============
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//================================
// プレイヤーの位置座標の描画処理
//================================
void DrawPos(void)
{
	RECT rect = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX= pPlayer->pos.x, fY= pPlayer->pos.y;
	sprintf(&aStr[0], "プレイヤー座標　X:%.2f　Y:%.2f\n", pPlayer->pos.x,pPlayer->pos.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==========================================
// アニメーションパターンカウントの描画処理
//==========================================
void DrawAnimPatten(void)
{
	RECT rect = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	wsprintf(&aStr[0], "アニメーションパターンカウント:%d\n", pPlayer->nPatternAnim);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// プレイヤーの位置座標の描画処理
//================================
void DrawPosPGCircle(void)
{
	RECT rect = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX = pPlayer->pos.x, fY = pPlayer->pos.y;
	sprintf(&aStr[0], "ポゴ当たり判定座標　X:%.2f　Y:%.2f\n", pPlayer->posPGCircle.x, pPlayer->posPGCircle.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// プレイヤーの位置座標の描画処理
//================================
void DrawPosPYCircle(void)
{
	RECT rect = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX = pPlayer->pos.x, fY = pPlayer->pos.y;
	sprintf(&aStr[0], "プレイヤー当たり判定座標　X:%.2f　Y:%.2f\n", pPlayer->posPYCircle.x, pPlayer->posPYCircle.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// プレイヤーの位置座標の描画処理
//================================
void DrawMove(void)
{
	RECT rect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	sprintf(&aStr[0], "ムーブ値　X:%.2f　Y:%.2f\n", pPlayer->move.x, pPlayer->move.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void DrawStage(void)
{
	RECT rect = { 0,90,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int stage = GetStage();
	sprintf(&aStr[0], "ステージ%d\n", stage);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}