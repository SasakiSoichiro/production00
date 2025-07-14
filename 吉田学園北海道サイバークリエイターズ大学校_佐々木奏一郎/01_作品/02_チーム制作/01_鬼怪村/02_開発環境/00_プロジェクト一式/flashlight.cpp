//=============================================================================
//
//		懐中電灯  flashlight.cpp
//		Auther:Sasaki Soichiro
//
//=============================================================================

#include "flashlight.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//	グローバル
FLASHLIGHT g_FlashLight[MAX_FLASH];

//=============================================================================
// 初期化処理
//=============================================================================
void InitFlashLight(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_FLASH];

	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	//	ライトをクリアする
	ZeroMemory(&g_FlashLight, sizeof(D3DLIGHT9) * MAX_FLASH);

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		//グローバル変数初期化
		InitFlashGlobal(nCntLight);

		//	ライトを設定する
		pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);

		//	ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFlashLight(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		//	ライトを有効にする
		pDevice->LightEnable(nCntLight, FALSE);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFlashLight(void)
{
	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		if (g_FlashLight[nCntLight].bLight == true)
		{
			bFlashTRUE(nCntLight);

			//	ライトを設定する
			pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);
		}
		else if (g_FlashLight[nCntLight].bLight == false)
		{
			bFlashFALSE(nCntLight);

			//	ライトを設定する
			pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);
		}
	}
}

//=============================================================================
// 懐中電灯の取得処理
//=============================================================================
FLASHLIGHT* GetFlashLight(void)
{
	return &g_FlashLight[0];
}

//=============================================================================
// グローバル変数の初期化
//=============================================================================
void InitFlashGlobal(int nCnt)
{
	g_FlashLight[nCnt].light.Type = D3DLIGHT_POINT;  // スポットライト
	g_FlashLight[nCnt].light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 白色の拡散光
	g_FlashLight[nCnt].light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // 鮮明な光
	g_FlashLight[nCnt].light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);   // 周囲の光
	g_FlashLight[nCnt].light.Range = 10.0f;  // 光の到達距離
	g_FlashLight[nCnt].light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 初期位置
	g_FlashLight[nCnt].light.Falloff = 1.0f;  // 光の減衰
	g_FlashLight[nCnt].light.Attenuation0 = 1.0f;
	g_FlashLight[nCnt].light.Attenuation1 = 0.0f;
	g_FlashLight[nCnt].light.Attenuation2 = 0.0f;
	g_FlashLight[nCnt].bLight = false;
}

//=============================================================================
// 懐中電灯ON
//=============================================================================
void bFlashTRUE(int nCnt)
{
	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	g_FlashLight[nCnt].light.Position = pPlayer->pos;

	g_FlashLight[nCnt].light.Position.y = pPlayer->pos.y + 100.0f;

	g_FlashLight[nCnt].light.Range = 800.0f;  // 光の到達距離
}

//=============================================================================
// 懐中電灯OFF
//=============================================================================
void bFlashFALSE(int nCnt)
{
	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	g_FlashLight[nCnt].light.Position = pPlayer->pos;

	g_FlashLight[nCnt].light.Position.y = pPlayer->pos.y + 100.0f;

	g_FlashLight[nCnt].light.Range = 10.0f;  // 光の到達距離
}