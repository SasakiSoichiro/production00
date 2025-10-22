//**************************************
//
// ボルト攻撃処理 [attackbolt.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ATTACKBOLT_H_ // このマクロ定義がされていなかったら
#define _ATTACKBOLT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//************************
// ボルト攻撃のクラス
//************************
class CAttackBolt :public CObjectX
{
public:
	CAttackBolt(int nPriority = 4);	// コンストラクタ
	~CAttackBolt();					// デストラクタ
	static CAttackBolt* Create(D3DXVECTOR3 pos,float fAngle);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetAngle(float fAngle) { m_fAngle = fAngle; }// 向きの設定
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
private:
	int m_nIdxXFile;	// 使うテクスチャの番号
	D3DXVECTOR3 m_move;	// 動く距離
	float m_fAngle;		// 向き
	int m_nLife;		// ライフ
	static constexpr float jump = 2.5f;
	static constexpr float speed = 1.2f;
	static constexpr float horizon = 0.08f;
	static constexpr int maxLife = 80;
	static const D3DXVECTOR3 ROT_MOVE;
};
#endif