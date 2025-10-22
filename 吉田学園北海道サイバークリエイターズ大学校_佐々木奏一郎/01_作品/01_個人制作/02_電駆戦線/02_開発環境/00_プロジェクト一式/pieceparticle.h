//*****************************************
//
// 破片パーティクル処理 [pieceparticle.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _PIECEPARTICLE_H_ // このマクロ定義がされていなかったら
#define _PIECEPARTICLE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//************************
// 破片パーティクルクラス
//************************
class CPieceParticle :public CObject
{
public:
	CPieceParticle(int nPriority = 3);	// コンストラクタ
	~CPieceParticle();				// デストラクタ
	static CPieceParticle* Create(D3DXVECTOR3 pos,int nAngle);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新		
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定	
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// 位置情報の取得
private:
	D3DXVECTOR3 m_pos;	// 位置
	int m_nAngle;		// 向き
};
#endif