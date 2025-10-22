//**************************************
//
// ビルボード処理 [objectBillboard.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// インクルード
//*******************
#include "objectBillboard.h"
#include "manager.h"
#include "renderer.h"

//*******************
// コンストラクタ
//*******************
CObjectBillboard::CObjectBillboard(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_offset = D3DXVECTOR2(0.0f, 0.0f);
	m_mtxWorld = {};
}

//*******************
// デストラクタ
//*******************
CObjectBillboard::~CObjectBillboard()
{

}

//*******************
// 初期化処理
//*******************
HRESULT CObjectBillboard::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//各種変数の初期化
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-20.0f+ m_offset.x, 20.0f + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f + m_offset.x, 20.0f + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f + m_offset.x, -20.0f + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f + m_offset.x, -20.0f + m_offset.y, 0.0f);

	//各頂点の法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

//*******************
// 終了処理
//*******************
void CObjectBillboard::Uninit(void)
{
	//頂点バッファの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//*******************
// 更新処理
//*******************
void CObjectBillboard::Update(void)
{
}

//*******************
// 描画処理
//*******************
void CObjectBillboard::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	CTexture* pTexture = CManager::GetCTexture();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックス取得
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// 向きを反映
	D3DXMatrixRotationZ(&mtxRot, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &mtxRot, &m_mtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);//for文に入れる

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//for文に入れる

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*******************
// 位置設定
//*******************
void CObjectBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*******************
// 向き設定
//*******************
void CObjectBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//*********************
// テクスチャ座標設定
//*********************
void CObjectBillboard::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_3D* pVertex;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].tex = uv1;
	pVertex[1].tex = uv2;
	pVertex[2].tex = uv3;
	pVertex[3].tex = uv4;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*******************
// 色設定
//*******************
void CObjectBillboard::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_3D* pVertex;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//頂点座標の設定
	pVertex[0].col = col;
	pVertex[1].col = col;
	pVertex[2].col = col;
	pVertex[3].col = col;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*******************
// 大きさ設定
//*******************
void CObjectBillboard::SetSize(D3DXVECTOR2 size)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ
	m_size = size;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//*******************
// オフセットの設定
//*******************
void CObjectBillboard::SetOffset(D3DXVECTOR2 offset)
{
	VERTEX_3D* pVtx;//頂点情報へのポインタ
	m_offset = offset;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);	
	m_pVtxBuff->Unlock();

}