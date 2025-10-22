//**************************************
//
// アイテム処理 [item.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ITEM_H_ // このマクロ定義がされていなかったら
#define _ITEM_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

class CItemSkill;

//********************
// アイテムクラス
//********************
class CItem :public CObjectX
{
public:
	typedef enum
	{
		ITEM_ADJUST=0,// 充電量を調節する
		ITEM_MAX
	}ITEM;
	CItem(int nPriority = 4);	// コンストラクタ
	~CItem();					// デストラクタ
	static CItem* Create(D3DXVECTOR3 pos,int nType);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
	CItemSkill* Collision(D3DXVECTOR3 pos);// あたり判定
private:
	int m_nIdxXFile;
	static constexpr float size = 30.0f;
};
#endif