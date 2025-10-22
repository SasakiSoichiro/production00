//**************************************
//
// 敵の体力UI処理 [enemyLifeUI.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYLIFEUI_H_ // このマクロ定義がされていなかったら
#define _ENEMYLIFEUI_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectBillboard.h"

//************************
// 敵の体力UIクラス
//************************
class CEnemyLifeUI :public CObjectBillboard
{
public:
	CEnemyLifeUI(int nPriority = 6);	// コンストラクタ
	~CEnemyLifeUI();					// デストラクタ
	static CEnemyLifeUI* Create(D3DXVECTOR3 pos,D3DXVECTOR2 offset, int nIdx);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
	void SetLife(int nLife);		// 終了するかの判断
private:
	int m_nIdxTexture[2];		// 使うテクスチャの番号
	int m_nIdx;					// インデックス
	int m_nUseTexture;			// 現在使っているテクスチャ
};
#endif