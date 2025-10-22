//=============================================================================
//
// レール中のエフェクト処理 [effect.h]
// Author Sasaki Soichiro
//
//=============================================================================
#ifndef _RAILEFFECT_H_//このマクロ定義がされていなかったら
#define _RAILEFFECT_H_//2重インクルード防止のマクロ定義
#include "main.h"
#include "object3D.h"

//************************
// レールエフェクトクラス
//************************
class CRailEffect :public CObject3D
{
public:
	CRailEffect(int nPriority = 4);	// コンストラクタ
	~CRailEffect();					// デストラクタ

	static CRailEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 size);// インスタンス生成

	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetCol(D3DXCOLOR col);		// 色の設定
	void SetSize(D3DXVECTOR2 size);	// 大きさの設定
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR2 GetSize(void);		// 大きさ情報の取得
private:
	int  m_nIdxTexture;			// 使うテクスチャの番号
	D3DXVECTOR3 m_move;			// 移動量
	int m_nPatternAnim;			// パターンカウント
	int m_nCntAnim;				// アニメーションカウント
	int m_nLife;				// ライフ
	bool m_bLife;				// 残っているか
};
#endif