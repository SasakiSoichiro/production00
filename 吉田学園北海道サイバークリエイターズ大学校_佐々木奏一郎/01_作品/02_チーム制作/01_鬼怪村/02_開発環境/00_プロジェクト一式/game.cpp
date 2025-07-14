//=============================================================================
//
//	ゲーム処理 [game.h]
// Author : Ryuusei Hirata
//
//=============================================================================

#include "input.h"
#include "game.h"
#include "fade.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "model.h"
#include "player.h"
#include "motion.h"
#include "stage.h"
#include "item.h"
#include "block.h"
#include "time.h"
#include "billboard.h"
#include "pause.h"
#include "enemy.h"
#include "edit.h"
#include "sound.h"
#include "gimmick.h"
#include "UI.h"
#include "BloodSplatter.h"
#include "slow.h"
#include "gauge.h"
#include "KeyUI.h"
#include <time.h>
#include "ItemUI.h"
#include "stamina.h"
#include "Recovery.h"
#include "Cancellation.h"
#include "viewportwaku.h"
#include "unlock.h"
#include "pickupUI.h"
#include "buttonUI.h"
#include "objective.h"
#include "flashlight.h"
#include "explain.h"
#include "Particle.h"
#include "effect.h"
#include "bloodflash.h"

//#include "etcUI.h"

// マクロ定義
#define RAND (6) // ランダム用変数

// ゲームの状態
GAMESTATE g_gameState = GAMESTATE_NONE;	// 初期化

// 状態管理カウンター
int g_nCounterGameState = 0;

// ポーズ
bool g_bPause = false;

// エディット
bool g_bEdit = false;

bool g_bExplain = false;

