//*****************************************
//
// エネミー処理 [enemy.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "enemychild.h"
#include "game.h"
#include "score.h"
#include "combo.h"
#include "mesh.h"
#include "enemyLifeManager.h"

//*******************
// マクロ定義
//*******************
#define SPEED (8.0f)	// プレイヤーの移動速度
#define NUMMODEL (15)	// モデルのパーツ数
#define DEST (0.3f)

//*****************
// 静的メンバ変数
//*****************
int CEnemy::m_nNumAll = 0;

//*****************
// コンストラクタ
//*****************
CEnemy::CEnemy(int nPriority) :CObject(nPriority)
{
	// 変数のクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_speed = 0;
	m_nLife = 0;
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_nLife = 0;
	m_State = STATE_NONE;
	m_pMotion = NULL;
	for (int nCnt = 0; nCnt < NUMMODEL; nCnt++)
	{
		m_apModel[nCnt] = NULL;
	}
	m_nNumModel = 0;
	m_Machine = NULL;
	m_nNumAll++;
	m_nType = 0;
	m_pLifeManager = NULL;
}

//*****************
// デストラクタ
//*****************
CEnemy::~CEnemy()
{
	m_nNumAll--;
}

//******************
// インスタンス生成
//*******************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos,int nType)
{
	// 自身のポインタ
	CEnemy* pEnemy = NULL;
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();
	// 現在のオブジェクトの総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		switch (nType)
		{// インスタンス生成
		case TYPE_SPIDER:
			pEnemy = new CSpiderEnemy;	
			pEnemy->m_nType = TYPE_SPIDER;
			break;
		case TYPE_FANMOTOR:
			pEnemy = new CFanmotorEnemy;
			pEnemy->m_nType = TYPE_FANMOTOR;
			break;
		}
		
		// 初期化
		pEnemy->Init(pos);		

		return pEnemy;
	}

	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	// 初期設定
	m_pos = pos;							
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_speed = 0.0f;							
	m_nLife = initLife;	
	// ステートマシン生成
	m_Machine = new CStateMachine;
	// ライフマネージャー生成
	m_pLifeManager = CEnemyLifeManager::Create(pos, initLife);
	// ニュートラル状態
	CNuetoralState* pNuetoralState = new CNuetoralState;
	ChangeState(pNuetoralState);

	return S_OK;
}

//***********
// 終了処理
//***********
void CEnemy::Uninit(void)
{
	m_pMotion->Uninit();
	delete m_pMotion;
	m_pMotion = NULL;
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = NULL;
	}
	m_Machine->Uninit();
	delete 	m_Machine;
	m_Machine = NULL;

	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos = m_pos;// 現在の位置を代入
	// 前フレームの位置情報保存
	m_oldPos = m_pos;

	// メッシュ情報の取得
	CMesh* pMesh = CGame::GetCMesh();
	// 高さ情報の取得
	pos.y = pMesh->GetHeight(pos);
	// 位置を設定
	SetPos(pos);
	pos.y += 90.0f;
	// モーションとステートマシンの更新
	m_pMotion->Update();
	m_Machine->Update();

	// ライフの設定
	m_pLifeManager->SetPos(pos);
	m_pLifeManager->SetLife(m_nLife);

	// 体力0以下で終了
	if (m_nLife <= 0)
	{
		CCombo::Add(400);
		m_pLifeManager->Uninit();
		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CEnemy::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	if (m_nType == TYPE_SPIDER)
	{
		CMesh* pMesh = CGame::GetCMesh();

		// モデルの上ベクトル
		D3DXVECTOR3 vecU = pMesh->GetNormal(m_pos);

		m_vecU += (vecU - m_vecU) * DEST;

		D3DXVECTOR3 vecF = -(m_pos - m_oldPos);

		D3DXVec3Normalize(&vecF, &vecF);

		if (D3DXVec3LengthSq(&vecF) > 0.001f)
		{
			m_vecF = vecF;
		}

		D3DXVECTOR3 baseForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXMATRIX rotMtx;
		D3DXMatrixRotationAxis(&rotMtx, &vecU, m_rot.y);

		D3DXVec3TransformNormal(&m_vecF, &baseForward, &rotMtx);


		D3DXVECTOR3 vecR, vecFa;
		D3DXVec3Cross(&vecR, &vecU, &m_vecF);
		D3DXVec3Normalize(&vecR, &vecR);
		m_vecR += (vecR - m_vecR) * DEST;
		D3DXVec3Cross(&m_vecF, &vecR, &vecU);
		D3DXVec3Normalize(&vecFa, &m_vecF);
		m_vecF += (vecFa - m_vecF) * DEST;
		D3DXMatrixIdentity(&m_mtxWorld);

		// ワールドマトリックスの更新
		m_mtxWorld._11 = m_vecR.x;
		m_mtxWorld._12 = m_vecR.y;
		m_mtxWorld._13 = m_vecR.z;
		m_mtxWorld._14 = 0;
		m_mtxWorld._21 = m_vecU.x;
		m_mtxWorld._22 = m_vecU.y;
		m_mtxWorld._23 = m_vecU.z;
		m_mtxWorld._24 = 0;
		m_mtxWorld._31 = m_vecF.x;
		m_mtxWorld._32 = m_vecF.y;
		m_mtxWorld._33 = m_vecF.z;
		m_mtxWorld._34 = 0;
		m_mtxWorld._41 = m_pos.x;
		m_mtxWorld._42 = m_pos.y;
		m_mtxWorld._43 = m_pos.z;
		m_mtxWorld._44 = 1;
	}
	else
	{
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
	}

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 全てのモデルの描画
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}


}

