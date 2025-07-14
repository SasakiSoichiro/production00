//========================================================
//
//			�J����	camera.cpp
//				ryuusei hirata
// 
//========================================================

#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "enemy.h"

// �O���[�o��
Camera g_camera[MAX_CAMERA] = {};	// �J�������

//==============================
// ����������
//==============================
void InitCamera(void)
{
	MODE mode = GetMode();

	// ���_�E�����_�E�������ݒ肷��
	for (int count = 0; count < MAX_CAMERA; count++)
	{
		// �e�ϐ��̏�����
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

	// �r���[�|�[�g�\���̕ۑ�	��
	g_camera[0].viewport.X = (DWORD)0.0f;
	g_camera[0].viewport.Y = (DWORD)0.0f;
	g_camera[0].viewport.Width = (DWORD)1280.0f;
	g_camera[0].viewport.Height = (DWORD)720.0f;
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	////	�r���[�|�[�g�\���̕ۑ�	�E
	//g_camera[1].viewport.X = 640.0f;
	//g_camera[1].viewport.Y = 0.0f;
	//g_camera[1].viewport.Width = 640.0f;
	//g_camera[1].viewport.Height = 720.0f;
	//g_camera[1].viewport.MinZ = 0.0f;
	//g_camera[1].viewport.MaxZ = 1.0f;

	// �r���[�|�[�g�\���̕ۑ�	�^��
	g_camera[1].viewport.X = (DWORD)450.0f;
	g_camera[1].viewport.Y = (DWORD)0.0f;
	g_camera[1].viewport.Width = (DWORD)350.0f;
	g_camera[1].viewport.Height = (DWORD)200.0f;
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;
}

//==============================
//	�I������
//==============================
void UninitCamera(void)
{

}

//==============================
//	�X�V����
//==============================
void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();

	MODE mode = GetMode();

	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	// �E�X�e�B�b�N���_
	if (GetJoyStick(0) == true)
	{
		if (pStick->Gamepad.sThumbRX > 10922)
		{
			if (pStick->Gamepad.sThumbRY > 10922)
			{
				// ��
				g_camera[0].rot.x -= 0.03f;
			}
			else if (pStick->Gamepad.sThumbRY < -10922)
			{
				// ��
				g_camera[0].rot.x += 0.03f;
			}

			// �E���
			g_camera[0].rot.y += 0.03f;
		}
		else if (pStick->Gamepad.sThumbRX < -10922)
		{
			if (pStick->Gamepad.sThumbRY > 10922)
			{
				// ��
				g_camera[0].rot.x -= 0.03f;
			}
			else if (pStick->Gamepad.sThumbRY < -10922)
			{
				// ��
				g_camera[0].rot.x += 0.03f;
			}

			// �����
			g_camera[0].rot.y -= 0.03f;
		}
		else if (pStick->Gamepad.sThumbRY > 10922)
		{
			if (pStick->Gamepad.sThumbRX > 10922)
			{
				// �E���
				g_camera[0].rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX < -10922)
			{
				// �����
				g_camera[0].rot.y -= 0.03f;
			}

			// ��
			g_camera[0].rot.x -= 0.03f;
		}
		else if (pStick->Gamepad.sThumbRY < -10922)
		{
			if (pStick->Gamepad.sThumbRX > 10922)
			{
				// �E���
				g_camera[0].rot.y += 0.03f;
			}
			else if (pStick->Gamepad.sThumbRX < -10922)
			{
				// �����
				g_camera[0].rot.y -= 0.03f;
			}

			// ��
			g_camera[0].rot.x += 0.03f;
		}
	}

	// �p�x�̐��K��
	if (g_camera[0].rot.y <= -D3DX_PI)
	{
		g_camera[0].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera[0].rot.y >= D3DX_PI)
	{
		g_camera[0].rot.y += -D3DX_PI * 2.0f;
	}

	// �p�x����
	if (g_camera[0].rot.x > 1.57f)
	{
		g_camera[0].rot.x = 1.57f;
	}
	else if (g_camera[0].rot.x < -1.57f)
	{
		g_camera[0].rot.x = -1.57f;
	}

	// �v���C���[�̎��_
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

		// �p�x�̐��K��
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

	// �G�̎��_
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
//	�J�����̐ݒ菈��
//==============================
void SetCamera(int nIdx)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// �r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

		// �r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&g_camera[nIdx].mtxView,
			&g_camera[nIdx].posV,
			&g_camera[nIdx].posR,
			&g_camera[nIdx].vecU);

		// �r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);

		// �v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

		// �v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixPerspectiveFovLH(&g_camera[nIdx].mtxProjection,
			D3DXToRadian(70.0f),				// ����p
			SCREEN_WIDTH / SCREEN_HEIGHT,		// �A�X�y�N�g��
			10.0f,								// �ǂ�����ǂ��܂�
			3000.0f);							// �J�����ŕ\�����邩

		// �v���W�F�N�g�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);
}

//==============================
//	�}�E�X�ł̃J�����ړ��̏���
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

	// �J�����̎��_�̏��
	g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.x) * sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posV.y = g_camera[0].posR.y - cosf(g_camera[0].rot.x) * g_camera[0].fDistance;
	g_camera[0].posV.z = g_camera[0].posR.z - sinf(g_camera[0].rot.x) * cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
}

//==============================
//	�J�����̏����擾���鏈��
//==============================
Camera* GetCamera(void)
{
	return &g_camera[0];
}