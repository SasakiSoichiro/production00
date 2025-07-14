//=============================================================================
//
//	メッシュフィールド処理 [Meshfield.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "meshfield.h"
#include "meshwall.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_posMeshField;//位置
D3DXVECTOR3 g_rotMeshField;//向き
D3DXMATRIX g_mtxWorldMeshField;//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\grand.jpg",
		&g_pTextureMeshField);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ


//頂点バッファをロックし、頂点情報へのポインタを取得
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
	{//各頂点の法線の設定
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


	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();

	//インデックスバッファをロック
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

	//頂点バッファをアンロックする
	g_pIdxBuffMeshField->Unlock();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshfield(void)
{

	//テクスチャの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}


	//頂点バッファの解放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}


	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshfield(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshField);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VTXCNT, 0, POLYCNT);
}