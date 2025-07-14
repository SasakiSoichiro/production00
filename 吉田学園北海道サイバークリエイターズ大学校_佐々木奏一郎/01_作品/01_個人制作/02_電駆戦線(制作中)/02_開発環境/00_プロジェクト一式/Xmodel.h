//*****************************************
// 
// Xファイル処理 [Xmodel.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _XMODEL_H_	// このマクロ定義がされていなかったら
#define _XMODEL_H_	// 二重インクルード防止のマクロ定義
//***************
// インクルード
//***************
#include "main.h"
class CXModel
{
public:
	//*******************
	// Xファイルの構造体
	//*******************
	typedef struct
	{
		LPD3DXMESH pMesh;
		LPD3DXBUFFER pBuffMat;
		DWORD dwNumMat;
	}XMODEL;
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_MAX
	}TYPE;
	CXModel();	// コンストラクタ
	~CXModel();	// デストラクタ
	HRESULT Load(void);	// ロード
	void Unload(void);	// アンロード
	int Register(const char* pFilename);	// Xファイルの登録
	XMODEL GetAddres(int nIdx);				// Xファイルのインデックス
private:
	XMODEL m_apXModel[256];
	static int m_nNumAll;
	const char* XFILE[256] =
	{
		"data\\MODEL\\aa.x",
	};
};



#endif