//***************************************
// 
// 編集中のカメラ処理 [editcamera.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _EDITCAMERA_H_ // このマクロ定義がされていなかったら
#define _EDITCAMERA_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"

//************************
// エディットカメラクラス
//************************
class CEditCamera
{
public:
	typedef enum
	{
		STATE_NONE=0,
		STATE_R,
		STATE_V,
		STATE_MAX
	}STATE;
	CEditCamera();	// コンストラクタ
	~CEditCamera();	// デストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
private:
	STATE m_state;
};
#endif