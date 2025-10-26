//**************************************
//
// メッシュ編集処理 [meshEdit.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _MESHEDIT_H_ // このマクロ定義がされていなかったら
#define _MESHEDIT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// メッシュ編集クラス
//********************
class CMeshEdit :public CObjectX
{
public:
	CMeshEdit(int nPriority = 4);	// コンストラクタ
	~CMeshEdit();					// デストラクタ
	static CMeshEdit* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
private:
	int m_nIdxXFile;	// 使うモデルの番号
	static constexpr float fSpeed = 1.5f;
};
#endif