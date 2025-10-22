//**********************************************
// 
// メッシュの編集処理 [edit.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _EDITMESH_H_ // このマクロ定義がされていなかったら
#define _EDITMESH_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include <vector>
#include "object.h"

class CModel;

//****************************
// エディットメッシュクラス
//****************************
class CEditMesh:public CObject
{
public:
	CEditMesh();	// コンストラクタ
	~CEditMesh();	// デストラクタ
	static CEditMesh* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// 位置
	void SetRot(D3DXVECTOR3 rot) {};	// 向き
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// 位置情報の取得
private:
	D3DXVECTOR3 m_pos;
	float m_caldera;
	static CModel* m_pModel;
};
#endif