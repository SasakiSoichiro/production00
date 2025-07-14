////==========================================
////
////		���f��			model.cpp
////			ryuusei hirata
////
////=========================================
//#include "main.h"
//#include "model.h"
//#include "input.h"
//
////	�O���o�[��
//Model g_Model[MODELTYPE_MAX][MAX_MODEL];
//
////========================
////		����������
////========================
//void InitModel(void)
//{
//	//	�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//	D3DXMATERIAL* pMat;
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//			g_Model[nCnt][nCNt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model[nCnt][nCNt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_Model[nCnt][nCNt].bUse = false;
//			g_Model[nCnt][nCNt].nType = MODELTYPE_0;
//		}
//	}
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//
//			//	X�t�@�C���̓ǂݍ���
//			D3DXLoadMeshFromX(MODEL[nCnt],
//				D3DXMESH_SYSTEMMEM,
//				pDevice,
//				NULL,
//				&g_Model[nCnt][nCNt].pBuffMat,
//				NULL,
//				&g_Model[nCnt][nCNt].dwNumMat,
//				&g_Model[nCnt][nCNt].pMesh);
//		}
//	}
//
//	int nNumVtx;
//	DWORD sizeFVF;
//	BYTE* pVtxBuff;
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//			nNumVtx = g_Model[nCnt][nCNt].pMesh->GetNumVertices();
//			sizeFVF = D3DXGetFVFVertexSize(g_Model[nCnt][nCNt].pMesh->GetFVF());
//
//			g_Model[nCnt][nCNt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//			for (int i = 0; i < nNumVtx; i++)
//			{
//				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//				if (vtx.x > g_Model[nCnt][nCNt].vtxMax.x)
//				{
//					g_Model[nCnt][nCNt].vtxMax.x = vtx.x;
//				}
//
//				if (vtx.y > g_Model[nCnt][nCNt].vtxMax.y)
//				{
//					g_Model[nCnt][nCNt].vtxMax.y = vtx.y;
//				}
//
//				if (vtx.z > g_Model[nCnt][nCNt].vtxMax.z)
//				{
//					g_Model[nCnt][nCNt].vtxMax.z = vtx.z;
//				}
//
//				if (vtx.x < g_Model[nCnt][nCNt].vtxMin.x)
//				{
//					g_Model[nCnt][nCNt].vtxMin.x = vtx.x;
//				}
//
//				if (vtx.y < g_Model[nCnt][nCNt].vtxMin.y)
//				{
//					g_Model[nCnt][nCNt].vtxMin.y = vtx.y;
//				}
//
//				if (vtx.z < g_Model[nCnt][nCNt].vtxMin.z)
//				{
//					g_Model[nCnt][nCNt].vtxMin.z = vtx.z;
//				}
//
//				pVtxBuff += sizeFVF;
//			}
//			g_Model[nCnt][nCNt].pMesh->UnlockVertexBuffer();
//		}
//	}
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//			//	�e�N�X�`���̓ǂݍ���
//			pMat = (D3DXMATERIAL*)g_Model[nCnt][nCNt].pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_Model[nCnt][nCNt].dwNumMat; nCntMat++)
//			{
//				if (pMat[nCntMat].pTextureFilename != NULL)
//				{
//					D3DXCreateTextureFromFile(pDevice,
//						pMat[nCntMat].pTextureFilename,
//						&g_Model[nCnt][nCNt].apTexture[nCntMat]);
//				}
//			}
//		}
//	}
//}
//
////========================
////		�I������
////========================
//void UninitModel(void)
//{
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//
//			//	���b�V���̔j��
//			if (g_Model[nCnt][nCNt].pMesh != NULL)
//			{
//				g_Model[nCnt][nCNt].pMesh->Release();
//				g_Model[nCnt][nCNt].pMesh = NULL;
//			}
//		}
//	}
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//
//			//	�}�e���A���̔j��
//			if (g_Model[nCnt][nCNt].pBuffMat != NULL)
//			{
//				g_Model[nCnt][nCNt].pBuffMat->Release();
//				g_Model[nCnt][nCNt].pBuffMat = NULL;
//			}
//		}
//	}
//}
//
////========================
////		�X�V����
////========================
//void UpdateModel(void)
//{
//
//}
//
////=======================
////		�`�揈��
////=======================
//void DrawModel(void)
//{
//	//	�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;
//	D3DMATERIAL9 matDef;
//	D3DXMATERIAL* pMat;
//
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//
//			if (g_Model[nCnt][nCNt].bUse == true)
//			{
//
//				//	���[���h�}�g���b�N�X�̏�����
//				D3DXMatrixIdentity(&g_Model[nCnt][nCNt].mtxWorld);
//
//				//	�������f
//				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCnt][nCNt].rot.y, g_Model[nCnt][nCNt].rot.x, g_Model[nCnt][nCNt].rot.z);
//				D3DXMatrixMultiply(&g_Model[nCnt][nCNt].mtxWorld, &g_Model[nCnt][nCNt].mtxWorld, &mtxRot);
//
//				//	�ʒu�̔��f
//				D3DXMatrixTranslation(&mtxTrans, g_Model[nCnt][nCNt].pos.x, g_Model[nCnt][nCNt].pos.y, g_Model[nCnt][nCNt].pos.z);
//				D3DXMatrixMultiply(&g_Model[nCnt][nCNt].mtxWorld, &g_Model[nCnt][nCNt].mtxWorld, &mtxTrans);
//
//				//	���[���h�}�g���b�N�X�̐ݒ�
//				pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCnt][nCNt].mtxWorld);
//
//				//	���݂̃}�e���A����ۑ�
//				pDevice->GetMaterial(&matDef);
//
//				//	�}�e���A���f�[�^�ւ̃|�C���^���[���擾
//				pMat = (D3DXMATERIAL*)g_Model[nCnt][nCNt].pBuffMat->GetBufferPointer();
//
//				//	�`��
//				for (int nCntMat = 0; nCntMat < (int)g_Model[nCnt][nCNt].dwNumMat; nCntMat++)
//				{
//					//	�}�e���A���̐ݒ�
//					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//					//	�e�N�X�`���̐ݒ�
//					pDevice->SetTexture(0, g_Model[nCnt][nCNt].apTexture[nCntMat]);
//
//					//	���f���̕`��
//					g_Model[nCnt][nCNt].pMesh->DrawSubset(nCntMat);
//				}
//
//				//	�ۑ������}�e���A����߂�
//				pDevice->SetMaterial(&matDef);
//
//			}
//		}
//	}
//}
//
//void SetModel(D3DXVECTOR3 pos,int nType)
//{
//	for (int nCntBuilding = 0; nCntBuilding < MAX_MODEL; nCntBuilding++)
//	{
//		if (g_Model[nType][nCntBuilding].bUse == false)
//		{
//			g_Model[nType][nCntBuilding].pos = pos;
//			g_Model[nType][nCntBuilding].nType = nType;
//			g_Model[nType][nCntBuilding].bUse = true;
//			break;
//		}
//	}
//
//}