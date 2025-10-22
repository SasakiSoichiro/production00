//*************************************************
// 
// 敵の体力マネージャー処理 [enemyLifeManager.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _ENEMYLIFEMANAGER_H_ // このマクロ定義がされていなかったら
#define _ENEMYLIFEMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

class CEnemyLifeUI;

//****************************
// 敵の体力マネージャークラス
//****************************
class CEnemyLifeManager :public CObject
{
public:
	CEnemyLifeManager(int nPriority = 1);	// コンストラクタ
	~CEnemyLifeManager();					// デストラクタ
	static CEnemyLifeManager* Create(D3DXVECTOR3 pos,int nLife);
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向き設定
	void SetLife(int nLife);	// 寿命の設定	
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置情報取得
	int GetLife(void) { return m_nLife; }			// 寿命情報の取得
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	int m_nOffsetLife;
	CEnemyLifeUI* m_pLifeUI[5];
	static constexpr float size = 7.0f;
};
#endif