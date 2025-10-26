//**************************************
//
// ホイール処理 [wheel.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _WHEEL_H_ // このマクロ定義がされていなかったら
#define _WHEEL_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "model.h"

//***************
// 前方宣言
//***************
class CCarBody;

//************************
// ホイールのクラス
//************************
class CWheel :public CModel
{
public:
	CWheel(int nPriority = 4);	// コンストラクタ
	~CWheel();					// デストラクタ
	static CWheel* Create(D3DXVECTOR3 pos, const char* pFileName);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetPosion(D3DXVECTOR3 pos);
	void SetOffsetY(float fOffsetY) { m_fOffset = fOffsetY; }// 高さのオフセット
	void SetCarBody(CCarBody* pCarBody) { m_pCarBody = pCarBody; }
	void SetAttachY(float fAttachY) { m_fAttachY = fAttachY; }
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);		// 向き情報の取得
	void CollisionMesh(void);		// 地面との当たり判定
	float GetDeltaHeight(void) { return m_fDeltaHeight; }
private:
	float m_fOffset;
	float m_fSuspension;					// 現在のサスペンションの長さ
	float m_fSuspensionOld;					// 前フレームのサスペンションの長さ
	float m_fDeltaHeight;					// 車体に伝わる高さの変化量
	float m_fAttachY;						// 接続部分の高さ
	CCarBody* m_pCarBody;
	static constexpr float fSusMin = -20.0f;// サスペンションの最小の長さ
	static constexpr float fSusMax = 20.0f;	// サスペンションの最大の長さ 
	static constexpr float fSusRest = -10.0f;
	static constexpr float fRadius = 25.0f;	// タイヤの半径
	static constexpr float fSpringK = 12.0f;
	static constexpr float fDanperC = 1.0f;
};

#endif