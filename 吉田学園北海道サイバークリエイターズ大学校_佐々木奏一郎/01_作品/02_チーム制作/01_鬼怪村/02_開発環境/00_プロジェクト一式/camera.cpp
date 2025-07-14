//========================================================
//
//			カメラ	camera.cpp
//				ryuusei hirata
// 
//========================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "enemy.h"

// グローバル
Camera g_camera[MAX_CAMERA] = {};	// カメラ情報

//==============================
// 初期化処理
//==============================
void InitCamera(void)
{
	MODE mode = GetMode();

	// 視点・注視点・上方向を設定する
	for (int count = 0; count < MAX_CAMERA; count++)
	{
		// 各変数の初期化
		g_camera[count].posV = D3DXVECTOR3(100.0f, 60.0f, 0.0f);
		g_camera[count].posR = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
		g_camera[count].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[count].rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		g_camera[count].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].fDistance = sqrtf((g_camera[count].posV.x - g_camera[count].posR.x) 
		* (g_camera[count].posV.x - g_camera[count].posR.x) + (g_camera[count].posV.y - g_camera[count].posR.y) 
		* (g_camera[count].posV.y - g_camera[count].posR.y) + (g_camera[count].posV.z - g_camera[count].posR.z) 
		* (g_camera[count].posV.z - g_camera[count].posR.z));
		g_camera[count].deltaX = 0.0f;
		g_camera[count].deltaY = 0.0f;

		if (mode == MODE_TITLE)
		{
			g_camera[count].posV = D3DXVECTOR3(-100.0f, 80.0f, -200.0f);
			g_camera[count].posR = D3DXVECTOR3(-100.0f, 70.0f, 0.0f);
			g_camera[count].rot = D3DXVECTOR3(0.0f, 90.0f, 0.0f);
		}
	}

	// ビューポート構成の保存	左
	g_camera[0].viewport.X = (DWORD)0.0f;
	g_camera[0].viewport.Y = (DWORD)0.0f;
	g_camera[0].viewport.Width = (DWORD)1280.0f;
	g_camera[0].viewport.Height = (DWORD)720.0f;
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	////	ビューポート構成の保存	右
	//g_camera[1].viewport.X = 640.0f;
	//g_camera[1].viewport.Y = 0.0f;
	//g_camera[1].viewport.Width = 640.0f;
	//g_camera[1].viewport.Height = 720.0f;
	//g_camera[1].viewport.MinZ = 0.0f;
	//g_camera[1].viewport.MaxZ = 1.0f;

	// ビューポート構成の保存	真ん中
	g_camera[1].viewport.X = (DWORD)450.0f;
	g_camera[1].viewport.Y = (DWORD)0.0f;
	g_camera[1].viewport.Width = (DWORD)350.0f;
	g_camera[1].viewport.Height = (DWORD)200.0f;
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;
}

//==============================
//	終了処理
//==============================
void UninitCamera(void)
{

}

