//**********************************************
// 
// 車マネージャー処理 [carManager.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _CARMANAGER_H_ // このマクロ定義がされていなかったら
#define _CARMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//***********
// 前方宣言
//***********
class CCarBody;


//****************************
// 車マネージャークラス
//****************************
class CCar:CObject
{
public:
	CCar();				// コンストラクタ
	~CCar();			// デストラクタ

	static CCar* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3  pos);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	CCarBody* m_pCarBody;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
};
#endif