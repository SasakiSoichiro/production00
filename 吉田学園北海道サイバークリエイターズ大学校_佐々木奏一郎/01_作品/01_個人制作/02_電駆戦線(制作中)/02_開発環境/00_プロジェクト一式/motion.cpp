//***************************************
// 
// メッシュフィールド処理[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// インクルード
//******************
#include "motion.h"

//*****************
// マクロ定義
//*****************
#define BLEND_FRAME (20)

//*****************
// コンストラクタ
//*****************
CMotion::CMotion()
{
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		m_apModel[nCnt]=NULL;
	}
	m_nNumModel=0;			
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_aInfo[nCnt] = {};
	}
	m_nNum=0;
	m_type=0;
	m_typeBlend = 0;
	m_bLoop=false;
	m_nNumKey=0;
	m_nKey=0;
	m_nCnt=0;
	m_nCntBlend = 0;
	m_bBlend = false;
	m_bFinish = false;
	m_nFrameBlend = 0;
	m_nKeyBlend = 0;
	m_nNumKeyBlend = 0;
	m_nCntMotionBlend = 0;
}

//*****************
// デストラクタ
//*****************
CMotion::~CMotion()
{
}

//*******************
// インスタンス生成
//*******************
CMotion*CMotion::Create(const char*pMotionScript)
{
	CMotion* pMotion;
	pMotion = new CMotion;
	pMotion->Init();
	pMotion->ReadScript(pMotionScript);
	return pMotion;
}

//*******************
// 初期化処理
//*******************
HRESULT CMotion::Init(void)
{

	return S_OK;
}

//*******************
// 終了処理
//*******************
void CMotion::Uninit(void)
{
	for (int nCnt = 0; nCnt < 20; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}
}

