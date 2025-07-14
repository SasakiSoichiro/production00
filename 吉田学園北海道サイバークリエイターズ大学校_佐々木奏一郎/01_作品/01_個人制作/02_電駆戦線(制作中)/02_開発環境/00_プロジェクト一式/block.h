//**************************************
//
// ブロック処理 [block.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _BLOCK_H_ // このマクロ定義がされていなかったら
#define _BLOCK_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"
#include "objectX.h"

//********************
// プレイヤークラス
//********************
class CBlock :public CObjectX
{
public:
	typedef enum
	{
		STATE_NONE=0,
		STATE_DRAG,
		STATE_MAX
	}STATE;
	CBlock(int nPriority = 4);	// コンストラクタ
	~CBlock();					// デストラクタ
	static CBlock* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報の取得
	D3DXVECTOR3 GetRot(void);
	bool CollisionCursor(void);
	void Drag(void);
private:
	int m_nIdxXFile;
	static int m_nNumAll;
	int m_nIdx;
	STATE m_State;
};
#endif