//---------------
//	初期化処理
//---------------
void InitGame(void)
{
	////　BGMを鳴らす
	//PlaySound(SOUND_LABEL_BGM2);


	//　各オブジェクトの初期化処理

	// ライト
	InitLight();

	// 懐中電灯
	InitFlashLight();

	// カメラ
	InitCamera();

	// メッシュフィールド
	InitMeshfield();

	// プレイヤー
	InitPlayer();

	// アイテム
	Inititem();

	// タイム
	InitTime();

	// 敵
	InitEnemy();

	// ブロック
	InitBlock();

	// エディット
	InitEdit();

	// ギミック
	InitGimmick();

	// ビルボード
	InitBillboard();

	// アイテム収集用ビルボード
	InitPickUpUI();

	// ポーズ
	InitPause();

	// 血しぶき
	InitBloodSplatter();

	// スロー
	InitSlow();

	// 各オブジェクトの設定処理
	LoadEdit();

	InitUnlock();

	// ゲージ
	InitGauge();

	// 解除UI
	InitCancellation();

	// 鍵のUI
	InitKeyUI();

	// アイテムのUI
	InitItemUI();

	// スタミナ
	InitStamina();
	
	// 回復
	InitRecovery();

	// 敵視点のビューポートの枠
	InitViewUI();

	// ボタンのUI
	InitButtonUI();

	// 目的の表示
	InitObjective();

	//	アイテム説明
	InitExplain();

	// エフェクト
	InitEffect();

	// パーティクル
	InitParticle();

	// 画面点滅
	InitBloodFlash();

	//InitEtcUI();

	//int a = rand() % 6 + 1;
	int a = rand() % RAND + 1;

	if (a == 1)
	{
		// 鍵の上部
		Setitem(D3DXVECTOR3(1422.6f, 1.5f, -738.7f), ITEMTYPE_ONE);
	}
	
	if (a == 2)
	{
		// 鍵の上部
		Setitem(D3DXVECTOR3(-94.6f, 1.5f, -608.8f), ITEMTYPE_ONE);
	}

	if (a == 3)
	{
		// 鍵の上部
		Setitem(D3DXVECTOR3(-1199.0f, 1.5f, 396.1f), ITEMTYPE_ONE);
	}

	if (a == 4)
	{
		// 鍵の上部
		Setitem(D3DXVECTOR3(785.7f, 1.5f, 615.6f), ITEMTYPE_ONE);
	}

	if (a == 5)
	{
		// 鍵の上部
		Setitem(D3DXVECTOR3(-94.9f, 1.5f, 480.5f), ITEMTYPE_ONE);
	}

	if (a == 6)
	{//蔵
		// 鍵の上部
		Setitem(D3DXVECTOR3(-1722.6f, 1.5f, -818.2f), ITEMTYPE_ONE);
	}

	int b = rand() % RAND + 1;

	if (b == 1)
	{
		// 鍵の下部
		Setitem(D3DXVECTOR3(1807.4f, 1.5f, 790.6f), ITEMTYPE_TWO);
	}

	if (b == 2)
	{
		// 鍵の下部
		Setitem(D3DXVECTOR3(674.0f, 1.5f, -261.1), ITEMTYPE_TWO);
	}

	if (b == 3)
	{
		// 鍵の下部
		Setitem(D3DXVECTOR3(-1049.5, 1.5f, 237.3f), ITEMTYPE_TWO);
	}

	if (b == 4)
	{
		// 鍵の下部
		Setitem(D3DXVECTOR3(-107.7, 1.5f, 498.6), ITEMTYPE_TWO);
	}

	if (b == 5)
	{
		// 鍵の下部
		Setitem(D3DXVECTOR3(-234.8, 1.5f, -492.5f), ITEMTYPE_TWO);
	}

	if (b == 6)
	{//蔵
		// 鍵の下部
		Setitem(D3DXVECTOR3(1809.9f, 1.5f, -807.0f), ITEMTYPE_TWO);
	}

	// 懐中時計
	Setitem(D3DXVECTOR3(-1500.0f, 0.0f, 700.0f), ITEMTYPE_THREE);

	// 救急箱
	Setitem(D3DXVECTOR3(792.3f, 0.0f, -789.5f), ITEMTYPE_FIVE);

	// 懐中電灯
	Setitem(D3DXVECTOR3(1625.0f, 9.0f, 100.0f), ITEMTYPE_SIX);

	// ビルボード(木)
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_0,D3DXVECTOR3(15.0f,35.0f,0.0f));

	// ビルボード(拾う)
	SetBillboard(D3DXVECTOR3(-100.0f, 75.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_1, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(-100.0f, 75.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_1, D3DXVECTOR3(2.0f, 2.0f, 0.0f));

	//// ビルボード(0/2)
	//SetBillboard(D3DXVECTOR3(-1785.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_2, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	//// ビルボード(1/2)
	//SetBillboard(D3DXVECTOR3(-1780.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_3, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	//// ビルボード(脱出可能)
	//SetBillboard(D3DXVECTOR3(-1780.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_4, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	// ビルボード(解除)
	SetBillboard(D3DXVECTOR3(-1750.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_5, D3DXVECTOR3(1.0f, 1.0f, 0.0f));

	//　
	//SetPickUpUI(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//　敵
	SetEnemy(D3DXVECTOR3(-1750.0f, 0.0f, 0.0f),0);

	// ドア
	SetGimmick(D3DXVECTOR3(-1800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 鍵のUI
	SetKeyUI(D3DXVECTOR3(960.0f, 80.0f, 0.0f), ITEMKEYUITYPE_NO5, 30.0f, 30.0f);

	// ゲージ
	SetGauge(D3DXVECTOR3(640.0f, 0.0f, 0.0f));

	// 目のUI
	InitEyeUI();

	// ボタンのUI
	SetButtonUI(D3DXVECTOR3(1030.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1090.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1150.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1090.0f, 25.0f, 0.0f), BUTTONUITYPE_BUTTON_X, 80.0f, 20.0f);

	// 目的の表示
	SetObjective(D3DXVECTOR3(20.0f, 100.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_WAKU1);
	SetObjective(D3DXVECTOR3(20.0f, 150.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_WAKU2);
	SetObjective(D3DXVECTOR3(20.0f, 100.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_CHECK);
	SetObjective(D3DXVECTOR3(145.0f, 100.0f, 0.0f), 110.0f, 15.0f, OBJECTIVETYPE_TEXT1);
	SetObjective(D3DXVECTOR3(165.0f, 150.0f, 0.0f), 130.0f, 15.0f, OBJECTIVETYPE_TEXT2);

	// 初期化処理
	g_bEdit = false;
	g_gameState = GAMESTATE_NORMAL;// 通常状態に設定
}

//---------------
//	終了処理
//---------------
void UninitGame(void)
{
	////　音楽を止める
	//StopSound();

	//　各オブジェクトの終了処理

	// ライト
	UninitLight();

	// 懐中電灯
	UninitFlashLight();

	// メッシュフィールド
	UninitMeshfield();

	// カメラ
	UninitCamera();

	// ブロック
	UninitBlock();

	// プレイヤー
	UninitPlayer();

	// 敵
	UninitEnemy();

	// アイテム
	Uninititem();

	// タイム
	UninitTime();

	// エディット
	UninitEdit();

	// ビルボード
	UninitBillboard();

	// アイテム収集用ビルボード
	UninitPickUpUI();

	// ポーズ
	UninitPause();

	// ギミック
	UninitGimmick();

	// 目のUI
	UninitEyeUI();

	// 血しぶき
	UinitBloodSplatter();

	// アンロック
	UninitUnlock();

	// ゲージ
	UinitGauge();

	// 解除UI
	UinitCancellation();

	// 鍵のUI
	UninitKeyUI();

	// アイテムのUI
	UninitItemUI();

	// スタミナ
	UninitStamina();

	// 回復
	UinitRecovery();

	// 敵視点のビューポートの枠
	UninitViewUI();

	// ボタンのUI
	UninitButtonUI();

	// 目的の表示
	UninitObjective();

	//	アイテム説明
	UninitExplain();

	UninitEffect();

	// 画面点滅
	UninitBloodFlash();

	//UninitEtcUI();
}

//---------------
//	更新処理
//---------------
void UpdateGame(void)
{
	bool isGoal = IsGoal();			// ゴールの判定

	Player* pPlayer = GetPlayer();	// プレイヤー情報取得
	EXPLAIN* pExplain = GetExplain();

	// ポーズ処理
	if (KeybordTrigger(DIK_TAB) || JoyPadTrigger(JOYKEY_START) == true)
	{// TAB
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{// g_bPauseがtrue
		UpdatePause();
	}

	// エディット処理
	if (g_bEdit == true&&KeybordTrigger(DIK_F1))
	{// F1
		g_bEdit = false;

		// ブロック初期化
		InitBlock();

		// ステージをロード
		LoadEdit();
	}

	else if (g_bEdit == false && KeybordTrigger(DIK_F1))
	{// b_Editがtrue
		g_bEdit = true;
	}
	if (g_bPause == false)
	{// b_Pauseがfalse
		if (g_bEdit == false)
		{// g_Editがfalse
			if (pExplain[0].bLook == false && pExplain[1].bLook == false && pExplain[2].bLook == false)
			{
				// ゲーム中の各オブジェクトの更新処理
# if 1		// メッシュフィールド
				UpdateMeshfield();

				// カメラ
				UpdateCamera();

				// ライト
				UpdateLight();

				// 懐中電灯
				UpdateFlashLight();

				// ブロック
				UpdateBlock();

				// プレイヤー
				UpdatePlayer();

				// 敵
				UpdateEnemy();

				// ギミック
				UpdateGimmick();

				// タイム
				UpdateTime();

				// ビルボード
				UpdateBillboard();

				// アイテム収集用ビルボード
				UpdatePickUpUI();

				// アイテム
				Updateitem();

				// 目のUI
				UpdateEyeUI();

				// 血しぶき
				UpdateBloodSplatter();

				UpdateUnlock();

				// ゲージ
				UpdateGauge();

				// 解除UI
				UpdateCancellation();

				// 鍵のUI
				UpdateKeyUI();

				// アイテムのUI
				UpdateItemUI();

				// スタミナ
				UpdateStamina();

				// 回復
				UpdateRecovery();

				// 敵視点のビューポートの枠
				UpdateViewUI();

				// ボタンのUI
				UpdateButtonUI();

				// 目的の表示
				UpdateObjective();

				UpdateEffect();

				UpdateParticle();

				// 画面点滅
				UpdateBloodFlash();

				// スロー
				UpdateSlow();
			}
			UpdateExplain();
#endif
		}
		else if (g_bEdit == true)
		{// g_Editがtrue

			// エディット中の各オブジェクトの更新処理

			// カメラ
			UpdateCamera();

			// エディット
			UpdateEdit();
		}
	}

	if (isGoal == true)
	{// ゴールがtrue
		g_gameState = GAMESTATE_END;		// ゲームを終了させる
	}

	if (pPlayer->nLife <= 0)
	{// プレイヤーが死んだとき

		// モード設定
		g_gameState = GAMESTATE_END;		// ゲームを終了させる

		// カウントを進める
		g_nCounterGameState++;
	}

	switch (g_gameState)
	{
		case GAMESTATE_NONE:				// ゲーム通常状態

			break;
		case GAMESTATE_END:					// ゲーム終了状態

		g_nCounterGameState++;

		if (g_nCounterGameState >= 30)
		{// 30Fたったら
			g_gameState = GAMESTATE_NONE;	// 何もしていない
			SetFade(MODE_RESULT);			// リザルト画面に遷移
			g_nCounterGameState = 0;		// 状態カウンター初期化
		}
		break;
	}
}

//---------------
//	描画処理
//---------------
void DrawGame(int nIdx)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	EXPLAIN* pExplain = GetExplain();

	// FOGの設定
	SetupVertexFog(D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.08f);

	//　各オブジェクトの描画処理

	// メッシュフィールド
	DrawMeshfield();

	// ブロック
	DrawBlock();

	// アイテム
	Drawitem();

	switch (nIdx)
	{
	case 0:

		// 敵
		DrawEnemy();

		// アイテム収集用ビルボード
		DrawPickUpUI();

		break;

	case 1:
		// プレイヤー
		DrawPlayer();
		break;

	default:
		break;
	}
	////　メッシュフィールド
	//DrawMeshfield();

	////　ブロック
	//DrawBlock();

	////　アイテム
	//Drawitem();

	//　プレイヤー
	//DrawPlayer();

	////　敵
	//DrawEnemy();

	// ギミック
	DrawGimmick();

	// FOGを消す
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// スロー
	DrawSlow();

	// 画面点滅
	DrawBloodFlash();

	// 回復
	DrawRecovery();

	// スタミナ
	DrawStamina();

	// ビルボード
	DrawBillboard();

	// 血しぶき
	DrawBloodSplatter();

	// タイム
	DrawTime();

	// 目のUI
	DrawEyeUI();

	DrawUnlock();

	// ゲージ
	DrawGauge();

	// 解除UI
	DrawCancellation();

	// 鍵のUI
	DrawKeyUI();

	// アイテムのUI
	DrawItemUI();

	// 敵視点のビューポートの枠
	DrawViewUI();

	// ボタンのUI
	DrawButtonUI();

	// 目的の表示
	DrawObjective();

	DrawEffect();
	//DrawEtcUI();

	if (pExplain[0].bLook == true || pExplain[1].bLook == true || pExplain[2].bLook == true)
	{
		DrawExplain();
	}

	// FOGを戻す
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (g_bPause == true)
	{//　g_Pauseがtrue

		// ポーズ
		DrawPause();
	}
	if (g_bEdit == true)
	{//　g_bEditがtrue

		// エディット
		DrawEdit();
	}
}

//----------------------
//	ポーズのbool処理
//----------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//------------------
// ゲーム状態の設定
//------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//------------------------
// エディットの情報の取得
//------------------------
bool GetEditState(void)
{
	return g_bEdit;
}