//***************************************
//
// カメラ処理 [camera.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _CAMERA_H_//このマクロ定義がされていなかったら
#define _CAMERA_H_//２重インクルード防止のマクロ定義
//**************
// インクルード
//**************
#include "main.h"
#include "player.h"

//**************
// カメラクラス
//**************
class CCamera
{
public:
	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ
	void Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void SetCamera(void);	// カメラの設定
	void Target(void);
	void Fixed(D3DXVECTOR3 pos);
	static void SetPlayer(CPlayer* pPlayer);

private:
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	D3DXVECTOR3 m_rot;			// 向き
	float m_fDistance;			// 視点から注視点の距離
	D3DXVECTOR3 m_posVDest;		// 目的の視点
	D3DXVECTOR3 m_posRDest;		// 目的の注視点
	static CPlayer* m_pPlayer;	// プレイヤーのポインタ
};
#endif