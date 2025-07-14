//=============================================================================
//
//	敵処理 [enemy.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "block.h"
#include "score.h"
#include "meshwall.h"
#include "slow.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"

Enemy g_Enemy[MAX_ENEMY];
int g_nEIdxShadow;
int nCntTypeState;
int g_nNumEnemy = 0;//敵の総数
int g_nCntEnemyState = 0;
int g_nIdxEnemyShadow;
int g_nCntPos = 0;
bool bRange;
Enemy g_LoadEnemy[3];

//=============================================================================
//初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//各種変数の初期化
		g_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_Enemy[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].nLife = 360;
		g_Enemy[nCnt].nType = 0;
		g_Enemy[nCnt].bBlendMotion = false;
		g_Enemy[nCnt].bUse = false;
		g_Enemy[nCnt].nCount = 0;
	}
	bRange = false;
	nCntTypeState = 0;
	g_nNumEnemy = 0;
	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		LoadEnemy(nCntType);
		g_LoadEnemy[nCntType].nLife = 30;
		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat->GetBufferPointer();


			for (int nCntMat = 0; nCntMat < (int)g_LoadEnemy[nCntType].aModel[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャファイルが存在する
						//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_LoadEnemy[nCntType].aModel[nCntModel].apTexture[nCntMat]);
				}
			}
			g_LoadEnemy[nCntType].aModel[nCntModel].Diffuse = pMat->MatD3D.Diffuse;
			g_LoadEnemy[nCntType].aModel[nCntModel].firstDiffuse = g_LoadEnemy[nCntType].aModel[nCntModel].Diffuse;
		}

		//g_nEIdxShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);

	}
	g_LoadEnemy[0].fRad = 30.01f;
	SetMotionType(EMOTIONTYPE_MOVE, true, 10, 0);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//// 攻撃音を止める
	StopSound(SOUND_LABEL_SE6);

	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			if (g_LoadEnemy[nCntType].aModel[nCntModel].pMesh != NULL)
			{
				g_LoadEnemy[nCntType].aModel[nCntModel].pMesh->Release();
				g_LoadEnemy[nCntType].aModel[nCntModel].pMesh = NULL;

			}
		}

		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			//頂点バッファの解放
			if (g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat != NULL)
			{
				g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat->Release();
				g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat = NULL;
			}
		}

	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{

	//==========
	// 変数宣言
	//==========

	//答え格納用
	KEY k_Answer;
	float fRotX = 0.0f;
	float fRotY = 0.0f;
	float fRotZ = 0.0f;


	//計算用
	float fDiffMotionX;
	float fDiffMotionY;
	float fDiffMotionZ;

	float fRotXCurrent;
	float fRotYCurrent;
	float fRotZCurrent;

	float DiffMotionBlendX;
	float DiffMotionBlendY;
	float DiffMotionBlendZ;

	float fRotXBlend;
	float fRotYBlend;
	float fRotZBlend;

	float fDiffBlendX;
	float fDiffBlendY;
	float fDiffBlendZ;

	// プレイヤーの半径の算出用変数
	float fPRadPos = 1000.0f;

	// 敵の半径の算出用変数
	float fERadPos = 200.0f;

	// 敵の半径の算出用変数1
	float fERadPos1 = 300.0f;

	// 敵の半径の算出用変数2
	float fERadPos2 = 350.0f;

	//カメラ情報取得
	Camera* pCamera = GetCamera();
	//プレイヤー情報取得
	Player* pPlayer = GetPlayer();
	//スロー情報取得
	Slow* pSlow = GetSlow();
	//コントローラー振動の初期化
	static VibrationState vibrationState = { 0,0,0,0,0 };//初期化

	// プレやーの位置を取得
	D3DXVECTOR3 PlayerPos = pPlayer->pos;

	// 範囲計算
	float fDisX = PlayerPos.x - g_Enemy[0].pos.x;
	float fDisY = PlayerPos.y - g_Enemy[0].pos.y;
	float fDisZ = PlayerPos.z - g_Enemy[0].pos.z;

	// 二つの半径を求める
	float fRadX = fPRadPos + fERadPos;

	// 二つの半径を求める
	float fRadX1 = fPRadPos + fERadPos1;

	// 二つの半径を求める
	float fRadX2 = fPRadPos + fERadPos2;

	//敵の向き用変数
	float fAnglemove = 0.0f;

	//現在のプレイヤーと敵の距離
	float fDistanceChase = (g_Enemy[0].pos.x - pPlayer->pos.x) * (g_Enemy[0].pos.x - pPlayer->pos.x) + (g_Enemy[0].pos.y - pPlayer->pos.y) * (g_Enemy[0].pos.y - pPlayer->pos.y) + (g_Enemy[0].pos.z - pPlayer->pos.z) * (g_Enemy[0].pos.z - pPlayer->pos.z);

	//敵の視野
	float fFOV = D3DX_PI / 3.0f;

	//プレイヤーを追いかける距離
	D3DXVECTOR3 fRadChaseP(200.0f, 0.0f, 200.0f);
	D3DXVECTOR3 fRadChaseE(200.0f, 0.0f, 200.0f);

	//追いかける半径の設定
	float fRadiusChase = (fRadChaseP.x + fRadChaseE.x) * (fRadChaseP.x + fRadChaseE.x) + (fRadChaseP.y + fRadChaseE.y) * (fRadChaseP.y + fRadChaseE.y) + (fRadChaseP.z + fRadChaseE.z) * (fRadChaseP.z + fRadChaseE.z);

	//敵の視界ベクトル1
	g_Enemy[0].posVec[0].x = sinf((g_Enemy[0].rot.y + fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.x;
	g_Enemy[0].posVec[0].z = cosf((g_Enemy[0].rot.y + fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.y;

	//敵の視界ベクトル2
	g_Enemy[0].posVec[1].x = sinf((g_Enemy[0].rot.y - fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.x;
	g_Enemy[0].posVec[1].z = cosf((g_Enemy[0].rot.y - fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.y;

	D3DXVECTOR3 vec;
	float fvecCross[2];
	vec = pPlayer->pos - g_Enemy[0].pos;
	fvecCross[0] = (g_Enemy[0].posVec[0].x * vec.x) + (g_Enemy[0].posVec[0].y * vec.y) + (g_Enemy[0].posVec[0].z * vec.z);

	fvecCross[1] = (g_Enemy[0].posVec[1].x * vec.x) + (g_Enemy[0].posVec[1].y * vec.y) + (g_Enemy[0].posVec[1].z * vec.z);

	nCntTypeState++;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].nCount++;	// インクリメント

		if (g_Enemy[nCntEnemy].nCount > 60)	// 60より大きかったら
		{
			PlaySound(SOUND_LABEL_SE7);		// 足音を鳴らす
			g_Enemy[nCntEnemy].nCount = 0;	// 0に戻す
		}

		if (g_Enemy[nCntEnemy].bUse == true)
		{			
			switch (g_Enemy[nCntEnemy].State)
			{
			case ENEMYSTATE_NORMAL:
				//徘徊処理
				LoiterEnemy();

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					SetVolume(SOUND_LABEL_SE7, 3.0f);
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX1 * fRadX1))
				{
					SetVolume(SOUND_LABEL_SE7, 2.0f);
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX2 * fRadX2))
				{
					SetVolume(SOUND_LABEL_SE7, 1.0f);
				}
				else
				{
					SetVolume(SOUND_LABEL_SE7, 0.0f);
				}

				if (fDistanceChase <= fRadiusChase && fvecCross[0] > 0 && fvecCross[1] > 0)
				{//エネミーの視界内に入ったら

					bRange = true;

					//チェイス状態
					g_Enemy[0].State = ENEMYSTATE_CHASE;
					SetMotionType(EMOTIONTYPE_MOVE, true, 10, nCntEnemy);

					// BGMを鳴らす
					PlaySound(SOUND_LABEL_BGM3);

					// 走る音を鳴らす
					
					//if (g_Enemy[nCntEnemy].nCount < 60)
					//{
						StopSound(SOUND_LABEL_SE5);
					//	//g_Enemy[nCntEnemy].nCount = 0;
					//}

				}
				if (fvecCross[0] > 0 && fvecCross[1] > 0)
				{//距離関係なし
					pPlayer->bEye = true;
				}
				else
				{
					pPlayer->bEye = false;
				}

				break;

			case ENEMYSTATE_CHASE://チェイス状態

				if (fDistanceChase > fRadiusChase)
				{//視界内から外れたら

					bRange = false;

					//徘徊状態
					g_Enemy[0].State = ENEMYSTATE_NORMAL;
					SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
					pPlayer->bEye = false;

					// BGMを消す
					StopSound(SOUND_LABEL_BGM3);

					//// 走る音を消す
					//StopSound();

					// 歩く音を鳴らす


					//PlaySound(SOUND_LABEL_BGM2);
				}

				//チェイス処理
				g_Enemy[0].rotDest.y = atan2f((pPlayer->pos.x - g_Enemy[0].pos.x), (pPlayer->pos.z - g_Enemy[0].pos.z)) + D3DX_PI;
				fAnglemove = atan2f((pPlayer->pos.x - g_Enemy[0].pos.x), (pPlayer->pos.z - g_Enemy[0].pos.z));
				g_Enemy[0].move.x = sinf(fAnglemove) * 1.25f;
				g_Enemy[0].move.z = cosf(fAnglemove) * 1.25f;
				StartVibration(&vibrationState, 20,20000,20000);
				break;

			case ENEMYSTATE_DAMAGE:
				g_nCntEnemyState--;

				//g_Enemy[nCntEnemy].move.x = 0.0f;
				//g_Enemy[nCntEnemy].move.z = 0.0f;
				
				if (g_nCntEnemyState <= 0)
				{
					g_Enemy[nCntEnemy].State = ENEMYSTATE_NORMAL;
					//SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
				}

				break;
			case ENEMYSTATE_ACTION:
				g_nCntEnemyState--;
				

				//g_Enemy[nCntEnemy].move.x = 0.0f;
				//g_Enemy[nCntEnemy].move.z = 0.0f;
				if (g_nCntEnemyState >= 0)
				{
					if (g_Enemy[nCntEnemy].motionType != EMOTIONTYPE_ACTION)
					{

						SetMotionType(EMOTIONTYPE_ACTION, true, 10, nCntEnemy);
						g_Enemy[nCntEnemy].move.x = 0.0f;
						g_Enemy[nCntEnemy].move.z = 0.0f;
						StartVibration(&vibrationState, 1000, 60000, 60000);

					}
					if (g_nCntEnemyState <= 0)
					{
						g_Enemy[nCntEnemy].State = ENEMYSTATE_NORMAL;
						SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
						bRange = false;
						pPlayer->bCaught = false;
						// BGMを消す
						StopSound(SOUND_LABEL_BGM3);
					}
				}
				break;
			}


			g_Enemy[nCntEnemy].OldState = g_Enemy[nCntEnemy].State;

			//現在の位置を保存
			g_Enemy[nCntEnemy].posOld = g_Enemy[nCntEnemy].pos;

			//重力加算
			g_Enemy[nCntEnemy].move.y -= GRAVI;

			//位置を更新
			g_Enemy[nCntEnemy].pos.x += g_Enemy[nCntEnemy].move.x * pSlow->fDivi;
			g_Enemy[nCntEnemy].pos.z += g_Enemy[nCntEnemy].move.z * pSlow->fDivi;

			//SetPositionGaugeLife(g_Enemy[nCntEnemy].nIdxLife, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 40.0f, g_Enemy[nCntEnemy].pos.z));


			float fDistance = (g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x) * (g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x) + (g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y) * (g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y) + (g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z) * (g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z);
			D3DXVECTOR3 fRadP(50.0f, 0.0f, 50.0f);
			D3DXVECTOR3 fRadE(50.0f, 0.0f, 50.0f);


			float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);

			//当たり判定
			if ((fDistance <= fRadius) && pPlayer->bAttack == false)
			{
				pPlayer->bCaught = true;
				g_nCntEnemyState = 150;
				g_Enemy[nCntEnemy].State = ENEMYSTATE_ACTION;

				if (g_Enemy[nCntEnemy].motionType == EMOTIONTYPE_ACTION && g_Enemy[nCntEnemy].nKey >= 2)
				{
					if (pPlayer->pState != PLAYERSTATE_DAMAGE)
					{
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE6);
					}
				}
			}



			if (g_Enemy[nCntEnemy].rotDest.y - g_Enemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_Enemy[nCntEnemy].rot.y = g_Enemy[nCntEnemy].rot.y + (D3DX_PI * 2);
			}
			else if (g_Enemy[nCntEnemy].rot.y - g_Enemy[nCntEnemy].rotDest.y > D3DX_PI)
			{
				g_Enemy[nCntEnemy].rot.y = g_Enemy[nCntEnemy].rot.y - (D3DX_PI * 2);
			}

			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move * pSlow->fDivi;

			if (g_Enemy[nCntEnemy].pos.y < 0.0f)
			{
				g_Enemy[nCntEnemy].pos.y = 0.0f;
			}

			g_Enemy[nCntEnemy].rot.y += (g_Enemy[nCntEnemy].rotDest.y - g_Enemy[nCntEnemy].rot.y) * 0.2f;

			//CollisionWall(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posOld);

			//敵同士の当たり判定
			CollisionEnemytoEnemy(nCntEnemy);

			CollisionBlock(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posOld);

			//SetPositionShadow(g_Enemy[nCntEnemy].IdxShadow, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, 1.0f, g_Enemy[nCntEnemy].pos.z), g_Enemy[nCntEnemy].pos.y);

			//SetPositionShadow(g_nEIdxShadow, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, 0.1f, g_Enemy[nCntEnemy].pos.z));
		}

		g_Enemy[nCntEnemy].nNumKey = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].nNumKey;
		g_Enemy[nCntEnemy].nNumKeyBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].nNumKey;


		//全モデル(パーツ)の更新
		for (int nCntModel = 0; nCntModel < g_Enemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//現在のキー情報代入(ポイント
			EKEY pKey = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel];
			//次のキー情報代入(ポイント
			EKEY pKeyNext = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel];

			//相対値
			float fRateMotion = g_Enemy[nCntEnemy].nCntMotion /( (float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame * pSlow->nMulti);

			//ブレンドするフレーム
			g_Enemy[nCntEnemy].nFrameBlend = EBLEND_FRAME * pSlow->nMulti;


			//ブレンドモーション処理
			if (g_Enemy[nCntEnemy].bBlendMotion == true)
			{//bBlendがtrueだったら


				//==========
				// 変数宣言
				//==========

				// ブレンド先の情報を代入
				// 現在のキー情報代入(ポイント
				EKEY pKeyBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].aKey[nCntModel];												// 現在のキー

				// 次のキー情報代入(ポイント
				EKEY pKeyNextBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[(g_Enemy[nCntEnemy].nKeyBlend + 1) % g_Enemy[nCntEnemy].nNumKeyBlend].aKey[nCntModel];	// 次のキー

				// 相対値
				float fRateMotionBlend = g_Enemy[nCntEnemy].nCntMotionBlend / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].nFlame * pSlow->nMulti);

				// ブレンドの相対値
				float fRateBlend = g_Enemy[nCntEnemy].nCntBlend / ((float)g_Enemy[nCntEnemy].nFrameBlend*pSlow->nMulti);



				// X軸の回転
				//=============================================================================================
				fDiffMotionX = pKeyNext.fRotX - pKey.fRotX;							// 次のキーとの差分
				fRotXCurrent = pKey.fRotX + (fDiffMotionX * fRateMotion);
				DiffMotionBlendX = pKeyNextBlend.fRotX - pKeyBlend.fRotX;
				fRotXBlend = pKeyBlend.fRotX + (DiffMotionBlendX * fRateMotionBlend);
				fDiffBlendX = fRotXBlend - fRotXCurrent;								// 差分
				fRotX = fRotXCurrent + (fDiffBlendX * fRateBlend);						// 求める値
				//=============================================================================================


				// Y軸の回転
				//=============================================================================================
				fDiffMotionY = pKeyNext.fRotY - pKey.fRotY;							// 次のキーとの差分
				fRotYCurrent = pKey.fRotY + (fDiffMotionY * fRateMotion);
				DiffMotionBlendY = pKeyNextBlend.fRotY - pKeyBlend.fRotY;
				fRotYBlend = pKeyBlend.fRotY + (DiffMotionBlendY * fRateMotionBlend);
				fDiffBlendY = fRotYBlend - fRotYCurrent;								// 差分
				fRotY = fRotYCurrent + (fDiffBlendY * fRateBlend);						// 求める値
				//=============================================================================================


				// Z軸の回転
				//=============================================================================================
				fDiffMotionZ = pKeyNext.fRotZ - pKey.fRotZ;							// 次のキーとの差分
				fRotZCurrent = pKey.fRotZ + (fDiffMotionZ * fRateMotion);
				DiffMotionBlendZ = pKeyNextBlend.fRotZ - pKeyBlend.fRotZ;
				fRotZBlend = pKeyBlend.fRotZ + (DiffMotionBlendZ * fRateMotionBlend);
				fDiffBlendZ = fRotZBlend - fRotZCurrent;								// 差分
				fRotZ = fRotZCurrent + (fDiffBlendZ * fRateBlend);						// 求める値
				//=============================================================================================

			}
			else
			{//ブレンド無し

				//キー情報から位置.向きを算出
				//次のキーとの差分
				k_Answer.fPosX = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosX) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosX);
				k_Answer.fPosY = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosY) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosY);
				k_Answer.fPosZ = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosZ) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ);
				fDiffMotionX = (pKeyNext.fRotX) - (pKey.fRotX);
				fDiffMotionY = (pKeyNext.fRotY) - (pKey.fRotY);
				fDiffMotionZ = (pKeyNext.fRotZ) - (pKey.fRotZ);

				//求める値
				fRotX = pKey.fRotX + fDiffMotionX * fRateMotion;
				fRotY = pKey.fRotY + fDiffMotionY * fRateMotion;
				fRotZ = pKey.fRotZ + fDiffMotionZ * fRateMotion;

			}


			//パーツの位置.向きを設定
			//位置
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.x = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.x + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));//オフセット考慮
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.y = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.y + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.z = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.z + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));

			//向き
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.x = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.x + fRotX;//オフセット考慮
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.y = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.y + fRotY;//オフセット考慮
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.z = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.z + fRotZ;//オフセット考慮


		}


		if (g_Enemy[nCntEnemy].bBlendMotion == true)
		{//ブレンドあり
			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].bLoop == false)
			{//ループモーションじゃない場合

				if (g_Enemy[nCntEnemy].nKeyBlend + 1 != g_Enemy[nCntEnemy].nNumKeyBlend)
				{//キー総数に達していない場合

					g_Enemy[nCntEnemy].nCntMotionBlend += 1;//再生フレーム数に達したら現在のキーを1つ進める

				}
			}

			else
			{//ループモーションの場合

				g_Enemy[nCntEnemy].nCntMotionBlend += 1;//カウントモーションを1つ進める

			}

			if (g_Enemy[nCntEnemy].nCntMotionBlend >= (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].nFlame * pSlow->nMulti))
			{//フレーム数を超えたら

				//カウントモーションを0にする
				g_Enemy[nCntEnemy].nCntMotionBlend = 0;

				//現在のキーを1つ進める
				g_Enemy[nCntEnemy].nKeyBlend += 1;

				if (g_Enemy[nCntEnemy].nKeyBlend >= g_Enemy[nCntEnemy].nNumKeyBlend)
				{//キー総数に達したら

					//現在のキーを0にする
					g_Enemy[nCntEnemy].nKeyBlend = 0;
				}
			}

			//ブレンドカウントを1つ進める
			g_Enemy[nCntEnemy].nCntBlend++;


			if (g_Enemy[nCntEnemy].nCntBlend >= (g_Enemy[nCntEnemy].nFrameBlend*pSlow->nMulti))
			{//ブレンドのフレーム数に達したら

				//初期化＆通常モーションに情報を代入
				g_Enemy[nCntEnemy].nCntMotion = g_Enemy[nCntEnemy].nCntMotionBlend;
				g_Enemy[nCntEnemy].nCntBlend = 0;
				g_Enemy[nCntEnemy].motionType = g_Enemy[nCntEnemy].motionTypeBlend;
				g_Enemy[nCntEnemy].nKey = g_Enemy[nCntEnemy].nKeyBlend;
				g_Enemy[nCntEnemy].bBlendMotion = false;

			}

			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].nNumKey - 1 <= g_Enemy[nCntEnemy].nKey && g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].bLoop == false)
			{
				g_Enemy[nCntEnemy].motionType = EMOTIONTYPE_NEUTRAL;
			}
		}


		else
		{//ブレンドなし

			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].bLoop == false)
			{//ループモーションじゃない場合

				if (g_Enemy[nCntEnemy].nKey + 1 != g_Enemy[nCntEnemy].nNumKey)
				{//キー総数に達していない場合

					g_Enemy[nCntEnemy].nCntMotion++;//モーションカウントを1つ進める

				}
			}


			else
			{//ループモーションの場合

				g_Enemy[nCntEnemy].nCntMotion++;//モーションカウントを1つ進める

			}



			if (g_Enemy[nCntEnemy].nCntMotion >= (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame * pSlow->nMulti))
			{//フレーム数を超えたら

				//カウントモーションを0にする
				g_Enemy[nCntEnemy].nCntMotion = 0;

				//現在のキーを1つ進める
				g_Enemy[nCntEnemy].nKey += 1;

				if (g_Enemy[nCntEnemy].nKey >= g_Enemy[nCntEnemy].nNumKey)
				{//キー総数に達したら

					//現在のキーを0にする
					g_Enemy[nCntEnemy].nKey = 0;

				}
			}
		}
	}
	UpdateVibration(&vibrationState);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	Camera* pCamera = GetCamera();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);
			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			pDevice->GetMaterial(&matDef);

			//全モデル（パーツ）の描画
			for (int nCntModel = 0; nCntModel < g_Enemy[nCntEnemy].nNumModel; nCntModel++)
			{
				//計算用マトリックス
				D3DXMATRIX mtxRotModel, mtxTransModel;
				D3DXMATRIX mtxParent;//親のマトリックス

				//パーツのワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntEnemy].aModel[nCntModel].rot.y, g_Enemy[nCntEnemy].aModel[nCntModel].rot.x, g_Enemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntEnemy].aModel[nCntModel].pos.x, g_Enemy[nCntEnemy].aModel[nCntModel].pos.y, g_Enemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//パーツの「親のマトリックス」を設定
				if (g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{//親モデルがある場合
					mtxParent = g_Enemy[nCntEnemy].aModel[g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[nCntEnemy].mtxWorld;
				}

				//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&mtxParent);
				//パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);


				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].aModel[nCntModel].dwNumMat; nCntMat++)
				{

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_Enemy[nCntEnemy].aModel[nCntModel].apTexture[nCntMat]);

					//モデル（パーツ）の描画
					g_Enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);

				}
			}
			pDevice->SetMaterial(&matDef);
		}

	}

}

