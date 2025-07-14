//================================================
//
//		�^�C�g��	title3D.cpp
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

// �^�C�g���̏�����
void InitTitle3D(void)
{
	InitCamera();
	InitTitle();
	InitMeshfield();
	InitLight();
	InitNoise();
}

// �^�C�g���̏I������
void UninitTitle3D()
{
	UninitCamera();
	UninitTitle();
	UninitMeshfield();
	UninitLight();
	UninitNoise();
}

// �^�C�g���̍X�V����
void UpdateTitle3D()
{
	UpdateCamera();
	UpdateTitle();
	UpdateMeshfield();
	UpdateLight();
	UpdateNoise();
}

// �^�C�g���̕`�揈��
void DrawTitle3D()
{
	SetCamera(0);
	DrawMeshfield();
	DrawNoise();
	DrawTitle();
}
