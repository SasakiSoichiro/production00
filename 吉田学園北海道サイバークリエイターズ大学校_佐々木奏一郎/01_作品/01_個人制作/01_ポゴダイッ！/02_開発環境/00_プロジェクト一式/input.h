//=============================================================================
//
//	�C���v�b�g���� [input.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _INPUT_H_//���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_//�Q�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
//�L�[�̎��
typedef enum
{
	JOYKEY_UP=0,		//�\���L�[(��)
	JOYKEY_DOWN,		//�\���L�[(��)
	JOYKEY_LEFT,		//�\���L�[(��)
	JOYKEY_RIGHT,		//�\���L�[(�E)
	JOYKEY_START,		//�X�^�[�g�{�^��
	JOYKEY_BACK,		//�o�b�N�{�^��
	JOYKEY_LEFTTHUMB,	//���X�e�B�b�N�{�^������
	JOYKEY_RIGHTTHUMB,	//�E�X�e�B�b�N�{�^������
	JOYKEY_LEFTS,		//LB�{�^��
	JOYKEY_RIGHTS,		//RB�{�^��
	JOYKEY_UNNOWN,		//�g���Ȃ�
	JOYKEY_NASHI,		//�g���Ȃ�
	JOYKEY_A,			//A�{�^��
	JOYKEY_B,			//B�{�^��
	JOYKEY_X,			//X�{�^��
	JOYKEY_Y,			//Y�{�^��
	JOYKEY_N,			//�Ȃɂ���
	JOYKEY_W,			//�Ȃɂ���
	JOYKEY_MAX
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT  InitKeyboard(HINSTANCE hInstance,HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);
HRESULT  InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
XINPUT_STATE* GetJoypad(void);
#endif