//=============================================================================
// 設定処理
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == false)
		{
			g_Enemy[nCnt] = g_LoadEnemy[nType];
			g_Enemy[nCnt].pos = pos;
			//g_Enemy[nCnt].nIdxLife = SetGaugeLife(g_Enemy[nCnt].pos, g_Enemy[nCnt].rot, g_Enemy[nCnt].nLife);
			//g_Enemy[nCnt].IdxShadow = SetShadow(pos, g_Enemy[nCnt].rot, D3DXVECTOR3(10.0f, 1.0f, 10.0f));
			g_Enemy[nCnt].bUse = true;
			g_nNumEnemy++;//敵の総数
			break;
		}
	}
}

//=============================================================================
// 敵の読込処理
//=============================================================================
void LoadEnemy(int nType)
{

	FILE* pFile;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	char str[MAX_WORD];

	pFile = fopen("data\\MOTION\\EnemyMotion1.txt", "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納

		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);


			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &str[0]);
						fscanf(pFile, "%d", &g_LoadEnemy[nType].nNumModel);
						while (nCntModel < g_LoadEnemy[nType].nNumModel)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &aString[0]);

								const char* MODEL_FILE = {};
								MODEL_FILE = aString;

								//xファイルの読み込み
								D3DXLoadMeshFromX(MODEL_FILE,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_LoadEnemy[nType].aModel[nCntModel].pBuffMat,
									NULL,
									&g_LoadEnemy[nType].aModel[nCntModel].dwNumMat,
									&g_LoadEnemy[nType].aModel[nCntModel].pMesh);

								if (nCntModel < g_LoadEnemy[nType].nNumModel)
								{
									nCntModel++;
								}
							}
						}
					}

					if (strcmp(aString, "CHARACTERSET") == 0)
					{
						while (1)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &g_LoadEnemy[nType].nNumModel);

							}
							while (nCntParts < g_LoadEnemy[nType].nNumModel)
							{
								//ファイルを読み込む
								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(aString, "PARTSSET") == 0)
								{
									while (1)
									{
										//ファイルを読み込む
										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(aString, "INDEX") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nIdx);
										}
										else if (strcmp(aString, "PARENT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &g_LoadEnemy[nType].aModel[nIdx].nIdxModelParent);

										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.z);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.z);

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
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &nBool);
								if (nBool == 0)
								{
									g_LoadEnemy[nType].aMotionInfo[nCntMotion].bLoop = false;
								}
								else
								{
									g_LoadEnemy[nType].aMotionInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].nNumKey);

								while (nCntKey < g_LoadEnemy[nType].aMotionInfo[nCntMotion].nNumKey)
								{
									//ファイルを読み込む
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(aString, "KEYSET") == 0)
									{
										nCntParts = 0;
										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "FRAME") == 0)
											{
												fscanf(pFile, "%s", &str[0]);
												fscanf(pFile, "%d", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
												break;
											}
										}

										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "KEY") == 0)
											{
												while (1)
												{
													//ファイルを読み込む
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(aString, "POS") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
	for (int nCnt = 0; nCnt < g_LoadEnemy[nType].nNumModel; nCnt++)
	{
		g_LoadEnemy[nType].aModel[nCnt].posFirst = g_LoadEnemy[nType].aModel[nCnt].pos;
		g_LoadEnemy[nType].aModel[nCnt].rotFirst = g_LoadEnemy[nType].aModel[nCnt].rot;
	}

}

//=============================================================================
// 敵の当たり判定
//=============================================================================
void CollisionEnemy(void)
{
	Player* pPlayer = GetPlayer();
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			float mtxX = (pPlayer->SwordmtxWorld._41 - pPlayer->motion.aModel[15].mtxWorld._41);
			float mtxY = (pPlayer->SwordmtxWorld._42 - pPlayer->motion.aModel[15].mtxWorld._42);
			float mtxZ = (pPlayer->SwordmtxWorld._43 - pPlayer->motion.aModel[15].mtxWorld._43);
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				D3DXVECTOR3 pos;
				pos.x = pPlayer->motion.aModel[15].mtxWorld._41 + mtxX * 0.25f * nCnt;
				pos.y = pPlayer->motion.aModel[15].mtxWorld._42 + mtxY * 0.25f * nCnt;
				pos.z = pPlayer->motion.aModel[15].mtxWorld._43 + mtxZ * 0.25f * nCnt;

				float DistanceX = g_Enemy[nCntEnemy].pos.x - pos.x;
				float DistanceY = g_Enemy[nCntEnemy].pos.y - pos.y;
				float DistanceZ = g_Enemy[nCntEnemy].pos.z - pos.z;

				float fDistance = (DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ);

				float fPlayerRad = 20.0f;

				float fRad = g_Enemy[nCntEnemy].fRad + fPlayerRad;
				fRad = fRad * fRad;

				if (fDistance <= fRad && g_Enemy[nCntEnemy].State != ENEMYSTATE_DAMAGE)
				{

				}
			}
		}
	}
}

