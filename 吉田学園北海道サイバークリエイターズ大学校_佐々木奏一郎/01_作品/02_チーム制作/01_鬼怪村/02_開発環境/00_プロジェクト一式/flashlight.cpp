//=============================================================================
//
//		�����d��  flashlight.cpp
//		Auther:Sasaki Soichiro
//
//=============================================================================

#include "flashlight.h"
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//	�O���[�o��
FLASHLIGHT g_FlashLight[MAX_FLASH];

//=============================================================================
// ����������
//=============================================================================
void InitFlashLight(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_FLASH];

	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	//	���C�g���N���A����
	ZeroMemory(&g_FlashLight, sizeof(D3DLIGHT9) * MAX_FLASH);

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		//�O���[�o���ϐ�������
		InitFlashGlobal(nCntLight);

		//	���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);

		//	���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitFlashLight(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		//	���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, FALSE);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFlashLight(void)
{
	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLight = 0; nCntLight < MAX_FLASH; nCntLight++)
	{
		if (g_FlashLight[nCntLight].bLight == true)
		{
			bFlashTRUE(nCntLight);

			//	���C�g��ݒ肷��
			pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);
		}
		else if (g_FlashLight[nCntLight].bLight == false)
		{
			bFlashFALSE(nCntLight);

			//	���C�g��ݒ肷��
			pDevice->SetLight(nCntLight, &g_FlashLight[nCntLight].light);
		}
	}
}

//=============================================================================
// �����d���̎擾����
//=============================================================================
FLASHLIGHT* GetFlashLight(void)
{
	return &g_FlashLight[0];
}

//=============================================================================
// �O���[�o���ϐ��̏�����
//=============================================================================
void InitFlashGlobal(int nCnt)
{
	g_FlashLight[nCnt].light.Type = D3DLIGHT_POINT;  // �X�|�b�g���C�g
	g_FlashLight[nCnt].light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���F�̊g�U��
	g_FlashLight[nCnt].light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);  // �N���Ȍ�
	g_FlashLight[nCnt].light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);   // ���͂̌�
	g_FlashLight[nCnt].light.Range = 10.0f;  // ���̓��B����
	g_FlashLight[nCnt].light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �����ʒu
	g_FlashLight[nCnt].light.Falloff = 1.0f;  // ���̌���
	g_FlashLight[nCnt].light.Attenuation0 = 1.0f;
	g_FlashLight[nCnt].light.Attenuation1 = 0.0f;
	g_FlashLight[nCnt].light.Attenuation2 = 0.0f;
	g_FlashLight[nCnt].bLight = false;
}

//=============================================================================
// �����d��ON
//=============================================================================
void bFlashTRUE(int nCnt)
{
	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	g_FlashLight[nCnt].light.Position = pPlayer->pos;

	g_FlashLight[nCnt].light.Position.y = pPlayer->pos.y + 100.0f;

	g_FlashLight[nCnt].light.Range = 800.0f;  // ���̓��B����
}

//=============================================================================
// �����d��OFF
//=============================================================================
void bFlashFALSE(int nCnt)
{
	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	g_FlashLight[nCnt].light.Position = pPlayer->pos;

	g_FlashLight[nCnt].light.Position.y = pPlayer->pos.y + 100.0f;

	g_FlashLight[nCnt].light.Range = 10.0f;  // ���̓��B����
}