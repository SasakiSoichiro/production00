//***************************************
//
// �C���v�b�g���� [input.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _INPUT_H_//���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_//�Q�d�C���N���[�h�h�~�̃}�N����`
//***************
// �C���N���[�h
//***************
#include "main.h"

//**************
// ���̓N���X
//**************
class CInput
{
public:
	CInput();			// �R���X�g���N�^
	virtual ~CInput();	// �f�X�g���N�^(�������z�֐�)
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������(���z�֐�)
	virtual void Uninit(void);								// �I��(���z�֐�)
	virtual void Update(void) = 0;							// �X�V(�������z�֐�)
protected:
	static LPDIRECTINPUT8 m_pInput;	// ���͂̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;	// ���̓f�o�C�X�ւ̃|�C���^
};

//*******************
// �L�[�{�[�h�N���X
//*******************
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();// �R���X�g���N�^
	~CInputKeyboard();// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	bool GetPress(int nKey);// �����Ă����
	bool Trigger(int nKey);	// �������u�Ԃ̂�
	bool Release(int nKey);	// �������Ƃ�
	bool Repeat(int nKey);	// �J��Ԃ�

private:
	BYTE m_aKeyState[256];				// �L�[�{�[�h�̑O��̃v���X���
	BYTE m_aOldState[256];				// �L�[�{�[�h�̃v���X���
};

//**************
// �}�E�X�N���X
//**************
class CInputMouse :public CInput
{
public:
	typedef enum
	{
		MOUSE_L = 0, // �}�E�X��
		MOUSE_R,     // �}�E�X�E
		MOUSE_H,     // �}�E�X�z�C�[��
		MOUSE_MAX
	}MOUSE;
	CInputMouse();	// �R���X�g���N�^
	~CInputMouse();	// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	bool GetDown(MOUSE button_type);// �������Ƃ�
	bool GetUp(MOUSE button_type);	// �������Ƃ�
	D3DXVECTOR2 GetVelocity();		// �������
	D3DXVECTOR2 GetVelocityOld();	// �O�t���[���̌������
private:
	BYTE m_aState[3];
	BYTE m_aOldState[3];
	DIMOUSESTATE m_CurrentState;	// ���݂̓��͏��
	DIMOUSESTATE m_PrevState;		// �O�t���[���̓��͏��
	DIMOUSESTATE m_Oldpos;		    // �O�t���[���̓��͏��
};

//********************
// �W���C�p�b�h�N���X
//********************
class CInputJoypad :public CInput
{
public:
	typedef enum
	{
		JOYKEY_UP = 0,		//�\���L�[(��)
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
		JOYKEY_N,
		JOYKEY_W,
		JOYKEY_MAX
	}JOYKEY;
	CInputJoypad();		// �R���X�g���N�^
	~CInputJoypad();	// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	bool GetPress(JOYKEY key);
	bool GetTrigger(JOYKEY key);
private:
	XINPUT_STATE m_oldState;				//�W���C�p�b�h�̑O��̃v���X���
	XINPUT_STATE m_State;					//�W���C�p�b�h�̃v���X���
	XINPUT_STATE m_StateTrigger;			//�g���K�[
};
#endif