//**************************************
//
// 車処理 [car.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _CAR_H_ // このマクロ定義がされていなかったら
#define _CAR_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "model.h"

class CWheel;

//********************
// 車体クラス
//********************
class CCarBody :public CModel
{
public:
	typedef enum
	{
		TYPE_BODY=0,
		TYPE_FLONTLEFT,
		TYPE_FLONTRIHGT,
		TYPE_REARLEFT,
		TYPE_REARRIGHT,
		TYPE_MAX
	}TYPE;
	CCarBody(int nPriority = 4);	// コンストラクタ
	~CCarBody();					// デストラクタ
	static CCarBody* Create(D3DXVECTOR3 pos, const char* pFileName);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetWheel(void);			// タイヤの位置設定
	void WheelAttachY(void);		// 接続部分の高さ
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	void SetMove(D3DXVECTOR3 move);	// 速度
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }	// 前フレームの位置情報取得
	D3DXVECTOR3 GetMove(void) { return m_move; }		// 動き情報取得
	D3DXVECTOR3 GetVecU(void) { return m_vecU; }		// 上ベクトル情報取得
private:
	D3DXVECTOR3 m_oldPos;	// 前フレームの位置
	D3DXVECTOR3 m_move;		// 動く
	D3DXVECTOR3 m_rotDest;	// 目標の向き
	D3DXVECTOR3 m_vecF;		// 前ベクトル
	D3DXVECTOR3 m_vecR;		// 右ベクトル
	D3DXVECTOR3 m_vecU;		// 上ベクトル
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	CWheel* m_pWheel[4];	// ホイール
	float m_fAngle;			// ハンドルの角度
	float m_fSpeed;
	int m_nIdxXFile;
	static constexpr float fWheelOffsetY = 50.0f;
	static constexpr float fWheelOffsetLeft = -30.0f;
	static constexpr float fWheelOffsetRight = 30.0f;
	static constexpr float fWheelOffsetFlont = 35.0f;
	static constexpr float fWheelOffsetRear = -35.0f;
	static constexpr float fDeltaAngle = 0.01f;
	static constexpr float fMaxSpeed = 4.0f;
	static constexpr float fMaxAngle = 1.0f;
};

#endif