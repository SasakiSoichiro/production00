//********************************
// 
// マルチテクスチャ版ナンバークラス
// Author Sasaki Soichiro
// 
//********************************
#ifndef _NUMBERMULTI_H_ // このマクロ定義がされていなかったら
#define _NUMBERMULTI_H_ // 二重インクルード防止のマクロ定義

//****************
// インクルード
//****************
#include "main.h"
#include "object2DMulti.h"

//******************
// ナンバークラス
//******************
class CNumberMulti:public CObject2DMulti
{
public:
	CNumberMulti(int nPriority = 5);	// コンストラクタ
	~CNumberMulti();					// デストラクタ
	static CNumberMulti* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos) ;	// 位置
	void SetRot(D3DXVECTOR3 rot) ;	// 向き
	void SetCol(D3DXCOLOR col);		// 色
	D3DXVECTOR3 GetPos(void);		// 位置情報
	void SetNumber(int nNum);		// ナンバーの設定
	void SetGauge(int nGauge);		// ゲージの設定
	void SetSize(D3DXVECTOR2 size);	// 大きさの設定
private:
	int m_nIdxTexture[2];	// 使うテクスチャの番号
	int m_nNum;				// 数
};
#endif