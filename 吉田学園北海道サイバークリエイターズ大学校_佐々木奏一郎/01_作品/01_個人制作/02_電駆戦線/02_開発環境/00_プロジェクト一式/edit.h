//************************************
//
// エディター処理 [edit.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _EDIT_H_ // このマクロ定義がされていなかったら
#define _EDIT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "scene.h"

class CEditCamera;
class CMesh;
class CEditMesh;

//********************
// エディタークラス
//********************
class CEdit :public CScene
{
public:
	CEdit();	// コンストラクタ
	~CEdit();	// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化
	void Uninit(void);					// 終了
	void Update(void);					// 更新
	void Draw(void);					// 描画
	void SetPos(D3DXVECTOR3 pos) {};	// 位置
	void SetRot(D3DXVECTOR3 rot) {};	// 向き
	D3DXVECTOR3 GetPos(void) { return NONE; }	// 位置情報
	static CMesh* GetMesh(void) { return m_pMesh; }
private:
	static CEditCamera* m_pEditCamera;
	static CMesh* m_pMesh;
	static CEditMesh* m_pEditMesh;
};
#endif