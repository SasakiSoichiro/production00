//************************************
//
// リザルト処理 [result.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _RESULT_H_ // このマクロ定義がされていなかったら
#define _RESULT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "scene.h"

//********************
// マネージャクラス
//********************
class CResult :public CScene
{
public:
	CResult();	// コンストラクタ
	~CResult();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);				// 初期化
	void Uninit(void);							// 終了
	void Update(void);							// 更新
	void Draw(void);							// 描画
	void SetPos(D3DXVECTOR3 pos) {};			// 位置
	void SetRot(D3DXVECTOR3 rot) {};			// 向き
	D3DXVECTOR3 GetPos(void) { return NONE; }	// 位置情報
private:
};
#endif