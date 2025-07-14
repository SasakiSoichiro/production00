//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : HRT ryuusei
//
//=============================================================================

#include "item.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "slow.h"
#include "Recovery.h"
#include "ItemUI.h"
#include "pickupUI.h"
#include "flashlight.h"
#include "Particle.h"

// �O���[�o���ϐ��錾
ITEM g_item[ITEMTYPE_MAX];
ITEMINFO Iteminfo[ITEMTYPE_MAX]; // ���
bool bNeed;

//=================
//	����������
//=================
void Inititem(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(ITEM_MODEL[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Iteminfo[nCnt].pBufferMat,
			NULL,
			&Iteminfo[nCnt].dwNuMat,
			&Iteminfo[nCnt].pMesh);
	}

	bNeed = false;

	for (int count = 0; count < ITEMTYPE_MAX; count++)
	{
		g_item[count].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W
		g_item[count].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �p�x
		g_item[count].nType = 0;							// ���
		g_item[count].bUse = false;							// ���g�p����
		g_item[count].bHave = false;
		g_item[count].bOldHave = false;
		g_item[count].bHold = false;
		g_item[count].nIdxUI = 0;

		// �}�e���A���̃|�C���^
		D3DXMATERIAL* pMat;

		// �}�e���A������
		pMat = (D3DXMATERIAL*)Iteminfo[count].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)Iteminfo[count].dwNuMat; nCntMat++)
		{
			// �e�N�X�`���̓ǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&Iteminfo[count].pTexture[nCntMat]);
			}
		}
	}
}

//=================
//	�I������
//=================
void Uninititem(void)
{
	// ��������
	StopSound();

	for (int count = 0; count < ITEMTYPE_MAX; count++)
	{
		int nType = g_item[count].nType;

		for (int nCntMat = 0; nCntMat < (int)Iteminfo[count].dwNuMat; nCntMat++)
		{
			// �e�N�X�`���̔j��
			if (Iteminfo[nType].pTexture[nCntMat] != NULL)
			{
				Iteminfo[nType].pTexture[nCntMat]->Release();
				Iteminfo[nType].pTexture[nCntMat] = NULL;
			}
		}
	}

	for (int count = 0; count < ITEMTYPE_MAX; count++)
	{
		// ���b�V���̔j��
		if (Iteminfo[count].pMesh != NULL)
		{
			Iteminfo[count].pMesh->Release();
			Iteminfo[count].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (Iteminfo[count].pBufferMat != NULL)
		{
			Iteminfo[count].pBufferMat->Release();
			Iteminfo[count].pBufferMat = NULL;
		}
	}
}

//================
// �X�V����
//================
void Updateitem(void)
{
	Player* pPlayer = GetPlayer();
	Slow* pSlow = GetSlow();

	static float fAngle = 0.0f; // ��]�p�x (�t���[�����Ƃɑ���)

	for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	{
		// �O�񎝂��Ă������̂�ۑ�
		g_item[nCnt].bOldHave = g_item[nCnt].bHave;

		if (g_item[nCnt].nType == ITEMTYPE_THREE|| g_item[nCnt].nType == ITEMTYPE_FIVE)
		{

			// Y����]�����̒ǉ�
			g_item[nCnt].rot.y += D3DXToRadian(1.0f); // ���t���[��1�x��]

			// ��]�p�x�̍X�V (��]���x�̒������\)
			fAngle += D3DXToRadian(10.0f);  // ���t���[��1�x����]
			if (fAngle >= D3DXToRadian(360.0f))
			{
				fAngle -= D3DXToRadian(360.0f); // 360�x�𒴂����烊�Z�b�g
			}
		}
		
		// �A�C�e�����g�p����Ă�����
		if (g_item[nCnt].bUse == true)
		{
			//�p�[�e�B�N���p�x
			float fAngleX = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleY = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleZ = (float)(rand() % 628 - 314) * 0.01f;

			//�p�[�e�B�N������
			float fIDisX = (float)(rand() % 10 + 5);
			float fIDisY = (float)(rand() % 10 + 5);
			float fIDisZ = (float)(rand() % 10 + 5);

			// �v���C���[�̔��a�̎Z�o�p�ϐ�
			float fPRadPos = 50.0f;

			// �A�C�e���̔��a�̎Z�o�p�ϐ�
			float fIRadPos = 50.0f;

			// �A�C�e���̔��a�̎Z�o�p�ϐ�(�p�[�e�B�N��)
			float fIRadPos1 = 150.0f;

			// �v����[�̈ʒu���擾
			D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

			// �A�C�e���̃v���C���[�̋����̍�
			D3DXVECTOR3 diff = PlayerPos - g_item[nCnt].pos;

			// �͈͌v�Z
			float fDisX = PlayerPos.x - g_item[nCnt].pos.x;
			float fDisY = PlayerPos.y - g_item[nCnt].pos.y;
			float fDisZ = PlayerPos.z - g_item[nCnt].pos.z;

			// ��̔��a�����߂�
			float fRadX = fPRadPos + fIRadPos;

			//�A�C�e���̃p�[�e�B�N�����o���͈�
			float fRadX1 = fPRadPos + fIRadPos1;

			float fParticleX = g_item[nCnt].pos.x + sinf(fAngleX) * fIDisX;
			float fParticleY = g_item[nCnt].pos.y + sinf(fAngleY) * fIDisY;
			float fParticleZ = g_item[nCnt].pos.z + cosf(fAngleZ) * fIDisZ;

			// �v���C���[���A�C�e���͈̔͂ɓ�������
			if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				if (KeybordTrigger(DIK_F) == true || JoyPadTrigger(JOYKEY_B) == true)
				{// F�������ꂽ�Ƃ�

					PlaySound(SOUND_LABEL_SE1);

					// �A�C�e�����E��

					g_item[nCnt].bHave = true;
					g_item[nCnt].bUse = false;
					SetItemUI(g_item[nCnt].nType);

					// �E�o����
					if (g_item[nCnt].bUse == false && g_item[nCnt].nType == ITEMTYPE_ONE)
					{
						g_item[nCnt].bHold = true;
					}

					if (g_item[nCnt].bUse == false && g_item[nCnt].nType == ITEMTYPE_TWO)
					{
						g_item[nCnt].bHold = true;
					}

					if (g_item[nCnt].bUse == false && g_item[nCnt].nType == ITEMTYPE_THREE)
					{
						g_item[nCnt].bHold = true;
					}

					if (g_item[nCnt].bUse == false && g_item[nCnt].nType == ITEMTYPE_FIVE)
					{
						g_item[nCnt].bHold = true;
					}

					if (g_item[nCnt].bUse == false && g_item[nCnt].nType == ITEMTYPE_SIX)
					{
						g_item[nCnt].bHold = true;
					}
				}
			}
			if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX1 * fRadX1))
			{
				SetParticle(D3DXVECTOR3(fParticleX, fParticleY, fParticleZ), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f), 30);
			}
		}
	}

	int nSelect = GetSelect();
	ItemUI* pItemUI = GetItemUI();
	FLASHLIGHT* pFlash = GetFlashLight();

	if (KeybordTrigger(DIK_E) == true || JoyPadTrigger(JOYKEY_X) == true)
	{// �������v�������Ă��鎞�A�������v���g�p���鏈��

		pItemUI += nSelect;
		for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
		{

			switch (pItemUI->nType)
			{
			case ITEM_POCKETWATCH:	// �X���[
				if (g_item[nCnt].bHave == true && g_item[nCnt].nType == ITEMTYPE_THREE)
				{
					// SE��炷
					PlaySound(SOUND_LABEL_SE3);

					pSlow->bUse = true;

					g_item[nCnt].bHave = false;

					SetUsedItemUI(g_item[nCnt].nType);

					SetSlow();
				}
				break;
			case ITEM_HEAL:		// �񕜃A�C�e��
				// �v���C���[�̗̑͂�2�ȉ��Ȃ�
				if (g_item[nCnt].bHave == true && g_item[nCnt].nType == ITEMTYPE_FIVE)
				{
					if (pPlayer->nLife <= 2)
					{

						bNeed = true;

						// SE��炷
						PlaySound(SOUND_LABEL_SE2);

						pPlayer->nLife += 1;
						SetRecovery(90);
						g_item[nCnt].bHave = false;
						SetUsedItemUI(g_item[nCnt].nType);
					}

					break;
				}
				break;
			case ITEM_FLASHLIGHT:		// �񕜃A�C�e��
				// �v���C���[�̗̑͂�2�ȉ��Ȃ�
				if (g_item[nCnt].bHave == true && g_item[nCnt].nType == ITEMTYPE_SIX)
				{
					if (pFlash->bLight == true)
					{
						// SE��炷
						PlaySound(SOUND_LABEL_SE4);

						pFlash->bLight = false;
					}
					else if (pFlash->bLight == false)
					{
						// SE��炷
						PlaySound(SOUND_LABEL_SE4);

						pFlash->bLight = true;
					}
				}
			}
		}
		pItemUI = 0;
	}
}

