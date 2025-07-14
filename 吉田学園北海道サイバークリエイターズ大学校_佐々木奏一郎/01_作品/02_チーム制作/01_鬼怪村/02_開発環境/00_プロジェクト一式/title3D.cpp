//================================================
//
//		タイトル	title3D.cpp
//
//			ryuusei.hirata
//================================================
#include "title3D.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "title.h"
#include "meshfield.h"
#include "light.h"
#include "model.h"
#include "noise.h"

// タイトルの初期化
void InitTitle3D(void)
{
	InitCamera();
	InitTitle();
	InitMeshfield();
	InitLight();
	InitNoise();
}

// タイトルの終了処理
void UninitTitle3D()
{
	UninitCamera();
	UninitTitle();
	UninitMeshfield();
	UninitLight();
	UninitNoise();
}

// タイトルの更新処理
void UpdateTitle3D()
{
	UpdateCamera();
	UpdateTitle();
	UpdateMeshfield();
	UpdateLight();
	UpdateNoise();
}

// タイトルの描画処理
void DrawTitle3D()
{
	SetCamera(0);
	DrawMeshfield();
	DrawNoise();
	DrawTitle();
}
