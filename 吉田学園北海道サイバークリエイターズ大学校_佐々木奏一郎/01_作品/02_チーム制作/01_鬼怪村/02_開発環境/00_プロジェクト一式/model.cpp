////==========================================
////
////		モデル			model.cpp
////			ryuusei hirata
////
////=========================================
//#include "main.h"
//#include "model.h"
//#include "input.h"
//
////	グロバール
//Model g_Model[MODELTYPE_MAX][MAX_MODEL];
//
////========================
////		初期化処理
////========================
//void InitModel(void)
//{
//	//	デバイスの取得
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
//			//	Xファイルの読み込み
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
//			//	テクスチャの読み込み
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
////		終了処理
////========================
//void UninitModel(void)
//{
//	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
//	{
//		for (int nCNt = 0; nCNt < MAX_MODEL; nCNt++)
//		{
//
//			//	メッシュの破棄
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
//			//	マテリアルの破棄
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
////		更新処理
////========================
//void UpdateModel(void)
//{
//
//}
//
////=======================
////		描画処理
////=======================
//void DrawModel(void)
//{
//	//	デバイスの取得
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
//				//	ワールドマトリックスの初期化
//				D3DXMatrixIdentity(&g_Model[nCnt][nCNt].mtxWorld);
//
//				//	向き反映
//				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model[nCnt][nCNt].rot.y, g_Model[nCnt][nCNt].rot.x, g_Model[nCnt][nCNt].rot.z);
//				D3DXMatrixMultiply(&g_Model[nCnt][nCNt].mtxWorld, &g_Model[nCnt][nCNt].mtxWorld, &mtxRot);
//
//				//	位置の反映
//				D3DXMatrixTranslation(&mtxTrans, g_Model[nCnt][nCNt].pos.x, g_Model[nCnt][nCNt].pos.y, g_Model[nCnt][nCNt].pos.z);
//				D3DXMatrixMultiply(&g_Model[nCnt][nCNt].mtxWorld, &g_Model[nCnt][nCNt].mtxWorld, &mtxTrans);
//
//				//	ワールドマトリックスの設定
//				pDevice->SetTransform(D3DTS_WORLD, &g_Model[nCnt][nCNt].mtxWorld);
//
//				//	現在のマテリアルを保存
//				pDevice->GetMaterial(&matDef);
//
//				//	マテリアルデータへのポインタあーを取得
//				pMat = (D3DXMATERIAL*)g_Model[nCnt][nCNt].pBuffMat->GetBufferPointer();
//
//				//	描画
//				for (int nCntMat = 0; nCntMat < (int)g_Model[nCnt][nCNt].dwNumMat; nCntMat++)
//				{
//					//	マテリアルの設定
//					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//					//	テクスチャの設定
//					pDevice->SetTexture(0, g_Model[nCnt][nCNt].apTexture[nCntMat]);
//
//					//	モデルの描画
//					g_Model[nCnt][nCNt].pMesh->DrawSubset(nCntMat);
//				}
//
//				//	保存したマテリアルを戻す
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