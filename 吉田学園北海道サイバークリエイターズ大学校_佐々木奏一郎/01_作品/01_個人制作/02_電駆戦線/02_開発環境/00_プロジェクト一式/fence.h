//**************************************
//
// 電気柵処理 [fence.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _FENCE_H_ // このマクロ定義がされていなかったら
#define _FENCE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// フェンスクラス
//********************
class CFence :public CObjectX
{
public:
	CFence(int nPriority = 4);	// コンストラクタ
	~CFence();					// デストラクタ
	static CFence* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
	bool Collision(D3DXVECTOR3 playerPos, D3DXVECTOR3 postPos0, D3DXVECTOR3 postPos1);
	void Shake(void);				// 揺らす
private:
	int m_nIdxXFile[3];	// 使うモデルの番号
	int m_nBreak;		// クールダウン時間
	int m_nBreakAttack;	// クールダウン時間
	int m_nLife;		// ライフ
};
#endif