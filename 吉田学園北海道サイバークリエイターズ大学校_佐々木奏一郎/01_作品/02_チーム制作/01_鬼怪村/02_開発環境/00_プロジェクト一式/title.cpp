//================================================
//
//		タイトル	title.cpp
//
//			ryuusei.hirata
//================================================
#include "title.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"

//	マクロ
#define MAX_TITLE (3)

// グローバル
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLE] = { NULL };			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;						// 頂点バッファへのポインタ
Title g_aTitle[MAX_TITLE] = {};										// タイトル構造体の情報
TITLE g_Title;														// タイトル列挙型の情報
int g_nCntTitleAnim;												// タイトル状態
int g_nPatternAnim;													// 状態パターン
int ranking = 0;
int nSelect2 = 0;

//---------------
//	初期化処理
//---------------
void InitTitle(void)
{
	// BGMを鳴らす
	PlaySound(SOUND_LABEL_BGM);

	SetVolume(SOUND_LABEL_BGM,3.0f);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// テクスチャの読み込み(タイトル) 
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\title001.png",
		&g_apTextureTitle[0]);

	// テクスチャの読み込み(チュートリアル)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\tutorial002.png",
		&g_apTextureTitle[1]);

	// テクスチャの読込(スタート)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Start2.png",
		&g_apTextureTitle[2]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;

	// ロック
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// 各種変数の初期化
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].nType = TITLE_ONE;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLEMODE_NONE;//何もしていない状態
	}

	g_nCntTitleAnim = 0;
	g_nPatternAnim = 0;
	ranking = 0;
	nSelect2 = 0;

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定　　１２５
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		// 大事
	}

	SetTitle(TITLE_ONE, D3DXVECTOR3(630.0f, 200.0f, 0.0f));		// タイトル1
	SetTitle(TITLE_TWO, D3DXVECTOR3(650.0f, 440.0f, 0.0f));		// タイトル2
	SetTitle(TITLE_THREE, D3DXVECTOR3(650.0f, 540.0f, 0.0f));	// タイトル3

	// アンロック
	g_pVtxBuffTitle->Unlock();
}

//---------------
//	終了処理
//---------------
void UninitTitle(void)
{
	// 音楽を止める
	StopSound();

	UninitCamera();

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// テクスチャの破棄
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

	// 頂点バッファの解放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//---------------
//	更新処理
//---------------
void UpdateTitle(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	//int Pad1, Pad2;
	//Pad1 = GetJoypadInputState(DX_INPUT_PAD1);

	//Pad2 = GetJoypadInputState(DX_INPUT_PAD2);

	XINPUT_STATE* pState = GetState();

	UpdateCamera();

	// スティック状態の取得
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_TITLE - 1; nCntPause++)
	{// 一度すべてを半透明に
		// 頂点カラーの設定
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	if (KeybordTrigger(DIK_W) == true || KeybordTrigger(DIK_UP) == true || OnMouseDown(MOUSE_L) == true || JoyPadTrigger(JOYKEY_UP) == true)//W
	{// 上選択
		nSelect2--;
	}
	else if (KeybordTrigger(DIK_S) == true || KeybordTrigger(DIK_DOWN) == true || OnMouseDown(MOUSE_R) == true || JoyPadTrigger(JOYKEY_DOWN) == true)//S
	{// 下選択
		nSelect2++;
	}
	
	////ゲームパッド1P
	//if (Pad1 & JOYKEY_DOWN)
	//{
	//	nSelect2++;
	//}
	//else if (Pad1 & JOYKEY_UP)
	//{
	//	nSelect2--;
	//}

	////ゲームパッド2P
	//if (Pad2 & JOYKEY_DOWN)
	//{
	//	nSelect2++;
	//}
	//else if (Pad2 & JOYKEY_UP)
	//{
	//	nSelect2--;
	//}

	// 範囲を超えないようにする
	if (nSelect2 < MODE_TUTRIAL)
	{// ゼロより小さい
		nSelect2 = MODE_GAME;
	}
	else if (nSelect2 > MODE_GAME)
	{// 最大値以上
		nSelect2 = MODE_TUTRIAL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// g_nSelectを基準にポリゴンを不透明にする
	pVtx += 4 * nSelect2;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	if (KeybordTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{// 決定キーが押された

		 // 音楽を鳴らす
		PlaySound(SOUND_LABEL_SE);

		// メニューに合わせてモードの切り替え
		switch (nSelect2)
		{
			case MODE_TUTRIAL:
			SetFade(MODE_GAME);
			break;

			case MODE_GAME:
			SetFade(MODE_TUTRIAL);
			break;
		}
	}
}

//---------------
//	描画処理
//---------------
void DrawTitle(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTextureTitle[g_aTitle[nCnt].nType]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//---------------
//	配置処理
//---------------
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	// 頂点情報のポインタ

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].nType = nType;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].bUse = true;

			// 場合分け
			switch (nType)
			{
			case TITLE_ONE:

				g_aTitle[nCntTitle].fHeight = 180.0f;	// 高さ
				g_aTitle[nCntTitle].fWidth = 500.0f;	// 横幅
				break;

			case TITLE_TWO:

				g_aTitle[nCntTitle].fHeight = 100.0f;	// 高さ
				g_aTitle[nCntTitle].fWidth = 300.0f;	// 横幅
				break;

			case TITLE_THREE:
				g_aTitle[nCntTitle].fHeight = 100.0f;	// 高さ
				g_aTitle[nCntTitle].fWidth = 300.0f;	// 横幅

			}

			// 頂点座標1の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 4つ目の頂点情報

			break;
		}
		pVtx += 4;
	}

	// アンロック
	g_pVtxBuffTitle->Unlock();
}