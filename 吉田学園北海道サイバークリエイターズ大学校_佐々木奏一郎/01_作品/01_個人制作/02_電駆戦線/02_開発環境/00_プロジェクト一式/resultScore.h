//**************************************
//
// リザルトスコア処理 [resultScore.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RESULTSCORE_H_ // このマクロ定義がされていなかったら
#define _RESULTSCORE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

class CNumber;

//*****************
// マクロ定義
//*****************
#define MAX_DIGIT (8)// 最大桁数

//**********************
// リザルトスコアクラス
//**********************
class CResultScore :public CObject
{
public:
	CResultScore(int nPriority = 5);// コンストラクタ
	~CResultScore();				// デストラクタ
	static CResultScore* Create(D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);					// 初期化
	void Uninit(void);								// 終了
	void Update(void);								// 更新
	void Draw(void);								// 描画
	void SetPos(D3DXVECTOR3 pos);					// 位置
	void SetRot(D3DXVECTOR3 rot);					// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置情報の取得
	D3DXVECTOR2 GetSize(void) { return m_size; }	// 大きさ情報の取得
	int Digit(int nScore);							// 桁数情報の取得

private:
	int  m_nIdxTexture;						// テクスチャのインデックス
	static CNumber* m_apNumber[MAX_DIGIT];	// ナンバーへのポインタ
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR2 m_size;						// 大きさ
	int m_nScore;							// スコア
};
#endif