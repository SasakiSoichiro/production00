//*****************************************
//
// 散るパーティクル処理 [sparkParticle.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _SPARKPARTICLE_H_ // このマクロ定義がされていなかったら
#define _SPARKPARTICLE_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//**************************
// 散るパーティクルクラス
//**************************
class CSparkParticle :public CObject
{
public:
	CSparkParticle(int nPriority = 3);	// コンストラクタ
	~CSparkParticle();					// デストラクタ
	static CSparkParticle* Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新		
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定	
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	void SetCol(D3DXCOLOR col);		// 色の設定
	void SetRadius(int nRadius) { m_nRad = nRadius; }	// 半径の設定
	void SetAngle(int nAngle) { m_nAngle = nAngle; }	// 角度の設定
	void SetAmount(int nAmount) { m_nAmount = nAmount; }// 量の設定
	void SetTime(int nTime) { m_nTime = nTime; }		// 時間の設定
	void SetSize(D3DXVECTOR2 size) { m_size = size; }	// 大きさの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// 位置情報の取得
	D3DXVECTOR2 GetSize(void) { return m_size; }		// 大きさ情報の設定
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR2 m_size;	// 大きさ
	D3DXCOLOR m_col;	// 色
	float m_fLength;	// 移動距離
	int m_nRad;			// 半径
	int m_nAngle;		// 向き
	int m_nLife;		// 寿命
	int m_nAmount;		// 量
	int m_nTime;		// 発生時間
};
#endif