//=============================================================================
//
//	���b�V���t�B�[���h���� [Meshfield.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "meshfield.h"
#include "meshwall.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_posMeshField;//�ʒu
D3DXVECTOR3 g_rotMeshField;//����
D3DXMATRIX g_mtxWorldMeshField;//���[���h�}�g���b�N�X

//=============================================================================
// ����������
//=============================================================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\grand.jpg",
		&g_pTextureMeshField);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^


//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPOS = 0;

	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, 1.0f, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
		}
	}


	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{//�e���_�̖@���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	int nCntTEX = 0;
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntTEX++)
		{
			pVtx[nCntTEX].tex = D3DXVECTOR2((1.0f / Xmesh) * nCntX, ((1.0f / Zmesh) * nCntZ));
		}
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	int nCntX{};
	int A[IDXCNT], B[IDXCNT];
	int nCnt = 0;


	for (nCnt = 0; nCnt < IDXCNT; nCnt++, nCntX++)
	{
		if (nCnt == 0)
		{
			A[nCnt] = (2 * XMESH) + 3;
			B[nCnt] = -XMESH - 1;
			pIdx[nCnt] = XMESH + 1;
		}
		else
		{
			A[nCnt] = -1 * (A[nCnt - 1]);

			B[nCnt] = B[nCnt - 1] + A[nCnt - 1];


			if (nCntX == 2 * (XMESH + 1))
			{
				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else if (nCntX == 2 * (XMESH + 1) + 1)
			{
				pIdx[nCnt] = pIdx[nCnt - 2] + B[nCnt - 2];
			}

			else if (nCntX == 2 * (XMESH + 1) + 2)
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
	g_pIdxBuffMeshField->Unlock();

}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshfield(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}


	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}


	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshfield(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VTXCNT, 0, POLYCNT);
}