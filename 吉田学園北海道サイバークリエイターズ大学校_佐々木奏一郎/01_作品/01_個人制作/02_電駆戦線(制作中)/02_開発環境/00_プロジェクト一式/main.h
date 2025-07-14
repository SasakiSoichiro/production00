//****************************************
//
// ���C������ [main.h]
// Author:Sasaki Soichiro
//
//****************************************
#ifndef _MAIN_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x800)	// �r���h���̌x���Ώ��p�}�N��
#include "dinput.h"					// ���͏����ɕK�v
#include "xaudio2.h"				// �T�E���h�����ɕK�v
#include "Xinput.h"					// �W���C�p�b�h�����ɕK�v

//********************
// ���C�u�����̃����N
//********************
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�̃R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	// �W���C�p�b�h�����ɕK�v

//********************
// �}�N����`
//********************
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME  "�d����"	// �E�B���h�E�̖��O
#define SCREEN_WIDTH (1280)		// ��ʂ̉���
#define SCREEN_HEIGHT (720)		// ��ʂ̏c��
#define FVF_VERTEX_2D  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)			// ���W�E�J���[�E�e�N�X�`��
#define FVF_VERTEX_2D_MULTI  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX2)		// ���W�E�J���[�E�e�N�X�`��
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���W�E�@���E�J���[�E�e�N�X�`��

//****************************
// ���_���[2D]�̍\���̂��`
//****************************
typedef struct
{
	D3DXVECTOR3 pos;    // ���_���W
	float rhw;          // ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;       // ���_�J���[
	D3DXVECTOR2 tex;    // �e�N�X�`�����W
}VERTEX_2D;

//***********************************************
// ���_���[2D](�}���`�e�N�X�`��)�̍\���̂��`
//***********************************************
typedef struct
{
	D3DXVECTOR3 pos;    // ���_���W
	float rhw;          // ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;       // ���_�J���[
	D3DXVECTOR2 tex;    // �e�N�X�`�����W
	D3DXVECTOR2 texM;   // �e�N�X�`�����W
}VERTEX_2D_MULTI;

//****************************
//���_���[3D]�̍\���̂��`
//****************************
typedef struct
{
	D3DXVECTOR3 pos;    // ���_���W
	D3DXVECTOR3 nor;    // �@���x�N�g��
	D3DCOLOR col;       // ���_�J���[
	D3DXVECTOR2 tex;    // �e�N�X�`�����W
}VERTEX_3D;

//********************
// �O���錾
//********************
class CRenderer;// �����_�����O�N���X
class CObject;	// �I�u�W�F�N�g�N���X

//********************
// �v���g�^�C�v�錾
//********************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif