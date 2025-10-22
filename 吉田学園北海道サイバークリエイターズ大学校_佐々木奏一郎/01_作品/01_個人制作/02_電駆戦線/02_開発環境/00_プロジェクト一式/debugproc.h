//***************************************
//
// デバッグフォント処理 [debugproc.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _DEBUGPROC_H_ // このマクロ定義がされていなかったら
#define _DEBUGPROC_H_ // 二重インクルード防止のマクロ定義
//****************
// インクルード
//****************
#include "main.h"

//*********************
// デバッグ表示クラス
//*********************
class CDebugProc
{
public:
	CDebugProc();	// コンストラクタ
	~CDebugProc();	// デストラクタ
	void Init(void);						// 初期化
	void Uninit(void);						// 終了
	static void Print(const char*fmt,...);	// 文字列表示
	static void Draw(void);					// 描画
	static void SwitchDebug(void) { m_bDebug = !m_bDebug; }	// デバッグ表示切替
private:
	static LPD3DXFONT m_pFont;	// フォントへのポインタ
	static char m_aStr[1024];	// 文字列を格納するバッファ
	static bool m_bDebug;		// デバッグ表示切替用
};
#endif