//=============================================================================
// 敵のヒット処理
//=============================================================================
void HitEnemy(int nCnt, int nDamage)
{
	g_Enemy[nCnt].nLife -= nDamage;

	if (g_Enemy[nCnt].nLife <= 0 && g_Enemy[nCnt].bUse == true)
	{
		//爆発の設定
		g_Enemy[nCnt].bUse = false;
		//EraseGaugeLife(g_Enemy[nCnt].nIdxLife);
		//EraseShadow(g_Enemy[nCnt].IdxShadow);
		AddScore(150);
		g_nNumEnemy--;//敵の総数カウントダウン
	}
	else
	{
		g_Enemy[nCnt].State = ENEMYSTATE_DAMAGE;
		g_Enemy[nCnt].move.x = sinf(D3DX_PI) * 80.0f;
		g_Enemy[nCnt].move.z = cosf(D3DX_PI) * 80.0f;
		g_nCntEnemyState = 240;
	}

}

//=============================================================================
//敵同士の当たり判定
//=============================================================================
void CollisionEnemytoEnemy(int nCnt)
{


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_Enemy[nCntEnemy].bUse == true && nCnt != nCntEnemy)
		{
			D3DXVECTOR3 pos;


			float fDistance = (g_Enemy[nCntEnemy].pos.x - g_Enemy[nCnt].pos.x) * (g_Enemy[nCntEnemy].pos.x - g_Enemy[nCnt].pos.x) + (g_Enemy[nCntEnemy].pos.y - g_Enemy[nCnt].pos.y) * (g_Enemy[nCntEnemy].pos.y - g_Enemy[nCnt].pos.y) + (g_Enemy[nCntEnemy].pos.z - g_Enemy[nCnt].pos.z) * (g_Enemy[nCntEnemy].pos.z - g_Enemy[nCnt].pos.z);
			D3DXVECTOR3 fRadP(1.0f, 0.0f, 1.0f);
			D3DXVECTOR3 fRadE(1.0f, 0.0f, 1.0f);


			float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);

			fRadius = fRadius * fRadius;

			if (fDistance <= fRadius)
			{
				g_Enemy[nCnt].pos = g_Enemy[nCnt].posOld;
			}
		}
	}

}