//==============================
//	更新処理
//==============================
void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();

	MODE mode = GetMode();

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	// 右スティック視点
	if (GetJoyStick(0) == true)
	{
		if (pStick->Gamepad.sThumbRX > 10922)
		{
			if (pStick->Gamepad.sThumbRY > 10922)
			{
				// 上
				g_camera[0].rot.x -= 0.03f;
			}
			else if (pStick->Gamepad.sThumbRY < -10922)
			{
				// 下
				g_camera[0].rot.x += 0.03f;
			}

			// 右回り
			g_camera[0].rot.y += 0.03f;
		}
		else if (pStick->Gamepad.sThumbRX < -10922)
		{
			if (pStick->Gamepad.sThumbRY > 10922)
			{
				// 上
				g_camera[0].rot.x -= 0.03f;
			}
			else if (pStick->Gamepad.sThumbRY < -10922)
			{
				// 下
				g_camera[0].rot.x += 0.03f;
			}

			// 左回り
			g_camera[0].rot.y -= 0.03f;
		}
		else if (pStick->Gamepad.sThumbRY > 10922)
		{
			if (pStick->Gamepad.sThumbRX > 10922)
			{
				// 右回り
				g_camera[0].rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX < -10922)
			{
				// 左回り
				g_camera[0].rot.y -= 0.03f;
			}

			// 上
			g_camera[0].rot.x -= 0.03f;
		}
		else if (pStick->Gamepad.sThumbRY < -10922)
		{
			if (pStick->Gamepad.sThumbRX > 10922)
			{
				// 右回り
				g_camera[0].rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX < -10922)
			{
				// 左回り
				g_camera[0].rot.y -= 0.03f;
			}

			// 下
			g_camera[0].rot.x += 0.03f;
		}
	}

	// 角度の正規化
	if (g_camera[0].rot.y <= -D3DX_PI)
	{
		g_camera[0].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera[0].rot.y >= D3DX_PI)
	{
		g_camera[0].rot.y += -D3DX_PI * 2.0f;
	}

	// 角度制限
	if (g_camera[0].rot.x > 1.57f)
	{
		g_camera[0].rot.x = 1.57f;
	}
	else if (g_camera[0].rot.x < -1.57f)
	{
		g_camera[0].rot.x = -1.57f;
	}

	// プレイヤーの視点
	if (GetEditState() == false && mode == MODE_GAME)
	{
		static POINT prevCursorPos = { (long)(SCREEN_WIDTH / 1.5f), (long)(SCREEN_HEIGHT / 1.5f) };

		POINT cursorPos;

		GetCursorPos(&cursorPos);

		float DeltaX = (float)cursorPos.x - prevCursorPos.x;
		float DeltaY = (float)cursorPos.y - prevCursorPos.y;

		const float mouseSensitivity = 0.0009f;

		DeltaX *= mouseSensitivity;
		DeltaY *= mouseSensitivity;

		g_camera[0].rot.x += DeltaY;
		g_camera[0].rot.y += DeltaX;

		SetCursorPos(SCREEN_WIDTH / (LONG)1.5f, SCREEN_HEIGHT / (LONG)1.5f);

		prevCursorPos.x = SCREEN_WIDTH / (LONG)1.5f;
		prevCursorPos.y = SCREEN_HEIGHT / (LONG)1.5f;

		g_camera[0].posV = pPlayer->pos;
		g_camera[0].posV.y += 75.0f;

		g_camera[0].posR.x = g_camera[0].posV.x - sinf(g_camera[0].rot.y) * cosf(g_camera[0].rot.x);
		g_camera[0].posR.y = g_camera[0].posV.y - sinf(g_camera[0].rot.x);
		g_camera[0].posR.z = g_camera[0].posV.z - cosf(g_camera[0].rot.y) * cosf(g_camera[0].rot.x);
	}
	else if (GetEditState() == true)
	{
		static POINT prevCursorPos = { (long)(SCREEN_WIDTH / 1.5), (long)(SCREEN_HEIGHT / 1.5) };

		POINT cursorPos;

		GetCursorPos(&cursorPos);

		float DeltaX = (float)cursorPos.x - prevCursorPos.x;
		float DeltaY = (float)cursorPos.y - prevCursorPos.y;

		const float mouseSensitivity = 0.0009f;

		DeltaX *= mouseSensitivity;
		DeltaY *= mouseSensitivity;

		g_camera[0].rot.x += DeltaY;
		g_camera[0].rot.y += DeltaX;

		// 角度の正規化
		if (g_camera[0].rot.y <= -D3DX_PI)
		{
			g_camera[0].rot.y += D3DX_PI * 2.0f;
		}
		else if (g_camera[0].rot.y >= D3DX_PI)
		{
			g_camera[0].rot.y += -D3DX_PI * 2.0f;
		}
		SetCursorPos(SCREEN_WIDTH / (LONG)1.5f, SCREEN_HEIGHT / (LONG)1.5f);

		prevCursorPos.x = SCREEN_WIDTH / (LONG)1.5f;
		prevCursorPos.y = SCREEN_HEIGHT / (LONG)1.5f;

		g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.x) * sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
		g_camera[0].posR.y = g_camera[0].posV.y + cosf(g_camera[0].rot.x) * g_camera[0].fDistance;
		g_camera[0].posR.z = g_camera[0].posV.z + sinf(g_camera[0].rot.x) * cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
	}

	// 敵の視点
	Enemy* pEnemy = GetEnemy();

	if (GetEditState() == false && mode == MODE_GAME)
	{
		g_camera[1].posV = pEnemy->pos;
		g_camera[1].posV.y += 100.0f;

		g_camera[1].posR.x = g_camera[1].posV.x - sinf(pEnemy->rot.y) * cosf(pEnemy->rot.x);
		g_camera[1].posR.y = g_camera[1].posV.y - sinf(pEnemy->rot.x);
		g_camera[1].posR.z = g_camera[1].posV.z - cosf(pEnemy->rot.y) * cosf(pEnemy->rot.x);

		if (g_camera[1].rot.y <= -D3DX_PI)
		{
			g_camera[1].rot.y += D3DX_PI * 2.0f;
		}
		else if (g_camera[1].rot.y >= D3DX_PI)
		{
			g_camera[1].rot.y += -D3DX_PI * 2.0f;
		}
	}
}

//==============================
//	カメラの設定処理
//==============================
void SetCamera(int nIdx)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ビューマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

		// ビューマトリックスの作成
		D3DXMatrixLookAtLH(&g_camera[nIdx].mtxView,
			&g_camera[nIdx].posV,
			&g_camera[nIdx].posR,
			&g_camera[nIdx].vecU);

		// ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);

		// プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

		// プロジェクションマトリックスの初期化
		D3DXMatrixPerspectiveFovLH(&g_camera[nIdx].mtxProjection,
			D3DXToRadian(70.0f),				// 視野角
			SCREEN_WIDTH / SCREEN_HEIGHT,		// アスペクト比
			10.0f,								// どこからどこまで
			3000.0f);							// カメラで表示するか

		// プロジェクトマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);
}

//==============================
//	マウスでのカメラ移動の処理
//==============================
void MouseWheel(int zDelta)
{
	if (zDelta > 0)
	{
		g_camera[0].fDistance -= 15.0f;
	}
	else if (zDelta < 0)
	{
		g_camera[0].fDistance += 15.0f;
	}

	// カメラの視点の情報
	g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.x) * sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posV.y = g_camera[0].posR.y - cosf(g_camera[0].rot.x) * g_camera[0].fDistance;
	g_camera[0].posV.z = g_camera[0].posR.z - sinf(g_camera[0].rot.x) * cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
}

//==============================
//	カメラの情報を取得する処理
//==============================
Camera* GetCamera(void)
{
	return &g_camera[0];
}