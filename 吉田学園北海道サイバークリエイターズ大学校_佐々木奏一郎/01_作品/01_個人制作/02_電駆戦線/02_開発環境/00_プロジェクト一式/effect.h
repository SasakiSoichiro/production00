//****************************************
//
//	エフェクト処理 [effect.h]
// Author Sasaki Soichiro
//
//****************************************
#ifndef _EFFECT_H_//このマクロ定義がされていなかったら
#define _EFFECT_H_//2重インクルード防止のマクロ定義
#include "main.h"
#include "objectBillboard.h"

//********************
// エフェクトクラス
//********************
class CEffect :public CObjectBillboard
{
public:
	CEffect(int nPriority = 4);	// コンストラクタ
	~CEffect();					// デストラクタ

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetRot(D3DXVECTOR3 rot);	// 向きの設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// ムーブ値の設定
	void SetCol(D3DXCOLOR col);							// 色の設定
	void SetSize(D3DXVECTOR2 size);						// 大きさの設定
	void SetTexture(int nTexture) { m_nIdxTexture = nTexture; }	// テクスチャの設定
	void SetLife(int nLife) { m_nLife = nLife; }// 寿命の設定
	D3DXVECTOR3 GetPos(void);					// 位置情報の取得
	D3DXVECTOR3 GetMove(void) { return m_move; }// ムーブ値の取得
	D3DXVECTOR2 GetSize(void);					// 大きさ情報の取得
private:
	int  m_nIdxTexture;			// 使うテクスチャの番号
	D3DXVECTOR3 m_move;			// 移動量
	int m_nPatternAnim;			// パターンカウント
	int m_nCntAnim;				// アニメーションカウント
	int m_nLife;				// 寿命
	bool m_bLife;				// 残っているか
	static constexpr int maxLife = 60;		// 寿命の時間
	static constexpr int anim = 3;			// 更新するフレーム
	static constexpr int patternAnim = 4;	// アニメーションのパターン数
	static constexpr float texOffset = 0.25f;	// テクスチャ座標のオフセット
};
#endif