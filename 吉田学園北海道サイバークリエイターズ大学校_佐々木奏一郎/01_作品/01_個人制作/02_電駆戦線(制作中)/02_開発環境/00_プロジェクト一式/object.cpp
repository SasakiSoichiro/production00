//**********************************
//
// オブジェクト処理 [object.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "camera.h"
#include "manager.h"

//***********************
// 静的メンバ変数初期化
//***********************
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[MAX_PRI][MAX_OBJ] = {};
int CObject::m_nNumPriority[MAX_PRI] = {};

//******************
// コンストラクタ
//******************
CObject::CObject(int nPriority)
{

	for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{// NULLだったら
			m_apObject[nPriority][nCntObject] = this;	// 自分自身を代入
			m_nID = nCntObject;							// 自分自身のIDを保存
			m_nNumAll++;								// 総数をカウントアップ
			m_nNumPriority[nPriority]++;				// 描画順ごとの総数を足す
			break;
		}
	}
	m_nPriority = nPriority;// 描画順割り当て
	m_type = TYPE_NONE;		// タイプ設定
}
//******************
// デストラクタ
//******************
CObject::~CObject()
{
}

//******************
// 全ての更新
//******************
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULLじゃなかったら
				m_apObject[nCntPriority][nCntObject]->Update();// 更新
			}
		}

	}
}

//******************
// 全ての描画
//******************
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCCamera();	// カメラ情報取得
	pCamera->SetCamera();						// カメラを設定

	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULLじゃなかったら
				m_apObject[nCntPriority][nCntObject]->Draw();// 描画
			}
		}
	}
}

//******************
// 全ての終了
//******************
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULLじゃなかったら
				m_apObject[nCntPriority][nCntObject]->Uninit();// 終了
			}
		}
	}
}

//******************
// 終了
//******************
void CObject::Release(void)
{
	int nID = this->m_nID;				// 自分のIDを代入
	int nPriority = this->m_nPriority;	// 自分の描画順を割り当て

	if (m_apObject[nPriority][nID] != NULL)
	{// オブジェクトがNULLじゃなかったら

		delete m_apObject[nPriority][nID];	// デリート
		m_apObject[nPriority][nID] = NULL;	// NULLを代入
		m_nNumAll--;						// 総数をカウントダウン
		m_nNumPriority[nPriority]--;		// 描画順ごとの総数を減らす
	}
}

//******************
// タイプの割り当て
//******************
void CObject::SetType(CObject::TYPE type)
{
	m_type = type;// タイプを設定
}