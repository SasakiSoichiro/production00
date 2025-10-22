//**************************************
//
// ウェーブ処理 [wave.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _WAVE_H_ // このマクロ定義がされていなかったら
#define _WAVE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include <string>
#include "object2D.h"

class CNumber;

//********************
// ウェーブクラス
//********************
class CWave:public CObject2D
{
public:
	CWave(int nPriority = 6);	// コンストラクタ
	~CWave();					// デストラクタ
	static CWave* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	void Load(int nWave);			// 読み込み
	void Move(void);				// 動かす
private:
	static int m_nCurrent;	// 現在のウェーブ
	static int m_nAll;		// ウェーブの最大
	// ウェーブのファイル名
	std::string WAVE[3] =
	{
		"data\\WAVE\\wave00.txt",
		"data\\WAVE\\wave01.txt",
		"data\\WAVE\\wave02.txt",
	};
	int  m_nIdxTexture[2];		// 使っているテクスチャの番号
	static CNumber* m_pNumber;	// ナンバーへのポインタ
	int m_nScreenTime;			// ウェーブ数の表示時間
	bool m_bScreen;				// 表示しているか
	bool m_bGo;					// 始まり
	bool m_bStop;				// 止めているとき
	bool m_bEnd;				// 終わり
	float m_fCnt;				// カウント
};
#endif