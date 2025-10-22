//**************************************
//
// ボルト処理 [bolt.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _BOLT_H_ // このマクロ定義がされていなかったら
#define _BOLT_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//********************
// ボルトクラス
//********************
class CBolt :public CObjectX
{
public:
	CBolt(int nPriority = 4);	// コンストラクタ
	~CBolt();					// デストラクタ
	static CBolt* Create(D3DXVECTOR3 pos);// インスタンス生成
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
	int m_nBreak;		// クールダウン時間
	int m_nLife;		// 寿命
	float m_fAngle;		// 向き
	float m_fAngleSum;	// 回転した角度の合計
	static constexpr int maxBreakTime = 60;		// 休憩の時間
	static constexpr int maxLife = 30;			// 寿命の時間
	static constexpr float maxRange = 100.0f;	// 判定する距離
};
#endif