//=================
//	�`�揈��
//=================
void Drawitem(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v�Z�p
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	for (int count = 0; count < ITEMTYPE_MAX; count++)
	{
		if (g_item[count].bUse == false)
		{// ���g�p��������
			// ���̏�����ʂ��Ȃ��ŃJ�E���g��i�߂�
			continue;
		}

		// ��ނ�ۑ�
		int nType = g_item[count].nType;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_item[count].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_item[count].rot.y, g_item[count].rot.x, g_item[count].rot.z);
		D3DXMatrixMultiply(&g_item[count].mtxWorld, &g_item[count].mtxWorld, &mtxRot);

		// �ʒu�̔��f
		D3DXMatrixTranslation(&mtxTrans, g_item[count].pos.x, g_item[count].pos.y, g_item[count].pos.z);
		D3DXMatrixMultiply(&g_item[count].mtxWorld, &g_item[count].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_item[count].mtxWorld);

		// ���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)Iteminfo[nType].dwNuMat; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)Iteminfo[nType].pBufferMat->GetBufferPointer();

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, Iteminfo[nType].pTexture[nCntMat]);

			// ���f���̕`��
			Iteminfo[nType].pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//=================
//	�擾����
//=================
ITEM* Getitem(void)
{
	return &g_item[0];
}

//=================
//	�z�u����
//=================
void Setitem(D3DXVECTOR3 pos, int nType)
{
	for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	{
		if (g_item[nCnt].bUse == false)
		{
			g_item[nCnt].pos = pos;
			g_item[nCnt].nType = nType;
			g_item[nCnt].bUse = true;
			g_item[nCnt].nIdxUI = SetPickUpUI(g_item[nCnt].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		}
	}
}

bool IsNeed()
{
	return bNeed;
}