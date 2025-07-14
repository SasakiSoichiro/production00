//=============================================================================
//
//	���͏��� [input.h]
// Author : HRT ryuusei
//
//=============================================================================
#ifndef _INPUT_H_// ���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//======================
// �C���N���[�h�t�@�C��
//======================
#include "main.h"

//================
//	�L�[�̎��
//================
typedef enum
{
	JOYKEY_UP = 0,	//	�\���L�[(��)
	JOYKEY_DOWN,	//	�\���L�[(��)
	JOYKEY_LEFT,	//	�\���L�[(��)
	JOYKEY_RIGHT,	//	�\���L�[(��)
	JOYKEY_START,	//	�X�^�[�g
	JOYKEY_BACK,	//	�o�b�N
	JOYKEY_LPUSH,	//	�X�e�B�b�N��������	��
	JOYKEY_RPUSH,	//	�X�e�B�b�N��������	�E
	JOYKEY_LB,		//	L1
	JOYKEY_RB,		//	R1
	JOYKEY_LT,		//	L2
	JOYKEY_RT,		//	R2
	JOYKEY_A,		//	A�{�^��
	JOYKEY_B,		//	B�{�^��
	JOYKEY_X,		//	X�{�^��
	JOYKEY_Y,		//	Y�{�^��
	JOYKEY_MAX
}JOYKEY;

//======================
// �}�E�X�̎��
//======================
typedef enum
{
	MOUSE_L = 0, // �}�E�X��
	MOUSE_R,     // �}�E�X�E
	MOUSE_H,     // �}�E�X�z�C�[��
	MOUSE_MAX
}MouseButton;

//======================
// �v���C���[�̎��
//======================
typedef enum
{
	PLAYER_1 = 0, // �v���C���[1
	PLAYER_2,     // �v���C���[2
	PLAYER_MAX
}PLAYER;

//======================
// �p�b�h�̎��
//======================
typedef enum
{
	DX_INPUT_KEY_PAD1 = 0, // �L�[���͂ƃp�b�h�P
	DX_INPUT_PAD1,         // �p�b�h�P
	DX_INPUT_PAD2,         // �p�b�h�Q
	DX_INPUT_KEY,          // �L�[����
	DX_INPUT_MAX
}InputType;

//=========================
//�U����Ԃ��Ǘ�����\����
//=========================
typedef struct
{
	int contorollerID;
	WORD leftMoter;
	WORD rightMoter;
	DWORD startTime;
	DWORD duration;
}VibrationState;

//==================
// �v���g�^�C�v�錾
//==================
// �L�[�{�[�h
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeybordTrigger(int nKey);
bool KeybordRelease(int nKey);
bool KeybordRepeat(int nKey);

// �W���C�p�b�h
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
bool JoyPadRelease(JOYKEY key);
bool GetJoyStick(int player);
XINPUT_STATE* GetJoyStickAngle(void);
XINPUT_STATE* GetState(void);
int GetJoypadInputState(int InputType);
void VibrateController(int ContorollerID, WORD leftMoter, WORD rightMoter);
void UpdateVibration(VibrationState* vibrationState);
void StartVibration(VibrationState* vibrationState, int VibrationTime, int leftMoter, int rightMoter);

// �}�E�X
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd);
void UninitMausu(void);
void UpdateMausu(void);
bool OnMouseDown(MouseButton button_type);
bool OnMouseUp(MouseButton button_type);
D3DXVECTOR2 GetMouseVelocity();
D3DXVECTOR2 GetMouseVelocityOld();

#endif