//=============================================================================
//
// レール処理 [rail.h]
// Author:SasakiSoichiro
//
//=============================================================================
#ifndef _RAIL_H_//このマクロ定義がされていなかったら
#define _RAIL_H_//2重インクルード防止のマクロ定義

//******************
// インクルード
//******************
#include "main.h"
#include "block.h"

//******************
// マクロ定義
//******************
#define BLOCK_TEXTURE (128) //ブロックのテクスチャの最大数
#define CONTROLL (4)
#define RAILBLOCK_NUM (CONTROLL+1)
#define MAX_POINT (32)

class CRail:public CObject
{
public:
	CRail();
	~CRail();
	static CRail* Create(D3DXVECTOR3 point0, D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 Curve(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, float t);
	void AddPoint(D3DXVECTOR3 pos);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool Collision(D3DXVECTOR3 pos);
	void Save(void);
	void Load(void);

private:
	CBlock* m_pBlock[MAX_POINT];
	CBlock* m_pPrev;
	int m_nNumPoint;
	float m_fTime;
	float m_fTension;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nCurrentIdx;
	int m_nPlayerCurrentIdx;
	float m_fPlayerCurrentT;
};

#endif