//**************************************
//
// レールのブロック処理 [railblock.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RAILBLOCK_H_ // このマクロ定義がされていなかったら
#define _RAILBLOCK_H_ // 二重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "objectX.h"

//************************
// レールのブロッククラス
//************************
class CRailBlock :public CObjectX
{
public:
	// 状態
	typedef enum
	{
		STATE_NONE=0,// 何もなし
		STATE_DRAG,// マウスでつかんでる状態
		STATE_MAX
	}STATE;
	CRailBlock(int nPriority = 4);	// コンストラクタ
	~CRailBlock();					// デストラクタ
	static CRailBlock* Create(D3DXVECTOR3 pos);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetPos(D3DXVECTOR3 pos);	// 位置
	void SetRot(D3DXVECTOR3 rot);	// 向き
	D3DXVECTOR3 GetPos(void);		// 位置情報取得
	D3DXVECTOR3 GetRot(void);		// 向き情報取得
	bool CollisionCursor(void);		// マウスとの当たり判定
	void Drag(void);				// 掴んで移動
private:
	int m_nIdxXFile;		// 使っているXファイルの番号
	static int m_nNumAll;	// 現在の数
	int m_nIdx;				// 番号
	STATE m_State;			// 状態
};
#endif