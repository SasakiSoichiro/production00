//=============================================================================
//
//	タイトル処理 [title.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "buckground.h"
#define MAX_TITLE (2)
//タイトル構造体
typedef struct
{
	D3DXVECTOR3 pos;//座標
	D3DXVECTOR3 col;//カラー
	int nType;//種類
	bool bUse;//使用状態
	float fHeight;//高さ
	float fWidth;//幅
	TITLESTATE state;//状態
}Title;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファへのポインタ
Title g_aTitle[MAX_TITLE];//タイトル構造体の情報
TITLE g_Title;//タイトル列挙型の情報
int g_nCntAnim;//タイトル状態
int g_nPatternAnim;//状態パターン
int g_nTimeCnt;
//タイトル画面の初期化処理
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TITLE000.png",
		&g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAMESTART000.png",
		&g_pTextureTitle[0]);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].nType = 0;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLESTATE_NONE;//何もしていない状態
	}

	g_nCntAnim = 0;//タイトル状態
	g_nPatternAnim = 0;//状態パターン
	g_nTimeCnt = 0;
	//頂点バッファの生成。頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_TITLE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	
	SetTitle(TITLE_1, D3DXVECTOR3(630.0f, 600.0f, 0.0f));
	SetTitle(TITLE_2, D3DXVECTOR3(650.0f, 250.0f, 1.0f));
	
	
	
	
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//背景の初期化処理
	InitBuckground();

	////サウンドの再生
	//PlaySound(SOUND_LABEL_BGM02);
}
//タイトル画面の終了処理
void UninitTitle(void)
{

	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle!= NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle= NULL;
	}

	//背景の終了処理
	UninitBuckground();
}
//タイトル画面の更新処理
void UpdateTitle(void)
{
	GetFade();//フェードの取得

	FADE g_fade = GetFade();//現在の状態

	if (KeyboardTrigger(DIK_RETURN) == true)
	{//Enterキーが押された

		//SE再生
		PlaySound(SOUND_LABEL_SE002);
		
		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && nCntTitle==1/*g_aTitle[nCntTitle].nType == TITLE_2*/)
			{
				g_aTitle[nCntTitle].state = TITLESTATE_FLASH;
			}
		}
		//モード設定(ゲーム画面に移動)
		SetFade(MODE_BLOCKINFO);
	}
	if (JoyPadTrigger(JOYKEY_A) == true)
	{//Aボタンが押された

		//SE再生
		PlaySound(SOUND_LABEL_SE002);

		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && nCntTitle == 1/*g_aTitle[nCntTitle].nType == TITLE_2*/)
			{
				g_aTitle[nCntTitle].state = TITLESTATE_FLASH;
			}
		}

		//モード設定(ゲーム画面に移動)
		SetFade(MODE_BLOCKINFO);
	}

	g_nTimeCnt++;
	if (g_nTimeCnt >= 900)
	{
		//モード設定(ランキング画面に移動)
		SetFade(MODE_BLOCKINFO);
	}
	TitleFlash(TITLE_2);//タイトルの点滅

	if (KeyboardTrigger(DIK_F2) == true)
	{
		//モード設定(ランキング画面に移動)
		SetFade(MODE_EDIT);
	}

	//背景の更新処理
	UpdateBuckground();

}
//タイトル画面の描画処理
void DrawTitle(void)
{
	//背景の描画処理
	DrawBuckground();

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for(int nCnt=0;nCnt<MAX_TITLE;nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCnt].nType]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
	}
		

}
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	int nCnt;
	VERTEX_2D* pVtx;//頂点情報へのポインタ
//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_aTitle[nCnt].bUse == false)
		{
			g_aTitle[nCnt].nType = nType;
			g_aTitle[nCnt].pos = pos;
			g_aTitle[nCnt].bUse = true;
			//場合分け
			switch (nType)
			{
			case TITLE_1:
				g_aTitle[nCnt].fHeight = 150.0f;//高さ
				g_aTitle[nCnt].fWidth = 400.0f;//横幅
				break;
			case TITLE_2:
				g_aTitle[nCnt].fHeight = 350.0f;//高さ
				g_aTitle[nCnt].fWidth = 800.0f;//横幅
				break;
			}
			//頂点座標1の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y - g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//1つ目の頂点情報
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y - g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//2つ目の頂点情報
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y + g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//3つ目の頂点情報
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y + g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//4つ目の頂点情報
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}
void TitleFlash(int nType)
{
	int nCnt;
	VERTEX_2D* pVtx;//頂点情報へのポインタ
//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_aTitle[nCnt].bUse == true && g_aTitle[nCnt].state == TITLESTATE_FLASH)
		{
			
			g_nCntAnim++;
			if (g_nCntAnim == 5)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
			}
			else if (g_nCntAnim == 10)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_nCntAnim = 0;//カウンターを初期値に戻す
			}
			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}