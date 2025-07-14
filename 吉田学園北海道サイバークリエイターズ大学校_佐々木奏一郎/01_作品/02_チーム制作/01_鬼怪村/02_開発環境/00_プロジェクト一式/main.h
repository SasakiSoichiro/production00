//============================================================
//
//	DirectX���		[main.h]
//
//			Athor : ryuusei hirata 
// 
//===========================================================
#ifndef _MAIN_H_							//	���̒�`������Ȃ�������
#define _MAIN_H_							//	��d�C���N���[�h�h�~�̃}�N����`

//====================
//	�C���N���[�h
//====================
#include<windows.h>
#include"d3dx9.h"							//	�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)		//	�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"							//	�L�[�{�[�h�̓��͏����ɕK�v
#include "Xinput.h"							//	�W���C�p�b�g�̓��͏���
#include "xaudio2.h"
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <strsafe.h>

//========================
//	���C�u�����̃����N
//========================
#pragma comment(lib,"d3d9.lib")				//	�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")			//	[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")			//	DirectX�̃R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")			//	�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")			//	�L�[�{�[�h�����ɕK�v
#pragma comment(lib,"xinput.lib")			//	�W���C�p�b�g�����ɕK�v
#pragma warning( disable : 4996 )
#pragma warning( default : 4996 )

//================
//	�}�N����`
//================
#define CLASS_NAME "WindowsClass"			//	�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�S����"				//	�E�B���h�E�̖��O
#define SCREEN_WIDTH (1280)					//	�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)					//	�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//	���W�A�@���A�J���[�A�e�N�X�`��

//================
//	��ʂ̎��
//================
typedef enum
{
	MODE_TITLE = 0,		//	�^�C�g�����
	MODE_TUTRIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_CLEAR,
	MODE_RANKING,
	MODE_MAX
}MODE;

//====================================
//	���_���u�QD�v�̍\���̂��`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;		//	���_���W
	float rhw;				//	���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;			//	���_�J���[
	D3DXVECTOR2 tex;		//	�e�N�X�`�����W
}VERTEX_2D;

//====================================
//	���_���u3D�v�̍\���̂��`
//====================================
typedef struct
{
	D3DXVECTOR3 pos;	//	���_���W
	D3DXVECTOR3 nor;	//	�@���x�N�g��
	D3DCOLOR col;		//	���_�J���[
	D3DXVECTOR2 tex;	//	�e�N�X�`�����W
}VERTEX_3D;

//==================
//	�v���g�^�C�v
//==================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
LPDIRECT3DDEVICE9 GetDevice(void);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);
void ToggleFullscreen(HWND hWnd);				// �E�B���h�E���t���X�N���[���ɂ�����@
void DrawFPS(void);
void DrawCameraPosR(void);
void DrawCameraPosV(void);
void DrawCameraRot(void);
void DrawDebugKey(void);
void DrawEnemyPos(void);
void DrawHoldTime(void);
void DrawNoTouchTime(void);
void DrawTotalTime(void);
void DrawDebugPlayer(void);
VOID Cleanup();
VOID Render();
#endif