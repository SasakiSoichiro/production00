//=============================================================================
//
//	ゲーム処理[game.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "buckground.h"
#include "input.h"
#include "pause.h"
#include "fade.h"
#include "ranking.h"
#include "rankingscore.h"
#include "score.h"
#include "block.h"
#include "moveblock.h"
#include "time.h"
#include "effect.h"
#include "particle.h"
#include "edit.h"
#include "sound.h"
//グローバル変数
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
bool g_bPause = false;						//ポーズ中かどうか
int g_nCntGameState = 0;					//状態管理カウンター
int g_nCntGameStateB = 0;					//状態管理カウンター
//=====================
//ゲームの初期化処理
//=====================
void InitGame(void)
{
	//各オブジェクトの初期化処理
	
	//背景の初期化処理
	InitBuckground();

	//プレイヤーの初期化処理
	InitPlayer();

	//エフェクトの初期化処理
	InitEffect();

	//パーティクルの初期化処理
	InitParticle();

	//ブロックの初期化処理
	InitBlock();

	//ムーブブロックの初期化処理
	InitMoveBlock();

	//スコアの初期化処理
	InitScore();

	//ポーズの初期化処理
	InitPause();

	//タイムの初期化処理
	InitTime();

	
	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCntGameState = 0;				//ゲームカウント初期化
	g_nCntGameStateB = 0;				//ゲームカウント初期化
	g_bPause = false;					//ポーズ解除
	SetScore(1000);
	LoadEdit();
	PlaySound(SOUND_LABEL_BGM01);
}
//===================
//ゲームの終了処理
//===================
void UninitGame(void)
{
	//各オブジェクトの終了処理

	//サウンドの停止
	StopSound();

	//背景の終了処理
	UninitBuckground();

	//プレイヤーの終了処理
	UninitPlayer();

	//エフェクトの終了処理
	UninitEffect();

	//パーティクルの終了処理
	UninitParticle();

	//ブロックの終了処理
	UninitBlock();

	//ムーブブロックの終了処理
	UninitMoveBlock();

	//スコアの終了処理
	UninitScore();

	//ポーズの終了処理
	UninitPause();

	//タイムの終了処理
	UninitTime();

}
//===================
//ゲームの更新処理
//===================
void UpdateGame(void)
{
	Player *LifePlayer = GetPlayer();
	
	bool goal = GetGoal();
	if (goal==true)
	{
		//モード設定
		g_gameState = GAMESTATE_END;
		g_nCntGameState++;
	}
	if (LifePlayer->nLife <= 0)
	{
		//モード設定
		//g_gameState = GAMESTATE_END;
		SetFade(MODE_GAME);
		//カウントを進める
		g_nCntGameState++;
	}
	if (KeyboardTrigger(DIK_P)==true)
	{//Pキーが押された

		g_bPause = g_bPause ? false: true;
	}
	if (JoyPadTrigger(JOYKEY_START) == true)
	{//Xボタンが押された

		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == true)
	{//ポーズ中

		//ポーズの更新処理
		UpdatePause();
	}
	else
	{
		//各オブジェクトの更新処理


		//背景の更新処理
		UpdateBuckground();

		//プレイヤーの更新処理
		UpdatePlayer();

		//エフェクトの更新処理
		UpdateEffect();

		//パーティクルの更新処理
		UpdateParticle();

		//ブロックの更新処理
		UpdateBlock();

		//ムーブブロックの更新処理
		UpdateMoveBlock();

		//スコアの更新処理
		UpdateScore();

		//タイムの更新処理
		UpdateTime();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
 		
			break;
		case GAMESTATE_END:
			if (g_nCntGameState >= 60)
			{
				AddScore(1000);
				g_nCntGameState = 0;
				g_gameState = GAMESTATE_NONE;//何もしていない状態に設定
				//画面の設定
				SetFade(MODE_RESULT);
				//ランキングの設定
				ResetRanking();
				SetRanking(GetScore());
			}
			break;
		}
	}
	
}
//=======================
//ゲーム画面の描画処理
//=======================
void DrawGame(void)
{
	//各オブジェクトの描画処理
	

	//バックグラウンドの描画処理
	DrawBuckground();

	//プレイヤーの描画処理
	DrawPlayer();

	//エフェクトの描画処理
	DrawEffect();

	//パーティクルの描画処理
	DrawParticle();

	//ブロックの描画処理
	DrawBlock();

	//ムーブブロックの描画処理
	DrawMoveBlock();

	//タイムの描画処理
	DrawTime();


	if (g_bPause == true)
	{//ポーズ中

		//ポーズの描画処理
		DrawPause();
	}

}

//===================
//ゲームの状態の設定
//===================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntGameState = 0;
}

//====================
//ゲームの状態の取得
//====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=====================
//ポーズの有効無効設定
//=====================
void SetEnblePause(bool bPause)
{
	g_bPause = bPause;
}