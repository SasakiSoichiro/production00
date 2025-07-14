//**********************************
//
// オブジェクト3D処理 [object3D.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "object3D.h"
#include "manager.h"
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
}
CObject3D::~CObject3D()
{

}
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D* pObject3D;
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pObject3D = new CObject3D;
		pObject3D->Init(pos);
		return pObject3D;
	}
	return NULL;
}

HRESULT CObject3D::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	D3DXVECTOR3 vec0, vec1, nor0, nor1;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\blue.JPG",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = m_pos.x - 150.0f;
	pVtx[0].pos.y = m_pos.y ;
	pVtx[0].pos.z = m_pos.z + 150.0f;
	pVtx[1].pos.x = m_pos.x + 150.0f;
	pVtx[1].pos.y = m_pos.y + 150.0f;
	pVtx[1].pos.z = m_pos.z + 150.0f;
	pVtx[2].pos.x = m_pos.x - 150.0f;
	pVtx[2].pos.y = m_pos.y + 150.0f;
	pVtx[2].pos.z = m_pos.z - 150.0f;
	pVtx[3].pos.x = m_pos.x + 150.0f;
	pVtx[3].pos.y = m_pos.y;
	pVtx[3].pos.z = m_pos.z - 150.0f;


	vec0 = pVtx[1].pos - pVtx[0].pos;
	vec1 = pVtx[2].pos - pVtx[0].pos;
	D3DXVec3Cross(&nor0, &vec0, &vec1);
	D3DXVec3Normalize(&nor0, &nor0);
	pVtx[0].nor = nor0;
	vec0 = pVtx[1].pos - pVtx[3].pos;
	vec1 = pVtx[2].pos - pVtx[3].pos;
	D3DXVec3Cross(&nor1, &vec0, &vec1);
	D3DXVec3Normalize(&nor1, &nor1);
	pVtx[3].nor = nor1;
	pVtx[1].nor = nor0 + nor1 / 2.0f;
	pVtx[2].nor = nor0 + nor1 / 2.0f;


	//頂点カラーの設定　　　　
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

void CObject3D::Uninit(void)
{

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}
void CObject3D::Update(void)
{

}
void CObject3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

float CObject3D::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ
	D3DXVECTOR3 nor,vtx0,norP[6];
	float fHeight=0.0f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	D3DXVECTOR3 vec1, vec2;
	// 1ポリゴン目
	vec1 = pVtx[1].pos - pVtx[0].pos;
	vec2 = pos - pVtx[0].pos;
	D3DXVec3Cross(&norP[0], &vec1, &vec2);

	vec1 = pVtx[2].pos - pVtx[1].pos;
	vec2 = pos - pVtx[1].pos;
	D3DXVec3Cross(&norP[1], &vec1, &vec2);

	vec1 = pVtx[0].pos - pVtx[2].pos;
	vec2 = pos - pVtx[2].pos;
	D3DXVec3Cross(&norP[2], &vec1, &vec2);

	// 2ポリゴン目
	vec1 = pVtx[3].pos - pVtx[2].pos;
	vec2 = pos - pVtx[2].pos;
	D3DXVec3Cross(&norP[3], &vec1, &vec2);

	vec1 = pVtx[2].pos - pVtx[1].pos;
	vec2 = pos - pVtx[1].pos;
	D3DXVec3Cross(&norP[4], &vec1, &vec2);

	vec1 = pVtx[1].pos - pVtx[3].pos;
	vec2 = pos - pVtx[3].pos;
	D3DXVec3Cross(&norP[5], &vec1, &vec2);

	if (0.0f < norP[0].y
		&& 0.0f < norP[1].y
		&& 0.0f < norP[2].y)
	{
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		nor = pVtx[0].nor;
		vtx0 = pVtx[0].pos;
		fHeight = vtx0.y -((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z)/nor.y;
	}
	else if (0.0f > norP[3].y
		&& 0.0f > norP[4].y
		&& 0.0f > norP[5].y)
	{
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		nor = pVtx[3].nor;
		vtx0 = pVtx[3].pos;
		fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	
	if (fHeight > 0.0f)
	{
		return fHeight;
	}
	return 0.0f;
}