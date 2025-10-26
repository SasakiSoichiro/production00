//***************************************
//
// ブロック管理処理 [blockManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************

//*******************
// インクルード
//*******************
#include "blockManager.h"

//*******************
// コンストラクタ
//*******************
CBlockManager::CBlockManager()
{
}

//*******************
// デストラクタ
//*******************
CBlockManager::~CBlockManager()
{
}

//*************
// 初期化処理
//*************
HRESULT CBlockManager::Init(void)
{

	return S_OK;
}

//*************
// 終了処理
//*************
void CBlockManager::Uninit(void)
{
}

//*************
// 更新処理
//*************
void CBlockManager::Update(void)
{
}

//**************
// 登録
//**************
void CBlockManager::Set(CBlock*block)
{
	m_Block.push_back(block);
}

//**********************
// 位置を返すあたり判定
//**********************
D3DXVECTOR3 CBlockManager::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	for (const auto& block : m_Block)
	{
		// ブロックの位置とモデル情報を取得
		D3DXVECTOR3 blockPos = block->GetPos();
		CXModel::XMODEL XModel = block->GetXModel();

		//左右手前奥のめり込み判定
		if (pos.y< blockPos.y + XModel.vtxMax.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)
		{
			//左右のめり込み判定
			if (pos.z - 25.0f< blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
			{

				if (posOld.x + 25.0f< blockPos.x + XModel.vtxMin.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの左側にくっつける
					pos.x = blockPos.x + XModel.vtxMin.x - 25.0f - 0.1f;
				}
				if (posOld.x - 25.0f > blockPos.x + XModel.vtxMax.x && pos.x - 25.0f < blockPos.x + XModel.vtxMax.x)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの右側にくっつける
					pos.x = blockPos.x + XModel.vtxMax.x + 25.0f + 0.1f;
				}
			}

			//手前奥のめり込み判定
			if (pos.x - 25.0f< blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
			{

				if (posOld.z + 25.0f< blockPos.z + XModel.vtxMin.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//Zが下から上にめり込んだ
				{
					//pPlayer->posをモデルの手前側にくっつける
					pos.z = blockPos.z + XModel.vtxMin.z - 25.0f - 0.1f;
					//return pos;
					
				}
				if (posOld.z - 25.0f > blockPos.z + XModel.vtxMax.z && pos.z - 25.0f < blockPos.z + XModel.vtxMax.z)//Zが上から下にめり込んだ
				{
					//pPlayer->posをモデルの奥側にくっつける
					pos.z = blockPos.z + XModel.vtxMax.z + 25.0f + 0.1f;
					
				}
			}

		}
		if (pos.z - 25.0f< blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z
			&& pos.x - 25.0f< blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)
		{
			if (posOld.y + (25.0f * 2.0f) < blockPos.y + XModel.vtxMin.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)//Ｘが左から右にめり込んだ
			{
				//pPlayer->posをモデルの下側にくっつける
				pos.y = blockPos.y + XModel.vtxMin.y - (25.0f * 2.0f) - 0.1f;
				
			}
			if (posOld.y > blockPos.y + XModel.vtxMax.y && pos.y < blockPos.y + XModel.vtxMax.y)//Ｘが左から右にめり込んだ
			{
				//pPlayer->posをモデルの上側にくっつける
				pos.y = blockPos.y + XModel.vtxMax.y + 0.1f;
				
			}

		}
		
	}

	return pos;
}

//**********************
// bool型のあたり判定
//**********************
bool CBlockManager::bCollision(D3DXVECTOR3 pos)
{
	for (const auto& block : m_Block)
	{
		D3DXVECTOR3 blockPos = block->GetPos();
		CXModel::XMODEL XModel = block->GetXModel();
		//左右手前奥のめり込み判定
		if (pos.y< blockPos.y + XModel.vtxMax.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)
		{
			//左右のめり込み判定
			if (pos.z - 25.0f < blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
			{

				if (pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの左側にくっつける
					pos.x = blockPos.x + XModel.vtxMin.x - 25.0f - 0.1f;
					return true;
				}
				if (pos.x - 25.0f < blockPos.x + XModel.vtxMax.x)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの右側にくっつける
					pos.x = blockPos.x + XModel.vtxMax.x + 25.0f + 0.1f;
					return true;
				}
			}

			//手前奥のめり込み判定
			if (pos.x - 25.0f < blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
			{

				if ( pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//Zが下から上にめり込んだ
				{
					//pPlayer->posをモデルの手前側にくっつける
					pos.z = blockPos.z + XModel.vtxMin.z - 25.0f - 0.1f;
					return true;

				}
				if ( pos.z - 25.0f < blockPos.z + XModel.vtxMax.z)//Zが上から下にめり込んだ
				{
					//pPlayer->posをモデルの奥側にくっつける
					pos.z = blockPos.z + XModel.vtxMax.z + 25.0f + 0.1f;
					return true;

				}
			}

		}
		if (pos.z - 25.0f < blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z
			&& pos.x - 25.0f < blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)
		{
			if ( pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)//Ｘが左から右にめり込んだ
			{
				//pPlayer->posをモデルの下側にくっつける
				pos.y = blockPos.y + XModel.vtxMin.y - (25.0f * 2.0f) - 0.1f;
				return true;

			}
			if ( pos.y < blockPos.y + XModel.vtxMax.y)//Ｘが左から右にめり込んだ
			{
				//pPlayer->posをモデルの上側にくっつける
				pos.y = blockPos.y + XModel.vtxMax.y + 0.1f;
				return true;

			}

		}

	}
	return false;
}