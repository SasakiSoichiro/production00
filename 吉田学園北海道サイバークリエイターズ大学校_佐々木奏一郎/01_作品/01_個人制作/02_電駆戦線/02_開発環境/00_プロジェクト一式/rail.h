//**********************************
//
// レール処理 [rail.h]
// Author:SasakiSoichiro
//
//**********************************
#ifndef _RAIL_H_// このマクロ定義がされていなかったら
#define _RAIL_H_// 2重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "object.h"

//******************
// マクロ定義
//******************
#define BLOCK_TEXTURE (128)			//ブロックのテクスチャの最大数
#define CONTROLL (4)				// 最初の制御点の個数
#define RAILBLOCK_NUM (CONTROLL+1)	// ブロックの総数
#define MAX_POINT (32)				// 点の最大数

class CRailBlock;
class CRailMesh;

//*********************
// レールクラス
//*********************
class CRail:public CObject
{
public:
	typedef enum
	{
		TYPE_CHARGE=0,
		TYPE_DISCHARGE,
		TYPE_MAX
	}TYPE;
	CRail();	// コンストラクタ
	~CRail();	// デストラクタ
	static CRail* Create(D3DXVECTOR3 point0, D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3, int nType);// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	D3DXVECTOR3 Curve(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, float t);// カーブ
	void AddPoint(D3DXVECTOR3 pos);					// 制御点追加
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// 位置の設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// 向きの設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// 位置情報取得
	bool Collision(D3DXVECTOR3 pos);				// あたり判定
	void SetMesh(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);// メッシュの設定
	float GetAngle(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);// 点から点の角度
	static void Change(void);
	static void InitAll(void) { m_nCntAll = 0; }
	void Save(void);	// 保存
	void Load(void);	// 読み込み

private:
	CRailBlock* m_pBlock[MAX_POINT];// 制御点
	CRailBlock* m_pPrev;			// どこを通っているかの確認
	int m_nNumPoint;				// 制御点の数
	float m_fTime;					// 時間
	float m_fTension;				// テンション
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_rot;				// 向き
	int m_nCurrentIdx;				// 現在の位置
	static int m_nPlayerCurrentIdx;		// 現在のプレイヤーの位置
	static float m_fPlayerCurrentT;		// 現在のプレイヤーの時間
	int m_nCnt;						// レールを動かすカウント
	int m_nIdx;						// レールのインデックス
	int m_nType;					// 種類
	static int m_nCntAll;			// レールが存在している数
	static int m_nUse;				// 現在触れているレールのインデックス
	static int m_nOldUse;			// 前フレームで触れたレールのインデックス
	CRailMesh* m_pMesh;				// レールメッシュへのポインタ
	int m_nEffectCnt;				// エフェクトの出るカウント
	static constexpr int effectCool = 3;// エフェクトが出るクールタイム
};

#endif