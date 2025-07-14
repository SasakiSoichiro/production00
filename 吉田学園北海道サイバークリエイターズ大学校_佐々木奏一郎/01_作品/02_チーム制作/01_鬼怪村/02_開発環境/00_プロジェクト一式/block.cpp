//=============================================================================
//
//	�u���b�N���� [block.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================

// �C���N���[�h�t�@�C��
#include "block.h"
#include "player.h"

// �O���[�o���ϐ��錾
BLOCK g_Block[NUM_BLOCK];
BLOCKTEX g_BlockTex[BLOCK_MAX];

//==============================
// �u���b�N�̏���������
//==============================
void InitBlock(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		// �e��ϐ��̏�����
		g_Block[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCnt].nType = BLOCK_HOUSE000_L;
		g_Block[nCnt].bUse = false;
	}

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		// x�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(X_BLOCK[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_BlockTex[nCnt].pBuffMat,
			NULL,
			&g_BlockTex[nCnt].dwNumMat,
			&g_BlockTex[nCnt].pMesh);
	}

	int nNumVtx=0;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���_���̎擾
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		nNumVtx = g_BlockTex[nCnt].pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_BlockTex[nCnt].pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		g_BlockTex[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			// ���_���W���r���ă��f���̍ŏ��l�ő�l���擾
			// X============================
			if (vtx.x > g_BlockTex[nCnt].vtxMax.x)
			{
				g_BlockTex[nCnt].vtxMax.x = vtx.x;
			}

			if (vtx.x < g_BlockTex[nCnt].vtxMin.x)
			{
				g_BlockTex[nCnt].vtxMin.x = vtx.x;
			}
			// Y============================
			if (vtx.y > g_BlockTex[nCnt].vtxMax.y)
			{
				g_BlockTex[nCnt].vtxMax.y = vtx.y;
			}

			if (vtx.y < g_BlockTex[nCnt].vtxMin.y)
			{
				g_BlockTex[nCnt].vtxMin.y = vtx.y;
			}
			// Z=============================
			if (vtx.z > g_BlockTex[nCnt].vtxMax.z)
			{
				g_BlockTex[nCnt].vtxMax.z = vtx.z;
			}

			if (vtx.z < g_BlockTex[nCnt].vtxMin.z)
			{
				g_BlockTex[nCnt].vtxMin.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		// ���_�o�b�t�@�̃A�����b�N
		g_BlockTex[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat; // �}�e���A���ւ̃|�C���^

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_BlockTex[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_BlockTex[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_BlockTex[nCnt].apTexture[nCntMat]);
			}
		}
	}
}
//==============================
// �u���b�N�̏I������
//==============================
void UninitBlock(void)
{
	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
	{
		// �e�N�X�`���̔j��
		for (int nCntTexture = 0; nCntTexture < BLOCK_TEXTURE; nCntTexture++)
		{
			if (g_BlockTex[nCntTex].apTexture[nCntTexture] != NULL)
			{
				g_BlockTex[nCntTex].apTexture[nCntTexture]->Release();
				g_BlockTex[nCntTex].apTexture[nCntTexture] = NULL;
			}
		}
		// ���b�V���̔j��
		if (g_BlockTex[nCntTex].pMesh != NULL)
		{
			g_BlockTex[nCntTex].pMesh->Release();
			g_BlockTex[nCntTex].pMesh = NULL;
		}
		// ���_�o�b�t�@�̉��
		if (g_BlockTex[nCntTex].pBuffMat != NULL)
		{
			g_BlockTex[nCntTex].pBuffMat->Release();
			g_BlockTex[nCntTex].pBuffMat = NULL;
		}
	}

	for (int nCntEdit = 0; nCntEdit < NUM_BLOCK; nCntEdit++)
	{
		for (int nCntTexture = 0; nCntTexture < BLOCK_TEXTURE; nCntTexture++)
		{
			if (g_Block[nCntEdit].tex.apTexture[nCntTexture] != NULL)
			{
				g_Block[nCntEdit].tex.apTexture[nCntTexture] = NULL;
			}
		}

		// ���b�V���̔j��
		if (g_Block[nCntEdit].tex.pMesh != NULL)
		{
			g_Block[nCntEdit].tex.pMesh = NULL;
		}
		// ���_�o�b�t�@�̉��
		if (g_Block[nCntEdit].tex.pBuffMat != NULL)
		{
			g_Block[nCntEdit].tex.pBuffMat = NULL;
		}
	}
}

//==============================
// �u���b�N�̍X�V����
//==============================
void UpdateBlock(void)
{
	// ����
}

//==============================
// �u���b�N�̕`�揈��
//==============================
void DrawBlock(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A���̕ۑ��p�ϐ�
	D3DMATERIAL9 matDef; // ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;  // �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{// ���g�p��ԂȂ�
			// ���̏�����ʂ����ɃJ�E���g��i�߂�
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);
		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlock].rot.y, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.z);
		D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y, g_Block[nCntBlock].pos.z);
		D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Block[nCntBlock].tex.pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Block[nCntBlock].tex.dwNumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Block[nCntBlock].tex.apTexture[nCntMat]);

			// ���f���i�p�[�c�j�̕`��
			g_Block[nCntBlock].tex.pMesh->DrawSubset(nCntMat);
		}

		// �}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//==============================
