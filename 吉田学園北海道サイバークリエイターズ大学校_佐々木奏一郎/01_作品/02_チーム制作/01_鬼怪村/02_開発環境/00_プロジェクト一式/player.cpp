//==========================================
//		プレイヤー		Player.cpp
//			ryuusei hirata
//=========================================

// インクルードファイル
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "block.h"
#include "meshwall.h"
#include "gimmick.h"
#include "fade.h"
#include "sound.h"
#include "BloodSplatter.h"
#include "slow.h"
#include "item.h"
#include "enemy.h"

//グローバル変数宣言
Player g_player[MAX_PLAYER];
Motion LoadMotion[2];
D3DXVECTOR3 g_Offpos[2];
int g_nIdxShadow;
int g_nCntPlayerState;
int g_nCntStop;
int g_nStateCnt;
int g_nCounterState;
bool bLanding, bOldLanding;
int OldType;

//========================
//プレイヤーの初期化処理
//========================
void InitPlayer(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//各種変数の初期化
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_player[nCnt].pos = D3DXVECTOR3(1750.0f, 100.0f, 100.0f);
		g_player[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		g_player[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].nLife = 3;
		g_player[nCnt].nStamina = 400;
		g_player[nCnt].pState = PLAYERSTATE_NORMAL;
		g_player[nCnt].bEye = false;
		g_player[nCnt].bAttack = false;
		g_player[nCnt].bCaught = false;
		g_nCounterState = 0;
		g_nCntPlayerState = 0;
		g_nStateCnt = 0;
		g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
		bLanding = true;
		ReadScriptPlayer(nCnt);
	}

	g_Offpos[0] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Offpos[1] = D3DXVECTOR3(0.0f, 60.0f, 0.0f);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_player[nCnt].Offpos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		g_player[nCnt].motion = LoadMotion[0];
		g_player[nCnt].motion.nNumKey = 0;
		g_player[nCnt].motion.nCntMotion = 0;

		for (int i = 0; i < g_player[nCnt].motion.nNumModel; i++)
		{
			g_player[nCnt].motion.aModel[i].posFirst = g_player[nCnt].motion.aModel[i].pos;
			g_player[nCnt].motion.aModel[i].rotFirst = g_player[nCnt].motion.aModel[i].rot;
		}

	}
	//g_nIdxShadow = SetShadow(g_player.pos, g_player.rot, D3DXVECTOR3(10.0f, 1.0f, 10.0f));

}
//========================
//プレイヤーの終了処理
//========================
void UninitPlayer(void)
{
	//音楽(SE)を止める
	//StopSound();

	for (int nCntType = 0; nCntType < 2; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < LoadMotion[nCntType].nNumModel; nCntModel++)
		{
			//メッシュの破棄
			if (LoadMotion[nCntType].aModel[nCntModel].pMesh != NULL)
			{
				LoadMotion[nCntType].aModel[nCntModel].pMesh->Release();
				LoadMotion[nCntType].aModel[nCntModel].pMesh = NULL;

			}
		}

		for (int nCntModel = 0; nCntModel < LoadMotion[nCntType].nNumModel; nCntModel++)
		{
			//頂点バッファの解放
			if (LoadMotion[nCntType].aModel[nCntModel].pBuffMat != NULL)
			{
				LoadMotion[nCntType].aModel[nCntModel].pBuffMat->Release();
				LoadMotion[nCntType].aModel[nCntModel].pBuffMat = NULL;
			}
		}

	}
}
//========================
//プレイヤーの更新処理
//========================
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();

	Slow* pSlow = GetSlow();

	ITEM* pItem = Getitem();

	Enemy* pEnemy = GetEnemy();

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	g_nCntStop++;
	g_nStateCnt++;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++,pCamera++, pStick++)
	{
		OldType = g_player[nCnt].nType;
		g_player[nCnt].motion.motionTypeOld = g_player[nCnt].motion.motionType; // モーションの種類

	

		g_nCounterState--;
		if (g_nCounterState <= 0)
		{
			g_player[nCnt].bAttack = false;
		}
		switch (g_player[nCnt].pState)
		{
		case PLAYERSTATE_NORMAL:

			break;

		case PLAYERSTATE_DAMAGE:
		{

			g_nStateCnt++;
			

			g_player[nCnt].bCaught = false;

			if (g_nCounterState <= 0)
			{
				g_player[nCnt].motion.motionType = MOTIONTYPE_DAMAGE;
				
				if (bLanding == true)
				{
					g_player[nCnt].pState = PLAYERSTATE_NORMAL;
				}
				g_nStateCnt = 0;
			}
			break;
		}

		case PLAYERSTATE_MOVE:
			g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
			break;

		case PLAYERSTATE_DASH:
			g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
			break;

		case MOTIONTYPE_DEATH:
			g_player[nCnt].motion.motionType = MOTIONTYPE_DEATH;
			break;

		case PLAYERSTATE_BREATH:
			g_nCntPlayerState++;
			if (g_nCntPlayerState >= 60)
			{
				g_player[nCnt].pState = PLAYERSTATE_NORMAL;
				g_nCntPlayerState = 0;
			}
			break;
		}

		switch (g_player[nCnt].motion.motionType)
		{
		case MOTIONTYPE_NEUTRAL:
			break;

		case MOTIONTYPE_MOVE:
			break;

		case MOTIONTYPE_RUN:
			break;

		case MOTIONTYPE_DAMAGE:
			break;

		case MOTIONTYPE_DEATH:
			break;

		case MOTIONTYPE_BREATH:
			break;
		}

		if (g_player[nCnt].bCaught == true)
		{
			//敵とプレイヤーの距離の差
			//D3DXVECTOR3 diff = pCamera[0].posR - pEnemy->pos;
			D3DXVECTOR3 diff = pCamera[0].posR - pEnemy->pos;

			float fAngle = atan2f(diff.x, diff.z);

			pCamera[0].rotDest.y = fAngle;

			//Dest公式だんだん目的に近づける
			pCamera[0].rot.y += (pCamera[0].rotDest.y - pCamera[0].rot.y) * 0.05f;
		}

		g_player[nCnt].posOld = g_player[nCnt].pos;

		// 重力加算
		g_player[nCnt].move.y -= GRAVI;

		//捕まってないとき
		if (g_player[nCnt].bCaught == false)
		{
			//g_player[nCnt].nCountA++;	// インクリメント

			//if (g_player[nCnt].nCountA > 180)	// 60より大きかったら
			//{
			//	PlaySound(SOUND_LABEL_SE5);		// 足音を鳴らす
			//	g_player[nCnt].nCountA = 0;		// 0に戻す
			//}
			//else if (GetKeyboardPress(DIK_W) == false)
			//{
			//	StopSound(SOUND_LABEL_SE5);
			//}

			// プレイヤーの移動
			if (GetKeyboardPress(DIK_A) == true)
			{// Aキーが押された
				if (GetKeyboardPress(DIK_W) == true)
				{// 左上
					g_player[nCnt].pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;


				}
				else if (GetKeyboardPress(DIK_S) == true)
				{// 左下

					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
					g_player[nCnt].pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;

				}
				else
				{// 左
					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
					g_player[nCnt].pos.x -= cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
					g_player[nCnt].pos.z += sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;

				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{// Dキーが押された
				if (GetKeyboardPress(DIK_W) == true)
				{// 右上
					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
					g_player[nCnt].pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;


				}
				else if (GetKeyboardPress(DIK_S) == true)
				{// 右下
					g_player[nCnt].pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;

				}
				else
				{// 右
					g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
					g_player[nCnt].pos.x += cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
					g_player[nCnt].pos.z -= sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;

				}
			}
			else if ((GetKeyboardPress(DIK_W) == true && GetKeyboardPress(DIK_LSHIFT) == true) && g_player[nCnt].nStamina > 0)
			{// Wキーが押された
				//ダッシュ
				g_player[nCnt].pState = PLAYERSTATE_DASH;
				//g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
				g_player[nCnt].pos.x -= sinf(pCamera->rot.y) * 4.0f;
				g_player[nCnt].pos.z -= cosf(pCamera->rot.y) * 4.0f;
				g_player[nCnt].rotDest.y = pCamera->rot.y;
			}
			else if(GetKeyboardPress(DIK_W) == true && GetKeyboardPress(DIK_LSHIFT) == false)
			{// 前
				g_player[nCnt].pState = PLAYERSTATE_MOVE;
				//g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
				g_player[nCnt].pos.x -= sinf(pCamera->rot.y) * 2.0f;
				g_player[nCnt].pos.z -= cosf(pCamera->rot.y) * 2.0f;
				g_player[nCnt].rotDest.y = pCamera->rot.y;
			}
			else if (GetKeyboardPress(DIK_W) == true && g_player[nCnt].nStamina < 0)
			{// 前
				g_player[nCnt].pState = PLAYERSTATE_MOVE;
				//g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
				g_player[nCnt].pos.x -= sinf(pCamera->rot.y) * 2.0f;
				g_player[nCnt].pos.z -= cosf(pCamera->rot.y) * 2.0f;
				g_player[nCnt].rotDest.y = pCamera->rot.y;
			}
			else if(GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_LSHIFT) == true)
			{
				g_player[nCnt].pState = PLAYERSTATE_MOVE;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{// Sキーが押された
				g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
				g_player[nCnt].pState = PLAYERSTATE_MOVE;
				g_player[nCnt].pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 2.0f;
				g_player[nCnt].pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 2.0f;
				g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;
			}
			//else if (GetKeyboardPress(DIK_W) == false)
			//{
			//	StopSound(SOUND_LABEL_SE5);
			//}
			else
			{
				if (g_player[nCnt].motion.motionType == MOTIONTYPE_MOVE)
				{
					g_player[nCnt].motion.motionType = MOTIONTYPE_NEUTRAL;
				}
				//g_player[nCnt].pState = PLAYERSTATE_NORMAL;
			}

			if (g_player[nCnt].rotDest.y - g_player[nCnt].rot.y > D3DX_PI)
			{
				g_player[nCnt].rot.y = g_player[nCnt].rot.y + (D3DX_PI * 2);
			}
			else if (g_player[nCnt].rot.y - g_player[nCnt].rotDest.y > D3DX_PI)
			{
				g_player[nCnt].rot.y = g_player[nCnt].rot.y - (D3DX_PI * 2);
			}
		}

		g_player[nCnt].move.x += (0.0f - g_player[nCnt].move.x) * 0.05f;
		g_player[nCnt].move.z += (0.0f - g_player[nCnt].move.z) * 0.05f;


		g_player[nCnt].pos += g_player[nCnt].move;

		float SposX = g_player[nCnt].motion.aModel[15].mtxWorld._41 + (g_player[nCnt].SwordmtxWorld._41 - g_player[nCnt].motion.aModel[15].mtxWorld._41) * 0.5f;
		float SposY = g_player[nCnt].motion.aModel[15].mtxWorld._42 + (g_player[nCnt].SwordmtxWorld._42 - g_player[nCnt].motion.aModel[15].mtxWorld._42) * 0.5f;
		float SposZ = g_player[nCnt].motion.aModel[15].mtxWorld._43 + (g_player[nCnt].SwordmtxWorld._43 - g_player[nCnt].motion.aModel[15].mtxWorld._43) * 0.5f;

		if (g_player[nCnt].pos.y < 0.0f)
		{
			bLanding = true;
			//g_player[nCnt].pState = PLAYERSTATE_NORMAL;
			g_player[nCnt].pos.y = 0.0f;
		}

		//捕まってないとき
		if (g_player[nCnt].bCaught == false)
		{
			g_player[nCnt].nCountA++;			// インクリメント

			if (g_player[nCnt].nCountA > 180)	// 180より大きかったら
			{
				PlaySound(SOUND_LABEL_SE5);		// SE(足音)を鳴らす
				g_player[nCnt].nCountA = 0;		// 0に戻す
			}

			// 左スティック移動
			if (GetJoyStick(nCnt) == true)
			{
				if (pStick->Gamepad.sThumbLX > 10922)
				{
					if (pStick->Gamepad.sThumbLY > 10922)
					{// 上移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= sinf(pCamera[nCnt].rot.y + D3DX_PI * 0.25f) * 2.0f;
						g_player[nCnt].pos.z -= cosf(pCamera[nCnt].rot.y + D3DX_PI * 0.25f) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera[nCnt].rot.y;

						if (GetJoypadPress(JOYKEY_LB) == true && g_player[nCnt].nStamina > 0 || GetJoypadPress(JOYKEY_RB) == true && g_player[nCnt].nStamina > 0)
						{// ダッシュ
							g_player[nCnt].pState = PLAYERSTATE_DASH;
							g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
							g_player[nCnt].pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 2.0f;
							g_player[nCnt].pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 2.0f;
							g_player[nCnt].rotDest.y = pCamera->rot.y;
						}
					}
					else if (pStick->Gamepad.sThumbLY < -10922)
					{// 下移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
						g_player[nCnt].pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;

					}
					else
					{// 右移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x += cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
						g_player[nCnt].pos.z -= sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;

					}
				}
				else if (pStick->Gamepad.sThumbLX < -10922)
				{
					if (pStick->Gamepad.sThumbLY > 10922)
					{// 上移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= sinf(pCamera[nCnt].rot.y - D3DX_PI * 0.25f) * 2.0f;
						g_player[nCnt].pos.z -= cosf(pCamera[nCnt].rot.y - D3DX_PI * 0.25f) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera[nCnt].rot.y;

						if (GetJoypadPress(JOYKEY_LB) == true && g_player[nCnt].nStamina > 0 || GetJoypadPress(JOYKEY_RB) == true && g_player[nCnt].nStamina > 0)
						{// ダッシュ
							g_player[nCnt].pState = PLAYERSTATE_DASH;
							g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
							g_player[nCnt].pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * 2.0f;
							g_player[nCnt].pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * 2.0f;
							g_player[nCnt].rotDest.y = pCamera->rot.y;
						}
					}
					else if (pStick->Gamepad.sThumbLY < -10922)
					{// 下移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
						g_player[nCnt].pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;

					}
					else
					{// 左移動
						g_player[nCnt].motion.motionType = MOTIONTYPE_MOVE;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
						g_player[nCnt].pos.z += sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;

					}
				}
				else if (pStick->Gamepad.sThumbLY > 10922 && (GetJoypadPress(JOYKEY_LB) == true && g_player[nCnt].nStamina > 0 || GetJoypadPress(JOYKEY_RB) == true && g_player[nCnt].nStamina > 0))
				{

					g_player[nCnt].pState = PLAYERSTATE_DASH;
					g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
					g_player[nCnt].pos.x -= sinf(pCamera->rot.y) * 5.0f;
					g_player[nCnt].pos.z -= cosf(pCamera->rot.y) * 5.0f;
					g_player[nCnt].rotDest.y = pCamera->rot.y;
				}
				else if (pStick->Gamepad.sThumbLY > 10922 && (GetJoypadPress(JOYKEY_LB) == false && g_player[nCnt].nStamina > 0 || GetJoypadPress(JOYKEY_RB) == false))
				{// 上移動
					g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
					g_player[nCnt].pos.x -= sinf(pCamera[nCnt].rot.y) * 2.0f;
					g_player[nCnt].pos.z -= cosf(pCamera[nCnt].rot.y) * 2.0f;
					g_player[nCnt].rotDest.y = pCamera[nCnt].rot.y;
				}
				else if (pStick->Gamepad.sThumbLY > 10922 && (GetJoypadPress(JOYKEY_LB) == false && g_player[nCnt].nStamina < 0 || GetJoypadPress(JOYKEY_RB) == false))
				{// 上移動
				g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
				g_player[nCnt].pState = PLAYERSTATE_MOVE;
				g_player[nCnt].pos.x -= sinf(pCamera[nCnt].rot.y) * 2.0f;
				g_player[nCnt].pos.z -= cosf(pCamera[nCnt].rot.y) * 2.0f;
				g_player[nCnt].rotDest.y = pCamera[nCnt].rot.y;
				}
				else if ((pStick->Gamepad.sThumbLY < 10922 && pStick->Gamepad.sThumbLY > -10922) && (GetJoypadPress(JOYKEY_LB) == false && g_player[nCnt].nStamina > 0 || GetJoypadPress(JOYKEY_RB) == false))
				{
					g_player[nCnt].pState = PLAYERSTATE_MOVE;
				}
			
				else if (pStick->Gamepad.sThumbLY < -10922)
				{
						g_player[nCnt].motion.motionType = MOTIONTYPE_RUN;
						g_player[nCnt].pState = PLAYERSTATE_MOVE;
						g_player[nCnt].pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 2.0f;
						g_player[nCnt].pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 2.0f;
						g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;
				}
			}
			else if (pStick->Gamepad.sThumbLY < -10922 == false)
			{
				g_player[nCnt].nCountA--;
				if (g_player[nCnt].nCountA < 180)	// 180より小さかったら
				{
					StopSound(SOUND_LABEL_SE5);		// SE(足音)を止める
					g_player[nCnt].nCountA = 0;		// 0に戻す
				}
			}
		}

		//g_player[nCnt].rot.y += (g_player[nCnt].rotDest.y - g_player[nCnt].rot.y) * 0.2f;
		
		//カメラとプレイヤー
		g_player[nCnt].rot.y = pCamera[0].rot.y;

		// ブロックの当たり判定
		CollisionBlock(&g_player[nCnt].pos, &g_player[nCnt].posOld);

		// ギミックの当たり判定
		CollisionGimmick(&g_player[nCnt].pos, &g_player[nCnt].posOld);

		//CollisionWall(&g_player[nCnt].pos, &g_player[nCnt].posOld);
		//CollisionCyrynder();
		//SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player[nCnt].pos.x, 1.0f, g_player[nCnt].pos.z), g_player[nCnt].pos.y);
		bOldLanding = bLanding;
		UpdateMotion();
	}
}
//========================
//プレイヤーの描画処理
//========================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	int nCnt = 0;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player[nCnt].mtxWorld);
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].rot.y, g_player[nCnt].rot.x, g_player[nCnt].rot.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player[nCnt].pos.x, g_player[nCnt].pos.y, g_player[nCnt].pos.z);
		D3DXMatrixMultiply(&g_player[nCnt].mtxWorld, &g_player[nCnt].mtxWorld, &mtxTrans);

		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].mtxWorld);

		pDevice->GetMaterial(&matDef);
		//全モデル（パーツ）の描画
		for (int nCntModel = 0; nCntModel < g_player[nCnt].motion.nNumModel; nCntModel++)
		{

			//計算用マトリックス
			D3DXMATRIX mtxRotModel, mtxTransModel;
			D3DXMATRIX mtxParent;//親のマトリックス

			//パーツのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_player[nCnt].motion.aModel[nCntModel].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player[nCnt].motion.aModel[nCntModel].rot.y, g_player[nCnt].motion.aModel[nCntModel].rot.x, g_player[nCnt].motion.aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player[nCnt].motion.aModel[nCntModel].mtxWorld, &g_player[nCnt].motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

			//位置を反映
			D3DXMatrixTranslation(&mtxTransModel, g_player[nCnt].motion.aModel[nCntModel].pos.x, g_player[nCnt].motion.aModel[nCntModel].pos.y, g_player[nCnt].motion.aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player[nCnt].motion.aModel[nCntModel].mtxWorld, &g_player[nCnt].motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

			//パーツの「親のマトリックス」を設定
			if (g_player[nCnt].motion.aModel[nCntModel].nIdxModelParent != -1)
			{//親モデルがある場合
				mtxParent = g_player[nCnt].motion.aModel[g_player[nCnt].motion.aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player[nCnt].mtxWorld;
			}

			//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
			D3DXMatrixMultiply(&g_player[nCnt].motion.aModel[nCntModel].mtxWorld,
				&g_player[nCnt].motion.aModel[nCntModel].mtxWorld,
				&mtxParent);
			//パーツのワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_player[nCnt].motion.aModel[nCntModel].mtxWorld);


			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_player[nCnt].motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCnt].motion.aModel[nCntModel].dwNumMat; nCntMat++)
			{

				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_player[nCnt].motion.aModel[nCntModel].apTexture[nCntMat]);

				//モデル（パーツ）の描画
				g_player[nCnt].motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

			}
			//nCnt++;
			//if (nCnt == 15)
			//{
				//SetMatrix();
			//}
		}
		pDevice->SetMaterial(&matDef);
	}
	
}
//========================
//プレイヤーのマトリックス
//========================
void SetMatrix(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルの保存用
	D3DXMATRIX mtxParent; // 親のマトリックス

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player[nCnt].SwordmtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCnt].motion.aModel[15].rot.y, g_player[nCnt].motion.aModel[15].rot.x, g_player[nCnt].motion.aModel[15].rot.z);
		D3DXMatrixMultiply(&g_player[nCnt].SwordmtxWorld, &g_player[nCnt].SwordmtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player[nCnt].Offpos.x, g_player[nCnt].Offpos.y, g_player[nCnt].Offpos.z);
		D3DXMatrixMultiply(&g_player[nCnt].SwordmtxWorld, &g_player[nCnt].SwordmtxWorld, &mtxTrans);

		mtxParent = g_player[nCnt].motion.aModel[15].mtxWorld;

		// 算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
		D3DXMatrixMultiply(&g_player[nCnt].SwordmtxWorld,
			&g_player[nCnt].SwordmtxWorld,
			&mtxParent);

		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].SwordmtxWorld);
	}
}
//===========================
//プレイヤーのモーション処理
//===========================
void SetMotion(int nType)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		g_player[nCnt].motion = LoadMotion[nType];
	}
}
//========================
//プレイヤーの取得
//========================
Player* GetPlayer(void)
{
	return &g_player[0];
}
//=============================
//プレイヤーのファイル読み込み
//=============================
void ReadScriptPlayer(int nType)
{
	FILE* pFile;
	switch (nType)
	{
	case 0:
		pFile = fopen("data\\MOTION\\PlayerMotion.txt", "r");
		break;

	case 1:
		pFile = fopen("data\\MOTION\\motion06.txt", "r");
		break;

	default:
		pFile = NULL;
		break;
	}

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;

	if (pFile != NULL)
	{
		char aString[MAX_WORD]; // 文字数を格納

		while (1)
		{
			// ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);


			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (1)
				{
					// ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &str[0]);
						fscanf(pFile, "%d", &LoadMotion[nType].nNumModel);
						while (nCntModel < LoadMotion[nType].nNumModel)
						{
							// ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &FileName[nCntModel][0]);

								// xファイルの読み込み
								D3DXLoadMeshFromX(FileName[nCntModel],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&LoadMotion[nType].aModel[nCntModel].pBuffMat,
									NULL,
									&LoadMotion[nType].aModel[nCntModel].dwNumMat,
									&LoadMotion[nType].aModel[nCntModel].pMesh);

								nCntModel++;
							}
						}
					}

					if (strcmp(aString, "CHARACTERSET") == 0)
					{
						while (1)
						{
							// ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &LoadMotion[nType].nNumModel);

							}
							while (nCntParts < LoadMotion[nType].nNumModel)
							{
								// ファイルを読み込む
								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(aString, "PARTSSET") == 0)
								{
									while (1)
									{
										// ファイルを読み込む
										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(aString, "INDEX") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nIdx);
										}
										else if (strcmp(aString, "PARENT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &LoadMotion[nType].aModel[nIdx].nIdxModelParent);

										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.z);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.z);

										}
										else if (strcmp(aString, "END_PARTSSET") == 0)
										{
											nCntParts++;
											break;
										}
									}

								}

							}
							if (strcmp(aString, "END_CHARACTERSET") == 0)
							{
								break;
							}

						}
					}
					if (strcmp(aString, "MOTIONSET") == 0)
					{
						while (1)
						{
							// ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &nBool);
								if (nBool == 0)
								{
									LoadMotion[nType].aMotionInfo[nCntMotion].bLoop = false;
								}
								else
								{
									LoadMotion[nType].aMotionInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &LoadMotion[nType].aMotionInfo[nCntMotion].nNumKey);

								while (nCntKey < LoadMotion[nType].aMotionInfo[nCntMotion].nNumKey)
								{
									// ファイルを読み込む
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(aString, "KEYSET") == 0)
									{
										nCntParts = 0;
										while (1)
										{
											// ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "FRAME") == 0)
											{
												fscanf(pFile, "%s", &str[0]);
												fscanf(pFile, "%d", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
												break;
											}
										}

										while (1)
										{
											// ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "KEY") == 0)
											{
												while (1)
												{
													// ファイルを読み込む
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(aString, "POS") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
													}
													if (strcmp(aString, "END_KEY") == 0)
													{
														nCntParts++;
														break;
													}
												}
											}
											if (strcmp(aString, "END_KEYSET") == 0)
											{
												nCntKey++;
												break;
											}

										}
									}


								}

							}

							if (strcmp(aString, "END_MOTIONSET") == 0)
							{
								nCntMotion++;
								nCntKey = 0;
								break;
							}
						}
					}
					if (strcmp(aString, "END_SCRIPT") == 0)
					{
						break;
					}
				}
				break;

			}
		}
	}
	for (int nCnt = 0; nCnt < LoadMotion[nType].nNumModel; nCnt++)
	{
		LoadMotion[nType].aModel[nCnt].posFirst = LoadMotion[nType].aModel[nCnt].pos;
		LoadMotion[nType].aModel[nCnt].rotFirst = LoadMotion[nType].aModel[nCnt].rot;
	}
}
//=======================
//プレイヤーのヒット処理
//=======================
void HitPlayer(int nDamege)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{

		if (g_player[nCnt].nLife == 3)
		{
			g_nCounterState = 180;

			g_player[nCnt].pState = PLAYERSTATE_DAMAGE;
			g_player[nCnt].nLife -= nDamege;
			g_player[nCnt].bAttack = true;
			SetBloodSplatter(90, BLOODTYPE_SMALL, UI_NONE);
			SetBloodSplatter(90, BLOODTYPE_RED, UI_IN);
			
			break;
		}
		else if (g_player[nCnt].nLife == 2)
		{
			g_nCounterState = 180;

			g_player[nCnt].pState = PLAYERSTATE_DAMAGE;
			g_player[nCnt].nLife -= nDamege;
			g_player[nCnt].bAttack = true;
			SetBloodSplatter(90, BLOODTYPE_BIG, UI_NONE);
			SetBloodSplatter(90, BLOODTYPE_RED, UI_IN);
			
			break;
		}
		else if (g_player[nCnt].nLife == 1)
		{
			g_player[nCnt].bCaught = false;
			g_player[nCnt].nLife -= nDamege;
			SetFade(MODE_RESULT);
		}
	}
}