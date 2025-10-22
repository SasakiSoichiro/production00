//***************************************
// 
// 影処理[shadowS.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// インクルード
//******************
#include "shadowS.h"
#include "manager.h"
#include "renderer.h"

//****************
// コンストラクタ
//****************
CShadowS::CShadowS(int nPriority) : CObjectX(nPriority)
{
	m_pVtxBuff = NULL;						// 頂点バッファ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_nIdxXFile = 0;
}

//****************
// デストラクタ
//****************
CShadowS::~CShadowS()
{

}

//*******************
// インスタンス生成
//*******************
CShadowS* CShadowS::Create(D3DXVECTOR3 pos)
{
	CShadowS* pMesh;// メッシュ情報取得
	CTexture* pTexture = CManager::GetCTexture();// テクスチャ情報の取得

	// 現在のオブジェクト総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数に達していなかったら

		// インスタンス生成
		pMesh = new CShadowS;
		// 初期化
		pMesh->Init(pos);
		// pMeshを渡す
		return pMesh;
	}

	//(失敗したら)NULLを返す
	return NULL;
}

//**************
// 初期化
//**************
HRESULT CShadowS::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();


	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\shadow.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);//←右回りで設定する
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, -0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定　　　　
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();



	return S_OK;
}

//**************
// 終了処理
//**************
void CShadowS::Uninit(void)
{
	//頂点バッファの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// 終了処理
	CObjectX::Uninit();
}

//**************
// 更新
//**************
void CShadowS::Update(void)
{

}

//**************
// 描画
//**************
void CShadowS::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// Zバッファの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// カラーバッファへの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// ス:合格　Z:合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);	// ス:合格　Z:不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT);	// ス:不合格

	// 表面をカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// カリングの設定

	 //影モデルを描画
	CObjectX::Draw();

	// ステンシルバッファの参照値を設定("1"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// ス:合格　Z:合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ス:合格　Z:不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// ス:不合格

	// 裏面をカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングの設定

	// 影モデルの描画
	CObjectX::Draw();

	// カラーバッファへの書き込みを有効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000F);

	// ステンシルバッファの参照値を設定する("2"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//ステンシルバッファの比較パラメータを設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// ス:合格　Z:合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	// ス:合格　Z:不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	// ス:不合格

	// 画面の大きさの黒いポリゴンを描画
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// すべて元に戻す
	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	// Zバッファの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ステンシルバッファの参照値を設定する("2"にする)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x00);
}

void CShadowS::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}