//*******************
// 更新処理
//*******************
void CMotion::Update(void)
{
	//答え格納用
	KEY k_Answer = {};
	float fRotX = 0.0f;
	float fRotY = 0.0f;
	float fRotZ = 0.0f;


	//計算用
	float fDiffMotionX;
	float fDiffMotionY;
	float fDiffMotionZ;

	float fRotXCurrent;
	float fRotYCurrent;
	float fRotZCurrent;

	float DiffMotionBlendX;
	float DiffMotionBlendY;
	float DiffMotionBlendZ;

	float fRotXBlend;
	float fRotYBlend;
	float fRotZBlend;

	float fDiffBlendX;
	float fDiffBlendY;
	float fDiffBlendZ;

	//m_nNumKey = m_aInfo[m_type].nNumKey;
	////m_typeOld = m_type;
	D3DXVECTOR3 ModelPos, ModelRot;
	//if (m_type != m_typeOld)
	//{
	//	m_nKey = 0;
	//	m_nCnt = 0;
	//}

	////全モデル(パーツ)の更新
	//for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	//{
	//	KEY k_Answer;

	//	//キー情報から位置.向きを算出
	//	k_Answer.fPosX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX);
	//	k_Answer.fPosY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY);
	//	k_Answer.fPosZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ);
	//	k_Answer.fRotX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotX);
	//	k_Answer.fRotY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotY);
	//	k_Answer.fRotZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ);

	//	//パーツの位置.向きを設定
	//	//位置
	//	//ModelPos.x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//ModelPos.y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//ModelPos.z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//m_apModel[nCntModel]->SetPos(ModelPos);
	//	//向き
	//	ModelRot.x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + k_Answer.fRotX * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//オフセット考慮
	//	ModelRot.y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + k_Answer.fRotY * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//オフセット考慮
	//	ModelRot.z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + k_Answer.fRotZ * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//オフセット考慮
	//	m_apModel[nCntModel]->SetRot(ModelRot);
	//}

	//if (m_aInfo[m_type].bLoop == false && m_nKey >= m_nNumKey - 1)
	//{
	//	m_type = TYPE_NEUTRAL;
	//}

	//if (m_aInfo[m_type].bLoop == false)
	//{
	//	if (m_nKey + 1 != m_nNumKey)
	//	{
	//		m_nCnt++;//再生フレーム数に達したら現在のキーを1つ進める
	//	}
	//}
	//else
	//{
	//	m_nCnt++;//再生フレーム数に達したら現在のキーを1つ進める
	//}

	//if (m_nCnt >= m_aInfo[m_type].aKeyInfo[m_nKey].nFlame)
	//{
	//	m_nCnt = 0;

	//	m_nKey += 1;
	//	if (m_nKey >= m_nNumKey)
	//	{
	//		m_nKey = 0;
	//	}
	//}
	m_nNumKey = m_aInfo[m_type].nNumKey;
	m_nNumKeyBlend = m_aInfo[m_typeBlend].nNumKey;


	//全モデル(パーツ)の更新
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		//現在のキー情報代入(ポイント
		KEY pKey = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel];
		//次のキー情報代入(ポイント
		KEY pKeyNext = m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel];

		//相対値
		float fRateMotion = m_nCnt / ((float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);

		//ブレンドするフレーム
		m_nFrameBlend = BLEND_FRAME;


		//ブレンドモーション処理
		if (m_bBlend == true)
		{//bBlendがtrueだったら


			//==========
			// 変数宣言
			//==========

			// ブレンド先の情報を代入
			// 現在のキー情報代入(ポイント
			KEY pKeyBlend = m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].aKey[nCntModel];								// 現在のキー

			// 次のキー情報代入(ポイント
			KEY pKeyNextBlend = m_aInfo[m_typeBlend].aKeyInfo[(m_nKeyBlend + 1) % m_nNumKeyBlend].aKey[nCntModel];	// 次のキー

			// 相対値
			float fRateMotionBlend = m_nCntMotionBlend / ((float)m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].nFlame);

			// ブレンドの相対値
			float fRateBlend = m_nCntBlend / ((float)m_nFrameBlend);



			// X軸の回転
			//=============================================================================================
			fDiffMotionX = pKeyNext.fRotX - pKey.fRotX;							// 次のキーとの差分
			fRotXCurrent = pKey.fRotX + (fDiffMotionX * fRateMotion);
			DiffMotionBlendX = pKeyNextBlend.fRotX - pKeyBlend.fRotX;
			fRotXBlend = pKeyBlend.fRotX + (DiffMotionBlendX * fRateMotionBlend);
			fDiffBlendX = fRotXBlend - fRotXCurrent;								// 差分
			fRotX = fRotXCurrent + (fDiffBlendX * fRateBlend);						// 求める値
			//=============================================================================================


			// Y軸の回転
			//=============================================================================================
			fDiffMotionY = pKeyNext.fRotY - pKey.fRotY;							// 次のキーとの差分
			fRotYCurrent = pKey.fRotY + (fDiffMotionY * fRateMotion);
			DiffMotionBlendY = pKeyNextBlend.fRotY - pKeyBlend.fRotY;
			fRotYBlend = pKeyBlend.fRotY + (DiffMotionBlendY * fRateMotionBlend);
			fDiffBlendY = fRotYBlend - fRotYCurrent;								// 差分
			fRotY = fRotYCurrent + (fDiffBlendY * fRateBlend);						// 求める値
			//=============================================================================================


			// Z軸の回転
			//=============================================================================================
			fDiffMotionZ = pKeyNext.fRotZ - pKey.fRotZ;							// 次のキーとの差分
			fRotZCurrent = pKey.fRotZ + (fDiffMotionZ * fRateMotion);
			DiffMotionBlendZ = pKeyNextBlend.fRotZ - pKeyBlend.fRotZ;
			fRotZBlend = pKeyBlend.fRotZ + (DiffMotionBlendZ * fRateMotionBlend);
			fDiffBlendZ = fRotZBlend - fRotZCurrent;								// 差分
			fRotZ = fRotZCurrent + (fDiffBlendZ * fRateBlend);						// 求める値
			//=============================================================================================

		}
		else
		{//ブレンド無し

			// キー情報から位置.向きを算出
			// 次のキーとの差分
			k_Answer.fPosX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX);
			k_Answer.fPosY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY);
			k_Answer.fPosZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ);
			fDiffMotionX = (pKeyNext.fRotX) - (pKey.fRotX);
			fDiffMotionY = (pKeyNext.fRotY) - (pKey.fRotY);
			fDiffMotionZ = (pKeyNext.fRotZ) - (pKey.fRotZ);

			//求める値
			fRotX = pKey.fRotX + fDiffMotionX * fRateMotion;
			fRotY = pKey.fRotY + fDiffMotionY * fRateMotion;
			fRotZ = pKey.fRotZ + fDiffMotionZ * fRateMotion;

		}


		//パーツの位置.向きを設定
		//位置
		//g_Enemy[nCntEnemy].aModel[nCntModel].pos.x = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.x + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));//オフセット考慮
		//g_Enemy[nCntEnemy].aModel[nCntModel].pos.y = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.y + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));
		//g_Enemy[nCntEnemy].aModel[nCntModel].pos.z = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.z + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));

		//向き
		ModelRot.x =fRotX;//オフセット考慮
		ModelRot.y =fRotY;//オフセット考慮
		ModelRot.z =fRotZ;//オフセット考慮
		m_apModel[nCntModel]->SetRot(ModelRot);
	}


	if (m_bBlend == true)
	{//ブレンドあり
		if (m_aInfo[m_typeBlend].bLoop == false)
		{//ループモーションじゃない場合

			if (m_nKeyBlend + 1 != m_nNumKeyBlend)
			{//キー総数に達していない場合

				m_nCntMotionBlend += 1;//再生フレーム数に達したら現在のキーを1つ進める

			}
			else
			{
				SetMotion(0);
			}
		}

		else
		{//ループモーションの場合

			m_nCntMotionBlend += 1;//カウントモーションを1つ進める

		}

		if (m_nCntMotionBlend >= (m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].nFlame))
		{//フレーム数を超えたら

			//カウントモーションを0にする
			m_nCntMotionBlend = 0;

			//現在のキーを1つ進める
			m_nKeyBlend += 1;

			if (m_nKeyBlend >= m_nNumKeyBlend)
			{//キー総数に達したら

				//現在のキーを0にする
				m_nKeyBlend = 0;
			}
		}

		//ブレンドカウントを1つ進める
		m_nCntBlend++;


		if (m_nCntBlend >= m_nFrameBlend)
		{//ブレンドのフレーム数に達したら

			//初期化＆通常モーションに情報を代入
			m_nCnt = m_nCntMotionBlend;
			m_nCntBlend = 0;
			m_type = m_typeBlend;
			m_nKey = m_nKeyBlend;
			m_bBlend = false;

		}

		if (m_aInfo[m_type].nNumKey - 1 <= m_nKey && m_aInfo[m_type].bLoop == false)
		{
			//m_typeBlend = TYPE_NEUTRAL;
			//m_bBlend = true;
			//m_nKeyBlend = 0;
			//m_nCntMotionBlend = 0;
			SetMotion(0);
		}
	}


	else
	{//ブレンドなし

		if (m_aInfo[m_type].bLoop == false)
		{//ループモーションじゃない場合

			if (m_nKey + 1 != m_nNumKey)
			{//キー総数に達していない場合

				m_nCnt++;// モーションカウントを1つ進める

			}
			else
			{
				SetMotion(0);
			}
		}


		else
		{//ループモーションの場合

			m_nCnt++;//モーションカウントを1つ進める
		}



		if (m_nCnt >= (m_aInfo[m_type].aKeyInfo[m_nKey].nFlame))
		{//フレーム数を超えたら

			//カウントモーションを0にする
			m_nCnt = 0;

			//現在のキーを1つ進める
			m_nKey += 1;

			if (m_nKey >= m_nNumKey)
			{//キー総数に達したら

				//現在のキーを0にする
				m_nKey = 0;

			}
		}
	}
}

