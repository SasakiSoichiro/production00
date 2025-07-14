//=============================================================================
//
//	���b�V���E�H�[������ [meshwall.h]
// Author : ���X�ؑt��Y
//
//=============================================================================

#include "meshwall.h"
#include"player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;
MeshWall g_MeshWall;

//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\wall004.png",
		&g_pTextureMeshWall);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^


//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPOS = 0;
	int radius = RADIUS;
	float Vmesh = (float)(VMESH);
	float Hmesh = (float)(HMESH);
	D3DXVECTOR3 nor;
	D3DXVECTOR3 vec1, vec2; // �x�N�g��
	// �O�ς����߂�


	int nCnt = 0;
	for (int nCntV = 0; nCntV < VMESH +1; nCntV++)
	{
		for (int nCntH = 0; nCntH < HMESH+1; nCntH++, nCnt++)
		{
			float Angle = ((D3DX_PI * 2) / (HMESH) * -nCntH)+D3DX_PI;
			pVtx[nCnt].pos = D3DXVECTOR3(sinf(-Angle) * radius, OBJ_V - ((OBJ_V/ VMESH) * nCntV), cosf(-Angle) * radius);
			//vec1= D3DXVECTOR3(0.0f, 0.0f, 0.0f)- pVtx[nCnt-1].pos;
			//vec2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f) - pVtx[nCnt].pos;
			//D3DXVec3Cross(&nor, &vec1, &vec2);
			nor = pVtx[nCnt].pos - D3DXVECTOR3(0.0f,0.0f,0.0f);
			D3DXVec3Normalize(&pVtx[nCnt].nor,&nor);
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.5f);
			pVtx[nCnt].tex = D3DXVECTOR2((1.0f / Vmesh) * nCntH, ((1.0f / Hmesh) * nCntH));
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX{};
	int A[IDXCNT], B[IDXCNT];


	for (nCnt = 0; nCnt < IDXCNT; nCnt++, nCntX++)
	{
		if (nCnt == 0)
		{
			A[nCnt] = (2 * HMESH) + 3;
			B[nCnt] = -HMESH - 1;
			pIdx[nCnt] = HMESH + 1;
		}
		else
		{
			A[nCnt] = -1 * (A[nCnt - 1]);

			B[nCnt] = B[nCnt - 1] + A[nCnt - 1];


			if (nCntX == 2 * (HMESH + 1))
			{
				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else if (nCntX == 2 * (HMESH + 1) + 1)
			{
				pIdx[nCnt] = pIdx[nCnt - 2] + B[nCnt - 2];
			}

			else if (nCntX == 2 * (HMESH + 1) + 2)
			{
				nCntX = 0;

				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else
			{
				pIdx[nCnt] = pIdx[nCnt - 1] + B[nCnt - 1];
			}

		}

	}

	//���_�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshWall->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}


	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}


	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshWall.mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshWall);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VTXCNT, 0, POLYCNT);
}

//=============================================================================
// �����蔻��
//=============================================================================
void CollisionCyrynder(void)
{

	int nCntPOS = 0;
	int radius = RADIUS;
	int nCntVtx[2] = {};
	float Vmesh = (float)(VMESH);
	float Hmesh = (float)(HMESH);
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3 nor[VMESH];
	D3DXVECTOR3 vec1[VMESH], vec2[HMESH]; // �x�N�g��

	for (int nCntVtx = 0; nCntVtx < VTXCNT; nCntVtx++)
	{
		float Angle = ((D3DX_PI * 2) / (HMESH) * -nCntVtx) + D3DX_PI;
		g_MeshWall.VtxPos[nCntVtx]= D3DXVECTOR3(sinf(-Angle) * radius, OBJ_V - ((OBJ_V / VMESH) * nCntVtx), cosf(-Angle) * radius);
	}
	for (int nCnt = 0; nCnt < VMESH; nCnt++)
	{
		
		nCntVtx[0] = nCnt % VMESH;
		nCntVtx[1] = (nCnt+1)%VMESH;
		vec1[nCnt] = g_MeshWall.VtxPos[nCntVtx[1]] - g_MeshWall.VtxPos[nCntVtx[0]];
		D3DXVec3Normalize(&vec1[nCnt], &vec1[nCnt]);
		vec2[nCnt] = pPlayer->pos - g_MeshWall.VtxPos[nCnt];
		D3DXVec3Normalize(&vec2[nCnt], &vec2[nCnt]);
		D3DXVec3Cross(&nor[nCnt], &vec1[nCnt], &vec2[nCnt]);
		D3DXVec3Normalize(&nor[nCnt], &nor[nCnt]);
		if (nor[nCnt].y < 0.0f)
		{
			pPlayer->pos.x = pPlayer->posOld.x;
			pPlayer->pos.z = pPlayer->posOld.z;
		}
	}
}