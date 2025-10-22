//=============================================================================
//
//	影の処理 [shadowS.h]
// Author:Sasaki Soichiro
//
//=============================================================================
#ifndef _SHADOWS_H_// このマクロ定義がされていなかったら
#define _SHADOWS_H_// 2重インクルード防止のマクロ定義
//**************
// インクルード
//**************
#include "main.h"
#include "objectX.h"

//***************
// 影クラス
//***************
class CShadowS :public CObjectX
{
public:
	CShadowS(int nPriority = 3);// コンストラクタ
	~CShadowS();				// デストラクタ
	static CShadowS* Create(D3DXVECTOR3 pos);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);				// 初期化
	void Uninit(void);							// 終了
	void Update(void);							// 更新
	void Draw(void);							// 描画
	void SetPos(D3DXVECTOR3 pos);				// 位置の設定
private:
	int m_nIdxXFile;					// 使っているXファイルの番号
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXCOLOR m_col;					// 色
	D3DXVECTOR2 m_size;					// 大きさ
};

#endif