// �u���b�N�̐ݒ菈��
//==============================
void SetBlock(D3DXVECTOR3 pos,int nType)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		if (g_Block[nCnt].bUse == false)
		{// ���g�p��ԂȂ�
			g_Block[nCnt].pos = pos;				// ���W
			g_Block[nCnt].nType = nType;			// ���
			g_Block[nCnt].tex = g_BlockTex[nType];	// �e�N�X�`��
			g_Block[nCnt].bUse = true;				// �g�p���

			break;
		}
	}
}

//==============================
// �u���b�N�̓����蔻�菈��
//==============================
void CollisionBlock(D3DXVECTOR3* pPos,		// ���݂̈ʒu
					D3DXVECTOR3* pPosOld)	// �O��̈ʒu
{					
	Player* pPlayer = GetPlayer();			// �v���C���[�̎擾
	D3DXVECTOR3* posOld = pPosOld;			// �O�t���[���̃v���C���[�̈ʒu
	D3DXVECTOR3* pos = pPos;				// ���t���[���̃v���C���[�̈ʒu

	// �l�p�̓����蔻��
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		// �g�p��Ԃ̕��̂�
		if (g_Block[nCnt].bUse == true)
		{
			// �K�p���Ă���u���b�N�^�C�v
			if (g_Block[nCnt].nType == BLOCK_WALL00     || g_Block[nCnt].nType == BLOCK_WALL01     ||
				g_Block[nCnt].nType == BLOCK_HOUSE000_L || g_Block[nCnt].nType == BLOCK_HOUSE000_r ||
				g_Block[nCnt].nType == BLOCK_HOUSE01_L  || g_Block[nCnt].nType == BLOCK_HOUSE01_R  ||
				g_Block[nCnt].nType == BLOCK_HOUSE04_L  || g_Block[nCnt].nType == BLOCK_HOUSE04_R  ||
				g_Block[nCnt].nType == BLOCK_KURA       || g_Block[nCnt].nType == BLOCK_TORIGOYA   ||
				g_Block[nCnt].nType == BLOCK_KANBAN)
			{
				// ���E��O���̂߂荞�ݔ���
				if (pos->y< g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y)
				{
					// ���E�̂߂荞�ݔ���
					if (pos->z - OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z)			// �v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
					{

						if (posOld->x + OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)	// �w��������E�ɂ߂荞��
						{
							// pPlayer->pos�����f���̍����ɂ�������
							pos->x = g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x - OBJ_P - 0.1f;

						}
						if (posOld->x - OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x - OBJ_P < g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x)	// �w��������E�ɂ߂荞��
						{
							// pPlayer->pos�����f���̉E���ɂ�������
							pos->x = g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x + OBJ_P + 0.1f;
						}
					}

					// ��O���̂߂荞�ݔ���
					if (pos->x - OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)			// �v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
					{

						if (posOld->z + OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z)	// Z���������ɂ߂荞��
						{
							// pPlayer->pos�����f���̎�O���ɂ�������
							pos->z = g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z - OBJ_P - 0.1f;
						}
						if (posOld->z - OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z - OBJ_P < g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z)	// Z���ォ�牺�ɂ߂荞��
						{
							// pPlayer->pos�����f���̉����ɂ�������
							pos->z = g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z + OBJ_P + 0.1f;
						}
					}
				}
				//if (pos->z - OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z
				//	&& pos->x - OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)
				//{
				//	if (posOld->y + (OBJ_P * 2.0f) < g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y)	// �w��������E�ɂ߂荞��
				//	{
				//		// pPlayer->pos�����f���̉����ɂ�������
				//		pos->y = g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
				//	}
				//	if (posOld->y > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y && pos->y < g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y)	// �w��������E�ɂ߂荞��
				//	{
				//		// pPlayer->pos�����f���̏㑤�ɂ�������
				//		pos->y = g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y + 0.1f;
				//	}
				//}
			}
		}
	}

	// �~�̓����蔻��
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		// �g�p��Ԃ̕��̂�
		if (g_Block[nCnt].bUse == true)
		{
			// �K�p���Ă���u���b�N�^�C�v
			if (g_Block[nCnt].nType == BLOCK_WTPOLE || g_Block[nCnt].nType == BLOCK_WELL ||
				g_Block[nCnt].nType == BLOCK_IREIHI || g_Block[nCnt].nType == BLOCK_KUMO ||
				g_Block[nCnt].nType == BLOCK_KUMONOSU || g_Block[nCnt].nType == BLOCK_DEADTREE ||
				g_Block[nCnt].nType == BLOCK_SPEACAR)
			{
				// ���a�̎Z�o�ϐ�
				float PRadiusPos = 8.0f;
				float BRadiusPos = 8.0f;

				// �v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �u���b�N�ƃv���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - g_Block[nCnt].pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - g_Block[nCnt].pos.x;
				float fDisY = PlayerPos.y - g_Block[nCnt].pos.y;
				float fDisZ = PlayerPos.z - g_Block[nCnt].pos.z;

				// ��̔��a�����߂�
				float fRadX = PRadiusPos + BRadiusPos;

				// �v���C���[���͈͂ɓ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					pPlayer->pos.x = pPlayer->posOld.x;
					pPlayer->pos.y = pPlayer->posOld.y;
					pPlayer->pos.z = pPlayer->posOld.z;
				}
			}
		}
	}
}