//*******************
// 描画処理
//*******************
void CMotion::Draw(void)
{
	// 全てのモデルの描画
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// モデルの描画
		m_apModel[nCnt]->Draw();
	}
}

//*******************
// モーションの設定
//*******************
void CMotion::SetMotion(int type)
{
	if (m_type != type)
	{// 現在のモーションとちがっていたとき
		m_typeBlend = type;		// 現在のモーションに設定
		m_bBlend = true;		// ブレンドありに設定
		m_nKeyBlend = 0;		// キーリセット
		m_nCntMotionBlend = 0;	// カウントモーションリセット
	}
}

//******************************
// モーションファイルの読み込み
//******************************
void CMotion::ReadScript(const char* pMotionScript)
{
	FILE* pFile = NULL;
	pFile = fopen(pMotionScript, "r");

	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	int nParent;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;

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
											m_apModel[nCntParts]->SetPos(pos);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &rot.x);
											fscanf(pFile, "%f", &rot.y);
											fscanf(pFile, "%f", &rot.z);
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
									m_aInfo[nCntMotion].bLoop = false;
								}
								else
								{
									m_aInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &m_aInfo[nCntMotion].nNumKey);

								while (nCntKey < m_aInfo[nCntMotion].nNumKey)
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
												fscanf(pFile, "%d", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
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
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
								nCntMotion++;
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