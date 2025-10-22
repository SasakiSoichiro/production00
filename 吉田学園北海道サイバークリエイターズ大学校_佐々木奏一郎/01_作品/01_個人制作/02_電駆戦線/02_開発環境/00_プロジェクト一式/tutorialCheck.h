//**********************************************
// 
// チュートリアルのチェック処理 [tutorialCheck.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _TUTORIALCHECK_H_ // このマクロ定義がされていなかったら
#define _TUTORIALCHECK_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object2D.h"
#include "tutorial.h"

//********************************
// チュートリアルのチェッククラス
//********************************
class CTutorialCheck :public CObject2D
{
public:
	CTutorialCheck(int nPriority = 5);	// コンストラクタ
	~CTutorialCheck();					// デストラクタ
	static CTutorialCheck* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置設定
	void SetRot(D3DXVECTOR3 rot);	// 向き設定
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	void Clear(void);					// 項目の設定
private:
	CObject2D* m_pCheckBox;					// チェック項目表示のポインタ
	int  m_nIdxTextureCheck[2];				// テクスチャのインデックス
	int  m_nIdxTextureCheckBox[CTutorial::STATE_MAX];	// テクスチャのインデックス
	static const D3DXVECTOR2 SIZE_CHECK;	// 大きさ
	static const D3DXVECTOR2 SIZE_CHECKBOX;	// 大きさ
	static constexpr float boxOffset = 300.0f;
	bool m_bCheck;							// チェック
	int m_nCheckBox;						// チェック項目
	int m_nCnt;								// カウント
};
#endif