//***************************************
// 
// ポーズマネージャー処理 [pauseManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _PAUSEMANAGER_H_ // このマクロ定義がされていなかったら
#define _PAUSEMANAGER_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

class CPause;

//**************************
// ポーズマネージャークラス
//**************************
class CPauseManager
{
public:
	CPauseManager();	// コンストラクタ
	~CPauseManager();	// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:
	static CPause* m_pBackGame;	// ゲームに戻る
	static CPause* m_pStartGame;// ゲームのスタートに戻る
	static CPause* m_pBackTitle;// タイトルに戻る
	static CPause* m_pReverse;	// 操作反転
};
#endif