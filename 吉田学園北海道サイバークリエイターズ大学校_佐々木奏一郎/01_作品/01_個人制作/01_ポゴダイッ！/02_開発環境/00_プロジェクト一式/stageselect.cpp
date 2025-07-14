//=============================================================================
//
//	ステージ選択処理 [stageselect.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "stageselect.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "main.h"
#include "sound.h"
#include "buckground.h"
#define MAX_STAGE (10)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureStageSelect[MAX_STAGE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageSelect = NULL;//頂点バッファへのポインタ
STAGE g_StageSelect;//ポーズメニュー
int StageState;
void InitStageSelect(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	g_StageSelect = STAGE_1;
	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			STAGE_TEXTURE[nCnt],
			&g_pTextureStageSelect[nCnt]);
	}
	//頂点バッファの生成。頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STAGE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStageSelect,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		if (nCnt < 5)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(200.0f + nCnt * 200.0f, 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f + nCnt * 200.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(200.0f + nCnt * 200.0f, 300.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(300.0f + nCnt * 200.0f, 300.0f, 0.0f);
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(200.0f + (nCnt - 5) * 200.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f + (nCnt - 5) * 200.0f, 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(200.0f + (nCnt - 5) * 200.0f, 500.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(300.0f + (nCnt - 5) * 200.0f, 500.0f, 0.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffStageSelect->Unlock();
}
void UninitStageSelect(void)
{
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureStageSelect[nCnt] != NULL)
		{
			g_pTextureStageSelect[nCnt]->Release();
			g_pTextureStageSelect[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffStageSelect != NULL)
	{
		g_pVtxBuffStageSelect->Release();
		g_pVtxBuffStageSelect = NULL;
	}

}
void UpdateStageSelect(void)
{

	if (KeyboardTrigger(DIK_D) == true ||KeyboardTrigger(DIK_RIGHT) == true || JoyPadTrigger(JOYKEY_RIGHT) == true)
	{
		//SE再生
		PlaySound(SOUND_LABEL_SE003);
		if (StageState == STAGE_5)
		{

			StageState = STAGE_1;
		}
		else if (StageState == STAGE_10)
		{
			StageState = STAGE_6;
		}
		else
		{
			StageState+=1;
		}
	}
	else if (KeyboardTrigger(DIK_A) == true ||KeyboardTrigger(DIK_LEFT) == true || JoyPadTrigger(JOYKEY_LEFT) == true)
	{

		//SE再生
		PlaySound(SOUND_LABEL_SE003);

		if (StageState == STAGE_1)
		{
			StageState += STAGE_5;
		}
		else if (StageState == STAGE_6)
		{
			StageState = STAGE_10;
		}
		else
		{
			StageState -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_W) == true || KeyboardTrigger(DIK_UP) == true || JoyPadTrigger(JOYKEY_UP) == true)
	{
		//SE再生
		PlaySound(SOUND_LABEL_SE003);

		if (StageState  <=STAGE_5)
		{
			StageState += 5;
		}
		else if (StageState > STAGE_5)
		{
			StageState -= 5;
		}
	}
	else if (KeyboardTrigger(DIK_S) == true || KeyboardTrigger(DIK_DOWN) == true || JoyPadTrigger(JOYKEY_DOWN) == true)
	{
		//SE再生
		PlaySound(SOUND_LABEL_SE003);

		if (StageState <= STAGE_5)
		{
			StageState += 5;
		}
		else if (StageState > STAGE_5)
		{
			StageState -= 5;
		}
	}

	VERTEX_2D* pVtx;//頂点情報へのポインタ
//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffStageSelect->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		if (nCnt == StageState)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
		pVtx += 4;
	}
	//メニューの選択→頂点カラーの設定
	if (KeyboardTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true)
	{
		//SE再生
		PlaySound(SOUND_LABEL_SE002);
		//メニューモードに合わせて切り替え
		switch (StageState)
		{
		case STAGE_1:
			SetFade(MODE_GAME);
			break;
		case STAGE_2:
			SetFade(MODE_GAME);
			break;
		case STAGE_3:
			SetFade(MODE_GAME);
			break;
		case STAGE_4:
			SetFade(MODE_GAME);
			break;
		case STAGE_5:
			SetFade(MODE_GAME);
			break;
		case STAGE_6:
			SetFade(MODE_GAME);
			break;
		case STAGE_7:
			SetFade(MODE_GAME);
			break;
		case STAGE_8:
			SetFade(MODE_GAME);
			break;
		case STAGE_9:
			SetFade(MODE_GAME);
			break;
		case STAGE_10:
			SetFade(MODE_GAME);
			break;
		}
	}
	if (KeyboardTrigger(DIK_B) == true || JoyPadTrigger(JOYKEY_B) == true)
	{
		SetFade(MODE_TITLE);
	}
}
void DrawStageSelect(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStageSelect, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ループ処理
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{//ブロックの数分ループする

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureStageSelect[nCnt]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
	}
}
int GetStageSelect(void)
{
	return StageState;
}