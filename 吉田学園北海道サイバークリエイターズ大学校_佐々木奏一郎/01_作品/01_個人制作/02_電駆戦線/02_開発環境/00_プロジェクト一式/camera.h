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
	void Target(D3DXVECTOR3 pos,D3DXVECTOR3 rot);	// 映すターゲットの設定
	void BackTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot);// 後ろに進む場合の設定
	void InitTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot);// カメラの初期化
	void JumpTarget(D3DXVECTOR3 pos,float fAngle);	// 空中にいる場合の設定
	void SetVandR(void);							// 視点と注視点の設定
	void MoveMouseR(void);							// マウスで注視点を動かす
	void MoveMouseV(void);							// マウスで視点を動かす
	void Shake(void);								// カメラを揺らす
	void SetShake(int nTime);						// カメラを揺らす時間を設定する
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
	int m_nShakeTime;			// カメラが揺れている時間
	static constexpr float ofsetV = 60.0f;	// プレイヤーから視点までの距離
	static constexpr float ofsetBackV = 90.0f;	// プレイヤーから視点までの距離(後ろ向きに進んでいるとき)
	static constexpr float ofsetR = 50.0f;	// プレイヤーから視点までの距離
	static constexpr float dest = 0.08f;	// 目標に到達するまでの遅延
	static constexpr float speed = 2.0f;	// カメラ操作時のスピード
	static constexpr float sensitivity = 0.009f;	// マウス感度
	static constexpr float shakeDistance = 1.5f;	// カメラ揺れの動く距離
	static constexpr float FOV = 100.0f;			// 視野角
	static constexpr float nearScreen = 10.0f;		// 描画距離(近く)
	static constexpr float farScreen = 10000.0f;	// 描画距離(遠く)
};
#endif