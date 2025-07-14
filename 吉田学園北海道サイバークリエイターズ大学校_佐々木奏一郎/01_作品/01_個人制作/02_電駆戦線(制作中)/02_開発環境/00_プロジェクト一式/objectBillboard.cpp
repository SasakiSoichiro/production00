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
//=================
// コンストラクタ
//=================
CObjectBillboard::CObjectBillboard(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
}

//=================
// デストラクタ
//=================
CObjectBillboard::~CObjectBillboard()
{

}

CObjectBillboard* CObjectBillboard::Create(D3DXVECTOR3 pos)
{
	CObjectBillboard* pCObjectBillboard;
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pCObjectBillboard = new CObjectBillboard;
		pCObjectBillboard->Init(pos);
		pCObjectBillboard->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\pause000.png");
		return pCObjectBillboard;
	}
	return NULL;
}
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

	pVtx[0].pos = D3DXVECTOR3(-20.0f, 20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f, 20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, -20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f, -20.0f, 0.0f);

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
	return TRUE;
}

void CObjectBillboard::Uninit(void)
{

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//頂点バッファの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}
void CObjectBillboard::Update(void)
{
}
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


	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);//for文に入れる

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//for文に入れる

	//ライトを有効に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}