//=============================================================================
// 徘徊処理
//=============================================================================
void LoiterEnemy(void)
{


	D3DXVECTOR3 Turn[POINT_MAX];

	float fAnglemove = 0.0f;

	Turn[0] = D3DXVECTOR3(800.0f, 0.0f, 250.0f);
	Turn[1] = D3DXVECTOR3(700.0f, 0.0f, -500.0f);
	Turn[2] = D3DXVECTOR3(20.0f, 0.0f, -150.0f);
	Turn[3] = D3DXVECTOR3(-800.0f, 0.0f, -400.0f);
	Turn[4] = D3DXVECTOR3(-850.0f, 0.0f, 950.0f);
	Turn[5] = D3DXVECTOR3(20.0f, 0.0f, -150.0f);
	Turn[6] = D3DXVECTOR3(500.0f, 0.0f, 600.0f);
	Turn[7] = D3DXVECTOR3(500.0f, 0.0f, 400.0f);
	Turn[8] = D3DXVECTOR3(300.0f, 0.0f, 300.0f);
	Turn[9] = D3DXVECTOR3(300.0f, 0.0f, -300.0f);

	float fDistance = (g_Enemy[0].pos.x - Turn[g_nCntPos].x) * (g_Enemy[0].pos.x - Turn[g_nCntPos].x) + (g_Enemy[0].pos.y - Turn[g_nCntPos].y) * (g_Enemy[0].pos.y - Turn[g_nCntPos].y) + (g_Enemy[0].pos.z - Turn[g_nCntPos].z) * (g_Enemy[0].pos.z - Turn[g_nCntPos].z);
	D3DXVECTOR3 fRadP(100.0f, 0.0f, 100.0f);
	D3DXVECTOR3 fRadE(100.0f, 0.0f, 100.0f);


	float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);


	if (fDistance <= fRadius)
	{//ターン地点まで来たら

		//次のターン地点を設定
		g_nCntPos += 1;
		g_nCntPos = g_nCntPos % POINT_MAX;

	}

	g_Enemy[0].rotDest.y = atan2f((Turn[g_nCntPos].x - g_Enemy[0].pos.x), (Turn[g_nCntPos].z - g_Enemy[0].pos.z))+D3DX_PI;
	fAnglemove = atan2f((Turn[g_nCntPos].x - g_Enemy[0].pos.x), (Turn[g_nCntPos].z - g_Enemy[0].pos.z));
	g_Enemy[0].move.x = sinf(fAnglemove) * 0.7f;
	g_Enemy[0].move.z = cosf(fAnglemove) * 0.7f;

}

//=============================================================================
// 敵の取得処理
//=============================================================================
Enemy* GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// 
//=============================================================================
int GetNumEnemy()
{
	return g_nNumEnemy;
}

//=============================================================================
//モーションの設定
//=============================================================================
void SetMotionType(EMOTIONTYPE MotionType, bool bBlendMotion, int nFrameBlend,int nCnt)
{
	g_Enemy[0].motionTypeBlend = MotionType;
	g_Enemy[0].bBlendMotion = bBlendMotion;
	g_Enemy[0].nFrameBlend = nFrameBlend;
	g_Enemy[0].nKeyBlend = 0;
	g_Enemy[0].nCntMotionBlend = 0;
}

//=============================================================================
//敵の条件文処理
//=============================================================================
bool IsRange()
{
	return bRange;
}