//======================================================
//
//		���C�g  light.cpp
//		ryuusei hirata
//
//======================================================
#include "light.h"
#include "main.h"
#include "player.h"

//	�O���[�o��
D3DLIGHT9 g_light[MAX_LIGHT] = {};	//	���C�g���
D3DLIGHT9 light;

void InitLight(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	//	���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9) * MAX_LIGHT);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;  // �X�|�b�g���C�g
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.7f);		// ���F�̊g�U��
		//g_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���F�̋��ʔ��ˌ�
		//g_light[nCntLight].Ambient = D3DXCOLOR(0.5f, 0.2f, 0.2f, 1.0f);		// �Â߂̎��͌�
		//g_light[nCntLight].Position = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y+10.0f, pPlayer->pos.z);		// ���C�g�̈ʒu
		//g_light[nCntLight].Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);		// ���C�g�̌����i�������j
		//g_light[nCntLight].Range = 10.0f;									// ���C�g�͈̔�
		//g_light[nCntLight].Falloff = 1.0f;									// ����
		//g_light[nCntLight].Attenuation0 = 1.0f;								// �����萔
		//g_light[nCntLight].Attenuation1 = 0.0f;
		//g_light[nCntLight].Attenuation2 = 0.0f;
		//g_light[nCntLight].Theta = D3DXToRadian(30.0f);						// �R�[���p�x
		//g_light[nCntLight].Phi = D3DXToRadian(60.0f);						// �L����p�x

		//	���C�g�̕���
		vecDir[0] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		vecDir[1] = D3DXVECTOR3(0.3f, -0.8f, 0.4f);
		vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

		//	���K������
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//	���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//	���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void UninitLight(void)
{

}

void UpdateLight(void)
{

	//�v���C���[���̎擾
	Player* pPlayer = GetPlayer();

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);		// ���F�̊g�U��
		g_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���F�̋��ʔ��ˌ�
		g_light[nCntLight].Ambient = D3DXCOLOR(0.5f, 0.2f, 0.2f, 1.0f);		// �Â߂̎��͌�
		g_light[nCntLight].Position = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 50.0f, pPlayer->pos.z);		// ���C�g�̈ʒu
		g_light[nCntLight].Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);		// ���C�g�̌����i�������j
		g_light[nCntLight].Range = 10.0f;									// ���C�g�͈̔�
		g_light[nCntLight].Falloff = 1.0f;									// ����
		g_light[nCntLight].Attenuation0 = 1.0f;								// �����萔
		g_light[nCntLight].Attenuation1 = 0.0f;
		g_light[nCntLight].Attenuation2 = 0.0f;
		g_light[nCntLight].Theta = D3DXToRadian(30.0f);						// �R�[���p�x
		g_light[nCntLight].Phi = D3DXToRadian(60.0f);						// �L����p�x

	}
	
}
void SetupPointLight(D3DXVECTOR3 pos)
{
	ZeroMemory(&light, sizeof(light));
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_POINT;
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// ���F�̊g�U��
		g_light[nCntLight].Position = D3DXVECTOR3(pos.x, pos.y, pos.z); // ���C�g�̈ʒu
		g_light[nCntLight].Range = 100.0f;
	}
}