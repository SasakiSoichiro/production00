//*****************************************
//
// アイテム処理 [item.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "itemskill.h"
#include "itemmanager.h"

//*****************
// コンストラクタ
//*****************
CItem::CItem(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// デストラクタ
//*****************
CItem::~CItem()
{
}

//******************
// インスタンス生成
//*******************
CItem* CItem::Create(D3DXVECTOR3 pos,int nType)
{
	// 自身のポインタ取得
	CItem* pItem;
	// XModelの取得
	CXModel* pXModel = CManager::GetCXModel();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合
		// インスタンス生成
		pItem = new CItem;	
		// 使うモデルのインデックスを入れる
		pItem->m_nIdxXFile = pXModel->Register("data\\MODEL\\adjust.x");
		pItem->Init(pos);

		return pItem;			
	}

	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CItem::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();

	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CItem::Update(void)
{
	// プレイヤーのアイテム情報取得	
	CPlayer* pPlayer = CGame::GetCPlayer();
	CItemManager* pItemManager=pPlayer->GetItemManager();
	// プレイヤーが範囲内に入ったら取得
	pItemManager->SetItem(Collision(pPlayer->GetPos()));

	// 回転させる
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
}

//*****************
// 描画処理
//*****************
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CItem::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CItem::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CItem::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// 向き情報の取得
//******************
D3DXVECTOR3 CItem::GetRot(void)
{
	return CObjectX::GetRot();
}

//******************
// あたり判定
//******************
CItemSkill* CItem::Collision(D3DXVECTOR3 pos)
{
	// アイテムの周りに4点設置
	D3DXVECTOR3 itemPos[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		itemPos[nCnt] = GetPos();
	}
	itemPos[0].x -= size;
	itemPos[0].z -= size;

	itemPos[1].x += size;
	itemPos[1].z -= size;

	itemPos[2].x += size;
	itemPos[2].z += size;

	itemPos[3].x -= size;
	itemPos[3].z += size;

	D3DXVECTOR3 Vec[4];
	D3DXVECTOR3 VecP[4];
	D3DXVECTOR3 nor[4];

	// プレイヤーとの距離
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Vec[nCnt] = itemPos[(nCnt+1)%4] - itemPos[nCnt];
		VecP[nCnt] = pos - itemPos[nCnt];
		D3DXVec3Cross(&nor[nCnt], &VecP[nCnt], &Vec[nCnt]);
	}

	if (nor[0].y > 0.0f&&nor[1].y > 0.0f && nor[2].y > 0.0f && nor[3].y > 0.0f)
	{// プレイヤーが範囲内だったら終了
		Uninit();
		return CItemSkill::Create(0);
	}
	else
	{
		return NULL;
	}
}