//******************
// 位置の設定
//*******************
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// 向きの設定
//*******************
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

bool CEnemy::Distance(float fDistance)
{
	// プレイヤーの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーとの距離計算
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	if (fDistance > fRadius)
	{// 範囲内
		return true;
	}
	return false;
}

//**********************
// モーションの読み込み
//**********************
void CEnemy::LoadMotion(const char* pMotionScript)
{
	FILE* pFile = NULL;
	pFile = fopen(pMotionScript, "r");

	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	int nParent;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;
	CMotion::MOTION_INFO Info;

	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納

		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);


			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &str[0]);
						fscanf(pFile, "%d", &m_nNumModel);
						while (nCntModel < m_nNumModel)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &FileName[nCntModel][0]);
								m_apModel[nCntModel] = CModel::Create(pos, FileName[nCntModel]);
								nCntModel++;
							}
						}
					}

					if (strcmp(aString, "CHARACTERSET") == 0)
					{
						while (1)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &m_nNumModel);

							}
							while (nCntParts < m_nNumModel)
							{
								//ファイルを読み込む
								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(aString, "PARTSSET") == 0)
								{
									while (1)
									{
										//ファイルを読み込む
										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(aString, "INDEX") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nIdx);
										}
										else if (strcmp(aString, "PARENT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nParent);
											if (nParent != -1)
											{
												m_apModel[nIdx]->SetParent(m_apModel[nParent]);
											}
										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &pos.x);
											fscanf(pFile, "%f", &pos.y);
											fscanf(pFile, "%f", &pos.z);
											m_apModel[nCntParts]->SetOffSetPos(pos);
											m_apModel[nCntParts]->SetPos(pos);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &rot.x);
											fscanf(pFile, "%f", &rot.y);
											fscanf(pFile, "%f", &rot.z);
											m_apModel[nCntParts]->SetOffSetRot(rot);
											m_apModel[nCntParts]->SetRot(rot);
										}
										else if (strcmp(aString, "END_PARTSSET") == 0)
										{
											nCntParts++;
											break;
										}
									}

								}

							}
							if (strcmp(aString, "END_CHARACTERSET") == 0)
							{
								break;
							}

						}
					}
					if (strcmp(aString, "MOTIONSET") == 0)
					{
						if (m_pMotion == NULL)
						{
							m_pMotion = CMotion::Create(&m_apModel[0], m_nNumModel,true);
						}
						while (1)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &nBool);
								if (nBool == 0)
								{
									Info.bLoop = false;
								}
								else
								{
									Info.bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &Info.nNumKey);

								while (nCntKey < Info.nNumKey)
								{
									//ファイルを読み込む
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(aString, "KEYSET") == 0)
									{
										nCntParts = 0;
										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "FRAME") == 0)
											{
												fscanf(pFile, "%s", &str[0]);
												fscanf(pFile, "%d", &Info.aKeyInfo[nCntKey].nFlame);
												break;
											}
										}

										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "KEY") == 0)
											{
												while (1)
												{
													//ファイルを読み込む
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(aString, "POS") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
													}
													if (strcmp(aString, "END_KEY") == 0)
													{
														nCntParts++;
														break;
													}
												}
											}
											if (strcmp(aString, "END_KEYSET") == 0)
											{
												nCntKey++;
												break;
											}

										}
									}


								}

							}

							if (strcmp(aString, "END_MOTIONSET") == 0)
							{
								if (m_pMotion != NULL)
								{
									m_pMotion->SetInfo(Info);
								}
								nCntKey = 0;
								break;
							}
						}
					}
					if (strcmp(aString, "END_SCRIPT") == 0)
					{
						break;
					}
				}
				break;

			}
		}
	}
}

//****************
// ステートの変更
//****************
void CEnemy::ChangeState(CEnemyStateBase* pState)
{
	pState->SetOwner(this);
	m_Machine->ChangeState(pState);
}