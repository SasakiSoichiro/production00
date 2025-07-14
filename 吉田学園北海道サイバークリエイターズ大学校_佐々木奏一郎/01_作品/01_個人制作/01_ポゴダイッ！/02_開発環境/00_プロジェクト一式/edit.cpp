#include "edit.h"
#include "Input.h"
#include "player.h"
#include "stageselect.h"
#include "moveblock.h"
#include <stdio.h>
#include <string.h>

//マクロ定義
#define EDIT_MOVE (5.0f)
#define MAX_WORD (4096)
#define MAX_STAGE (10)
#define TXTFILE ("data\\stage000.txt")
#define TXTFILE1 ("data\\stage001.txt")
#define TXTFILE2 ("data\\stage002.txt")
#define TXTFILE3 ("data\\stage003.txt")
#define TXTFILE4 ("data\\stage004.txt")
#define TXTFILE5 ("data\\stage005.txt")
#define TXTFILE6 ("data\\stage006.txt")
#define TXTFILE7 ("data\\stage007.txt")
#define TXTFILE8 ("data\\stage008.txt")
#define TXTFILE9 ("data\\stage009.txt")
//構造体定義
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
	bool bUse;
}EditInfo;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEdit[MAX_NUMBLOCK] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;			//頂点バッファへのポインタ
EditInfo g_EditInfo[MAX_BLOCK];								//ブロックの情報
int g_nCntEdit;
int g_stage;

