//======================================================
//
//		ライト  light.cpp
//		ryuusei hirata
//
//======================================================
#include "light.h"
#include "main.h"
#include "player.h"

//	グローバル
D3DLIGHT9 g_light[MAX_LIGHT] = {};	//	ライト情報
D3DLIGHT9 light;

void InitLight(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	//	ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9) * MAX_LIGHT);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;  // スポットライト
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.7f);		// 白色の拡散光
		//g_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 白色の鏡面反射光
		//g_light[nCntLight].Ambient = D3DXCOLOR(0.5f, 0.2f, 0.2f, 1.0f);		// 暗めの周囲光
		//g_light[nCntLight].Position = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y+10.0f, pPlayer->pos.z);		// ライトの位置
		//g_light[nCntLight].Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);		// ライトの向き（下向き）
		//g_light[nCntLight].Range = 10.0f;									// ライトの範囲
		//g_light[nCntLight].Falloff = 1.0f;									// 減衰
		//g_light[nCntLight].Attenuation0 = 1.0f;								// 減衰定数
		//g_light[nCntLight].Attenuation1 = 0.0f;
		//g_light[nCntLight].Attenuation2 = 0.0f;
		//g_light[nCntLight].Theta = D3DXToRadian(30.0f);						// コーン角度
		//g_light[nCntLight].Phi = D3DXToRadian(60.0f);						// 広がり角度

		//	ライトの方向
		vecDir[0] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		vecDir[1] = D3DXVECTOR3(0.3f, -0.8f, 0.4f);
		vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

		//	正規化する
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//	ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//	ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void UninitLight(void)
{

}

void UpdateLight(void)
{

	//プレイヤー情報の取得
	Player* pPlayer = GetPlayer();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);		// 白色の拡散光
		g_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 白色の鏡面反射光
		g_light[nCntLight].Ambient = D3DXCOLOR(0.5f, 0.2f, 0.2f, 1.0f);		// 暗めの周囲光
		g_light[nCntLight].Position = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 50.0f, pPlayer->pos.z);		// ライトの位置
		g_light[nCntLight].Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);		// ライトの向き（下向き）
		g_light[nCntLight].Range = 10.0f;									// ライトの範囲
		g_light[nCntLight].Falloff = 1.0f;									// 減衰
		g_light[nCntLight].Attenuation0 = 1.0f;								// 減衰定数
		g_light[nCntLight].Attenuation1 = 0.0f;
		g_light[nCntLight].Attenuation2 = 0.0f;
		g_light[nCntLight].Theta = D3DXToRadian(30.0f);						// コーン角度
		g_light[nCntLight].Phi = D3DXToRadian(60.0f);						// 広がり角度

	}
	
}
void SetupPointLight(D3DXVECTOR3 pos)
{
	ZeroMemory(&light, sizeof(light));
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_POINT;
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 白色の拡散光
		g_light[nCntLight].Position = D3DXVECTOR3(pos.x, pos.y, pos.z); // ライトの位置
		g_light[nCntLight].Range = 100.0f;
	}
}