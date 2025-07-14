//=============================================================================
//
//	プレイヤー処理 [player.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h" 
#include "block.h"
#include "moveblock.h"
#include "effect.h"
#include "sound.h"
#include "score.h"
#include "fade.h"
#include "particle.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer2=NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点バッファへのポインタ
Player g_player;//プレイヤーの情報

//=====================
//ポリゴンの初期化処理
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hoppingman000.png",
		&g_pTexturePlayer2);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		 FVF_VERTEX_2D ,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);
	g_player.nCounterAnim=0;							//カウンターを初期化する
	g_player.nPatternAnim = 0;							//パターンNo.を初期化する
	g_player.pos = D3DXVECTOR3(200,500, 0);				//位置を初期化する
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動値を初期化する
	g_player.rot= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//向きを初期化する
	g_player.state= PLAYERSTATE_NORMAL;					//プレイヤーの状態
	g_player.nCntState=0;								//状態管理カウンター
	g_player.nLife=1;									//体力
	g_player.bDisp=true;								//表示するかしないか
	g_player.bJump = true;								//ジャンプしているかしてないか
	g_player.bRightMove = true;							//右に向いているかどうか
	g_player.bMove = false;								//動いているかどうか
	g_player.bUse = false;								//使われているかどうか
	g_player.pBlock = NULL;								//pBlockを初期化する

	//対角線の長さを算出する
	g_player.fLength = sqrtf(((OBJ_WIDTH * OBJ_WIDTH)/2.0f) + (OBJ_HEIGHT * OBJ_HEIGHT));
	g_player.fAngle = atan2f(OBJ_WIDTH, (OBJ_HEIGHT*2.0f));

	//当たり判定の中心をずらす
	g_player.posPGCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PGPOS;
	g_player.posPGCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PGPOS;

	g_player.posPYCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PYPOS;
	g_player.posPYCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PYPOS;

	VERTEX_2D* pVtx=0;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;
	
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;
	
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI/2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.z = 0.0f;													
																			
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定　　　　
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//===================
//ポリゴンの終了処理
//===================
void UninitPlayer(void)
{
	StopSound();
	//テクスチャの破棄
	if (g_pTexturePlayer2 != NULL)
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//====================
//ポリゴンの更新処理
//====================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx=0;					//頂点情報へのポインタ
	XINPUT_STATE* pStick = GetJoypad();	//スティック取得
	static float fData = 0.25;
	bool goal=GetGoal();
	if (g_player.nLife > 0&& goal == false)
	{
		if (GetKeyboardPress(DIK_Q) == true)
		{//Qキーが押されたとき
			g_player.rot.z += 0.05f;
		}

		else if (GetKeyboardPress(DIK_E) == true)
		{//Eキーが押されたとき
			g_player.rot.z -= 0.05f;
		}

		if (GetJoypadPress(JOYKEY_LEFT) == true||pStick->Gamepad.sThumbLX<=-20000)
		{//左ボタンが押されたとき
			g_player.rot.z += 0.05f;
		}

		else if (GetJoypadPress(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 20000)
		{//右ボタンが押されたとき
			g_player.rot.z -= 0.05f;
		}
		else if (GetJoypadPress(JOYKEY_RIGHTS) == true && GetJoypadPress(JOYKEY_LEFTS) == true|| KeyboardTrigger(DIK_F) == true)
		{
			SetFade(MODE_GAME);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();




	//重力加算
	g_player.move.y += GRAVI;

	if (goal == false)
	{
		//位置の更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
	}


	//前回の位置を保存
	g_player.posPGOld = g_player.posPGCircle;

	g_player.posPYOld = g_player.posPYCircle;
	if (g_player.nLife <= 0)
	{
		g_player.rot.z += 0.2f;
	}
	//位置情報の更新
	g_player.posPGCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PGPOS;
	g_player.posPGCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PGPOS;

	g_player.posPYCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PYPOS;
	g_player.posPYCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PYPOS;

	SetEffect(g_player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 5.0f, 40, EFFECTTYPE_PLAYER);
	if (g_player.nLife > 0)
	{
		//ブロックの当たり判定
		g_player.bJump = !CollisionBlock(&g_player.posPGCircle, &g_player.posPGOld, &g_player.posPYCircle, &g_player.posPYOld, &g_player.move, OBJ_WIDTH, OBJ_HEIGHT, &g_player.pBlock);
	}

	if (g_player.pBlock != NULL && g_player.bJump == false)
	{//プレイヤーが着地した瞬間

		switch (g_player.pBlock->nType)
		{
		case BLOCK_NORMAL:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;

		case BLOCK_BUTTON:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;

		case BLOCK_MOVEWALL:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;

		case BLOCK_SLIME:
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * SLIMEJUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * SLIMEJUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;

		case BLOCK_TRANPORIN:
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * TRANPORINJUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * TRANPORINJUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;

		case BLOCK_GOAL:
			
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
			g_player.bJump = true;
			break;
		case BLOCK_LR:

			g_player.move.x = g_player.pBlock->move.x;	//移動値代入
			g_player.move.y = 0;
			g_player.pos.y = g_player.pBlock->pos.y- g_player.pBlock->fHeight;//Y軸固定
			if (GetKeyboardPress(DIK_SPACE) == true||GetJoypadPress(JOYKEY_A) == true)
			{//スペースを押した場合
				PlaySound(SOUND_LABEL_RAND01);
				SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
				g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
				g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
				g_player.bJump = true;
			}
			break;
		case BLOCK_UPDOWN:

			g_player.move.y = g_player.pBlock->move.y;	//ジャンプ力加算
			g_player.move.x = 0;
			g_player.pos.y = g_player.pBlock->pos.y - g_player.pBlock->fHeight;//Y軸固定
			if (GetKeyboardPress(DIK_SPACE) == true || GetJoypadPress(JOYKEY_A) == true)
			{
				PlaySound(SOUND_LABEL_RAND01);
				SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
				g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//ジャンプ力加算
				g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//ジャンプ力加算
				g_player.bJump = true;
			}
			break;
		}

	}

	if (g_player.nLife > 0)
	{
		//ムーブブロックの当たり判定
		g_player.bJump = !CollisionMoveBlock(&g_player.posPGCircle, &g_player.posPGOld, &g_player.posPYCircle, &g_player.posPYOld, &g_player.move, OBJ_WIDTH, OBJ_HEIGHT);
	}



	if (g_player.pos.y >= 720.0f)
	{//プレイヤーの位置が画面外に出た場合

		if (g_player.nLife > 0)
		{
			//プレイヤーのライフを1減らす
			g_player.nLife--;
		}
		//ジャンプしていない
		//g_player.bJump = false;	
	}

	if (g_player.pos.x  <= -150.0f)
	{//プレイヤーが右の画面外から出た場合

		//左の画面外に移動させる
		g_player.pos.x = 1400.0f;
	}

	if (g_player.pos.x >= 1500.0f)
	{//プレイヤーが左の画面外から出た場合
		g_player.pos.x = -70.0f;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//====================
//ポリゴンの描画処理
//====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
 	if (g_player.bDisp == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer2);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================
// プレイヤーの値を返す
//=====================
Player* GetPlayer(void)
{
	return &g_player;
}