//********************************
// 
// ナンバークラス
// Author Sasaki Soichiro
// 
//********************************
#ifndef _NUMBER_H_ // このマクロ定義がされていなかったら
#define _NUMBER_H_ // 二重インクルード防止のマクロ定義

//****************
// インクルード
//****************
#include "main.h"

//******************
// ナンバークラス
//******************
class CNumber
{
public:
	CNumber();// コンストラクタ
	~CNumber();// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Draw(void);	// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置の設定
	void SetNumber(int nNum);		// ナンバーの設定
	void SetSize(D3DXVECTOR2 size);	// 大きさの設定
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR2 m_size;	// 大きさ
	int nNum;			// 数情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
};

//****************
// 記号クラス
//****************
class CSymbol
{
public:
	CSymbol();	// コンストラクタ
	~CSymbol();	// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Draw(void);	// 描画
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定
	void SetSize(D3DXVECTOR2 size);					// 大きさの設定
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャの設定
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR2 m_size;	// 大きさ
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点情報のポインタ
};
#endif