void InitEdit(void)
{

	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			BLOCK_TEXTURE[nCnt],
			&g_pTextureEdit[nCnt]);
	}

	//初期化処理
	for (int nCnt=0;nCnt<MAX_BLOCK;nCnt++)
	{
		g_EditInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
		g_EditInfo[nCnt].fWidth = 30.0f;						//幅を初期化する
		g_EditInfo[nCnt].fHeight = 30.0f;						//高さを初期化する
		g_EditInfo[nCnt].nType = 0;								//種類を初期化する
		g_EditInfo[nCnt].bUse = false;							//使われていない状態にする	
	}
	g_EditInfo[0].bUse = true;
	g_stage = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdit,
		NULL);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの数分ループする

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x - 40, g_EditInfo[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x + 40, g_EditInfo[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x - 40, g_EditInfo[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x + 40, g_EditInfo[nCntBlock].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEdit->Unlock();

}
void UninitEdit(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBLOCK; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureEdit[nCnt] != NULL)
		{
			g_pTextureEdit[nCnt]->Release();
			g_pTextureEdit[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEdit != NULL)
	{
		g_pVtxBuffEdit->Release();
		g_pVtxBuffEdit = NULL;
	}

}

void UpdateEdit(void)
{
	if (GetKeyboardPress(DIK_A) == true)
	{//左に移動
		g_EditInfo[g_nCntEdit].pos.x -= EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//左に移動
		g_EditInfo[g_nCntEdit].pos.x += EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//左に移動
		g_EditInfo[g_nCntEdit].pos.y -= EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//左に移動
		g_EditInfo[g_nCntEdit].pos.y += EDIT_MOVE;
	}
	else if (KeyboardTrigger(DIK_T) == true)
	{//左に移動
		if (g_EditInfo[g_nCntEdit].nType >=1)
		{
			g_EditInfo[g_nCntEdit].nType -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_G) == true)
	{//左に移動
		if (g_EditInfo[g_nCntEdit].nType < MAX_NUMBLOCK-1)
		{
			g_EditInfo[g_nCntEdit].nType += 1;
		}
		
	}
	else if (KeyboardTrigger(DIK_O) == true)
	{//左に移動
		if (g_stage >= 1)
		{
			g_stage -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_L) == true)
	{//左に移動
		if (g_stage < MAX_STAGE - 1)
		{
			g_stage += 1;
		}

	}


	else if (KeyboardTrigger(DIK_Y) == true&& GetKeyboardPress(DIK_SPACE) == true)
	{//縦に小さく微調整
		g_EditInfo[g_nCntEdit].fHeight -= 2.0f;
	}


	else if (KeyboardTrigger(DIK_H) == true&& GetKeyboardPress(DIK_SPACE) == true)
	{//縦に大きく微調整
		g_EditInfo[g_nCntEdit].fHeight += 2.0f;
	}


	else if (KeyboardTrigger(DIK_Y) == true)
	{//縦に小さく
			g_EditInfo[g_nCntEdit].fHeight -= 40.0f;
	}


	else if (KeyboardTrigger(DIK_H) == true)
	{//縦に大きく
			g_EditInfo[g_nCntEdit].fHeight += 40.0f;
	}


	else if (KeyboardTrigger(DIK_U) == true && GetKeyboardPress(DIK_SPACE) == true)
	{//横に小さく微調整
		g_EditInfo[g_nCntEdit].fWidth -= 2.0f;
	}


	else if (KeyboardTrigger(DIK_J) == true && GetKeyboardPress(DIK_SPACE) == true)
	{//横に大きく微調整
		g_EditInfo[g_nCntEdit].fWidth += 2.0f;

	}


	else if (KeyboardTrigger(DIK_U) == true)
	{//横に小さく
		g_EditInfo[g_nCntEdit].fWidth -= 40.0f;
	}


	else if (KeyboardTrigger(DIK_J) == true)
	{//横に大きく
		g_EditInfo[g_nCntEdit].fWidth += 40.0f;
	}


	if (KeyboardTrigger(DIK_RETURN) == true)
	{//Enterキーを押して配置
		g_EditInfo[g_nCntEdit + 1].pos = g_EditInfo[g_nCntEdit].pos;


		g_EditInfo[g_nCntEdit + 1].nType = g_EditInfo[g_nCntEdit].nType;

		g_EditInfo[g_nCntEdit + 1].bUse = true;
		g_nCntEdit++;
	}
	if (KeyboardTrigger(DIK_F7) == true)
	{
		SaveEdit();
	}
	//頂点座標の設定
	VERTEX_2D* pVtx = 0;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{//ブロックの最大数分ぶん回す


		if (g_EditInfo[nCnt].bUse == true)
		{//ブロックを使用している場合

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x - g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y - g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x + g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y - g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x - g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y + g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x + g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y + g_EditInfo[nCnt].fHeight, 0.0f);
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEdit->Unlock();

}

void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEdit, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの数分ループする

		if (g_EditInfo[nCntBlock].bUse == true)
		{//弾が使用されている


			//テクスチャの設定
			pDevice->SetTexture(BLOCK_NORMAL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_BUTTON, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVEWALL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_SLIME, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_TRANPORIN, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_GOAL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}

}

void SaveEdit(void)
{
	//ファイルポインタを宣言
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	float fWidth=0.0f;
	float fHeight=0.0f;
	int nType=0;

	switch (g_stage)
	{
	case 0:
		pFile = fopen(TXTFILE, "w");
		break;
	case 1:
		pFile = fopen(TXTFILE1, "w");
		break;
	case 2:
		pFile = fopen(TXTFILE2, "w");
		break;
	case 3:
		pFile = fopen(TXTFILE3, "w");
		break;
	case 4:
		pFile = fopen(TXTFILE4, "w");
		break;
	case 5:
		pFile = fopen(TXTFILE5, "w");
		break;
	case 6:
		pFile = fopen(TXTFILE6, "w");
		break;
	case 7:
		pFile = fopen(TXTFILE7, "w");
		break;
	case 8:
		pFile = fopen(TXTFILE8, "w");
		break;
	case 9:
		pFile = fopen(TXTFILE9, "w");
		break;
	default:
		pFile = NULL;
		break;
	}

	if (pFile!=NULL)
	{
		fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

		for (int nCnt = 0; nCnt < g_nCntEdit; nCnt++)
		{
			if (g_EditInfo[nCnt].bUse== true)
			{
				fprintf(pFile, "BLOCKSET\n\n");
				fprintf(pFile, "POS %f %f %f\n\n", g_EditInfo[nCnt].pos.x, g_EditInfo[nCnt].pos.y, g_EditInfo[nCnt].pos.z);
				fprintf(pFile, "fWIDTH %f\n\n", g_EditInfo[nCnt].fWidth);
				fprintf(pFile, "fHEIGHT %f\n\n", g_EditInfo[nCnt].fHeight);
				fprintf(pFile, "TYPE %d\n\n", g_EditInfo[nCnt].nType);
				fprintf(pFile, "END_BLOCKSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n\n\n");
		fclose(pFile);
	}
	else
	{//開けなかったときの処理
		return;
	}
}

void LoadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	float fWidth=0.0f;
	float fHeight=0.0f;
	int nType=0;
	g_stage = GetStageSelect();
	//ファイルを開く
	switch (g_stage)
	{
	case 0://ステージ1
		pFile = fopen(TXTFILE, "r");
		break;
	case 1://ステージ2
		pFile = fopen(TXTFILE1, "r");
		SetMoveBlock(D3DXVECTOR3(340.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 2://ステージ3
		pFile = fopen(TXTFILE2, "r");
		break;
	case 3:
		pFile = fopen(TXTFILE3, "r");
		break;
	case 4:
		pFile = fopen(TXTFILE4, "r");
		break;
	case 5:
		pFile = fopen(TXTFILE5, "r");
		SetMoveBlock(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 6:
		pFile = fopen(TXTFILE6, "r");
		SetMoveBlock(D3DXVECTOR3(1100.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 7:
		pFile = fopen(TXTFILE7, "r");
		break;
	case 8:
		pFile = fopen(TXTFILE8, "r");
		break;
	case 9:
		pFile = fopen(TXTFILE9, "r");
		SetMoveBlock(D3DXVECTOR3(900.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	default:
		pFile = NULL;
		break;
	}
	
	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納
		//全部のテキストに書かれた情報を読み取りが終わるまで回す
		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);

			//読み取る特定の文字列が一致していたら
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{//POSを読み取ったら
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "fWIDTH") == 0)
					{
						fscanf(pFile, "%f", &fWidth);
					}
					else if (strcmp(aString, "fHEIGHT") == 0)
					{
						fscanf(pFile, "%f", &fHeight);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}
					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						SetBlock(pos, fWidth, fHeight, nType);
						break;
					}
				}
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				//whileを抜けるため
				break;
			}
		}
		fclose(pFile);

		Player* pPlayer = GetPlayer();

	}
	else
	{//開けなかったときの処理
		return;
	}
}

int GetStage(void)
{
	return g_stage;
}