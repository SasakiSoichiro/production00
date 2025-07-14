//=============================================================================
//
//	�G�f�B�b�g���� [edit.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "block.h"
#include "edit.h"
#include "input.h"
#include "player.h"

// �O���[�o���ϐ��錾
EDITINFO g_Edit[NUM_EDIT];
EDITTEX g_EditTex[EDIT_MAX];
int g_EditCnt;
int g_nReloadCnt;

//=============================================================================
// ����������
//=============================================================================
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < NUM_EDIT; nCnt++)
	{
		// �e��ϐ��̏�����
		g_Edit[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Edit[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Edit[nCnt].nType = BLOCK_HOUSE000_L;
		g_Edit[nCnt].bUse = false;
	}

	for (int nCnt = 0; nCnt <EDIT_MAX; nCnt++)
	{
		// x�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(X_EDIT[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_EditTex[nCnt].pBuffMat,
			NULL,
			&g_EditTex[nCnt].dwNumMat,
			&g_EditTex[nCnt].pMesh);
	}

	// �}�e���A���̎擾
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		// �}�e���A���ւ̃|�C���^
		D3DXMATERIAL* pMat;

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_EditTex[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_EditTex[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���
					// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_EditTex[nCnt].apTexture[nCntMat]);
			}
		}
	}

	// 1�Ԗڂ�true�ɂ���
	g_Edit[0].bUse = true;

	// �ϐ���������
	g_Edit[0].tex[0] = g_EditTex[0];

	// �J�E���g������������
	g_EditCnt = 0;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEdit(void)
{
	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
	{
		for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
		{
			if (g_EditTex[nCntTex].apTexture[nCntTexture] != NULL)
			{
				g_EditTex[nCntTex].apTexture[nCntTexture]->Release();
				g_EditTex[nCntTex].apTexture[nCntTexture] = NULL;

			}
		}

		// �e�N�X�`���̔j��
		if (g_EditTex[nCntTex].pMesh != NULL)
		{
			g_EditTex[nCntTex].pMesh->Release();
			g_EditTex[nCntTex].pMesh = NULL;

		}

		// ���_�o�b�t�@�̉��
		if (g_EditTex[nCntTex].pBuffMat != NULL)
		{
			g_EditTex[nCntTex].pBuffMat->Release();
			g_EditTex[nCntTex].pBuffMat = NULL;
		}
	}
	for (int nCntEdit = 0; nCntEdit < NUM_EDIT; nCntEdit++)
	{

		for (int nCntType = 0; nCntType < EDIT_MAX; nCntType++)
		{
			for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
			{
				if (g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] != NULL)
				{
					g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] = NULL;

				}
			}

			if (g_Edit[nCntEdit].tex[nCntType].pMesh != NULL)
			{
				g_Edit[nCntEdit].tex[nCntType].pMesh = NULL;

			}

			// ���_�o�b�t�@�̉��
			if (g_Edit[nCntEdit].tex[nCntType].pBuffMat != NULL)
			{
				g_Edit[nCntEdit].tex[nCntType].pBuffMat = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEdit(void)
{
	if (g_Edit[g_EditCnt].bUse == true)
	{
		// �ړ��ʂ̍X�V
		g_Edit[g_EditCnt].move.x += (0.0f - g_Edit[g_EditCnt].move.x) * 0.25f;

		// �ړ��ʂ̍X�V
		g_Edit[g_EditCnt].move.z += (0.0f - g_Edit[g_EditCnt].move.z) * 0.25f;

		// �ʒu�X�V
		g_Edit[g_EditCnt].pos.x += g_Edit[g_EditCnt].move.x;

		// �ʒu�X�V
		g_Edit[g_EditCnt].pos.z += g_Edit[g_EditCnt].move.z;

		if (GetKeyboardPress(DIK_A) == true)
		{// ���Ɉړ�
			g_Edit[g_EditCnt].move.z -= EDIT_MOVE;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// ���Ɉړ�
			g_Edit[g_EditCnt].move.z += EDIT_MOVE;
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{// ���Ɉړ�
			g_Edit[g_EditCnt].move.x -= EDIT_MOVE;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// ���Ɉړ�
			g_Edit[g_EditCnt].move.x += EDIT_MOVE;
		}
		else if (KeybordTrigger(DIK_T) == true)
		{// ���Ɉړ�
			if (g_Edit[g_EditCnt].nType >= 1)
			{
				g_Edit[g_EditCnt].nType -= 1;
				g_Edit[g_EditCnt].tex[g_Edit[g_EditCnt].nType] = g_EditTex[g_Edit[g_EditCnt].nType];
			}
		}
		else if (KeybordTrigger(DIK_G) == true)
		{// ���Ɉړ�
			if (g_Edit[g_EditCnt].nType < EDIT_MAX - 1)
			{
				g_Edit[g_EditCnt].nType += 1;
				g_Edit[g_EditCnt].tex[g_Edit[g_EditCnt].nType] = g_EditTex[g_Edit[g_EditCnt].nType];
			}
		}
		if (KeybordTrigger(DIK_RETURN) == true)
		{
			g_Edit[g_EditCnt + 1].pos = g_Edit[g_EditCnt].pos;

			g_Edit[g_EditCnt + 1].bUse = true;

			g_Edit[g_EditCnt + 1].nType = g_Edit[g_EditCnt].nType;
			g_Edit[g_EditCnt + 1].tex[g_Edit[g_EditCnt + 1].nType] = g_EditTex[g_Edit[g_EditCnt].nType];

			g_EditCnt++;
		}
	}

#ifdef _DEBUG// �f�o�b�O
	if (KeybordTrigger(DIK_F7) == true)
	{
		SaveEdit();
	}
	if (KeybordTrigger(DIK_F8) == true)
	{
		ReloadEdit();
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEdit(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���̕ۑ��p
	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;		// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntBlock = 0; nCntBlock < NUM_EDIT; nCntBlock++)
	{
		if (g_Edit[nCntBlock].bUse == false)
		{
			continue;
		}

		int nType = g_Edit[nCntBlock].nType;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Edit[nCntBlock].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Edit[nCntBlock].rot.y, g_Edit[nCntBlock].rot.x, g_Edit[nCntBlock].rot.z);
		D3DXMatrixMultiply(&g_Edit[nCntBlock].mtxWorld, &g_Edit[nCntBlock].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Edit[nCntBlock].pos.x, g_Edit[nCntBlock].pos.y, g_Edit[nCntBlock].pos.z);
		D3DXMatrixMultiply(&g_Edit[nCntBlock].mtxWorld, &g_Edit[nCntBlock].mtxWorld, &mtxTrans);

		pDevice->SetTransform(D3DTS_WORLD, &g_Edit[nCntBlock].mtxWorld);

		pDevice->GetMaterial(&matDef);

		for (int nCntMat = 0; nCntMat < (int)g_Edit[nCntBlock].tex[nType].dwNumMat; nCntMat++)
		{
			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Edit[nCntBlock].tex[nType].pBuffMat->GetBufferPointer();

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Edit[nCntBlock].tex[nType].apTexture[nCntMat]);

			// ���f���i�p�[�c�j�̕`��
			g_Edit[nCntBlock].tex[nType].pMesh->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);
	}
}

//=============================================================================
// ���e�ۑ�����
//=============================================================================
void SaveEdit(void)
{
	// �t�@�C���|�C���^��錾
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nType = 0;

	pFile = fopen(TEXTFILE, "w");

	if (pFile != NULL)
	{
		fwrite(&g_EditCnt, sizeof(int), 0, pFile);

		for (int nCnt = 0; nCnt < g_EditCnt; nCnt++)
		{
			if (g_Edit[nCnt].bUse == true)
			{
				fprintf(pFile, "BLOCKSET\n\n");
				fprintf(pFile, "POS %f %f %f\n\n", g_Edit[nCnt].pos.x, g_Edit[nCnt].pos.y, g_Edit[nCnt].pos.z);
				fprintf(pFile, "TYPE %d\n\n", g_Edit[nCnt].nType);
				fprintf(pFile, "END_BLOCKSET\n\n");
			}
		}
		fprintf(pFile, "EDITCNT %d\n\n",g_EditCnt);
		fprintf(pFile, "END_SCRIPT\n\n\n");
		fclose(pFile);
	}
	else
	{// �J���Ȃ������Ƃ��̏���
		return;
	}
}

//=============================================================================
// �Ǎ�����
//=============================================================================
void LoadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nType = 0;
	pFile = fopen(TEXTFILE, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];		// ���������i�[

		// �S���̃e�L�X�g�ɏ����ꂽ����ǂݎ�肪�I���܂ŉ�
		while (1)
		{
			// �t�@�C����ǂݍ���
			fscanf(pFile, "%s", &aString[0]);

			// �ǂݎ�����̕����񂪈�v���Ă�����
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					// �t�@�C����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{// POS��ǂݎ������
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}

					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						SetBlock(pos,nType);
						break;
					}
				}
			}
			//else if (strcmp(aString, "EDITCNT") == 0)
			//{
			//	fscanf(pFile, "%d", &g_nReloadCnt);
			//}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				// while�𔲂��邽��
				break;
			}
		}
		////�t�@�C�������
		//fclose(pFile);
	}
	else
	{// �J���Ȃ������Ƃ��̏���
		// �t�@�C�������
		return;
	}
	// �t�@�C�������
	fclose(pFile);
}

//=============================================================================
// �ēǍ�����
//=============================================================================
void ReloadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nCnt = 0;
	pFile = fopen(TEXTFILE, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];		// ���������i�[

		// �S���̃e�L�X�g�ɏ����ꂽ����ǂݎ�肪�I���܂ŉ�
		while (1)
		{
			// �t�@�C����ǂݍ���
			fscanf(pFile, "%s", &aString[0]);

			// �ǂݎ�����̕����񂪈�v���Ă�����
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					// �t�@�C����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{// POS��ǂݎ������
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.x);
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.y);
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.z);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &g_Edit[nCnt].nType);
					}

					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						nCnt++;
						break;
					}
				}
			}
			if (strcmp(aString, "EDITCNT") == 0)
			{
				fscanf(pFile, "%d", &g_nReloadCnt);
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				// while�𔲂��邽��
				break;
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �J���Ȃ������Ƃ��̏���
		return;
	}
	for (int nCntReload = 0; nCntReload < g_nReloadCnt; nCntReload++)
	{
		g_Edit[g_EditCnt + 1].bUse = true;

		g_Edit[g_EditCnt + 1].tex[g_Edit[nCntReload].nType] = g_EditTex[g_Edit[nCntReload].nType];

		g_EditCnt++;
	}
}
