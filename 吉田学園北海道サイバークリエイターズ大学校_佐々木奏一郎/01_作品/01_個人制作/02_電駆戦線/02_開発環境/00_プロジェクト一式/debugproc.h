//***************************************
//
// �f�o�b�O�t�H���g���� [debugproc.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _DEBUGPROC_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _DEBUGPROC_H_ // ��d�C���N���[�h�h�~�̃}�N����`
//****************
// �C���N���[�h
//****************
#include "main.h"

//*********************
// �f�o�b�O�\���N���X
//*********************
class CDebugProc
{
public:
	CDebugProc();	// �R���X�g���N�^
	~CDebugProc();	// �f�X�g���N�^
	void Init(void);						// ������
	void Uninit(void);						// �I��
	static void Print(const char*fmt,...);	// ������\��
	static void Draw(void);					// �`��
	static void SwitchDebug(void) { m_bDebug = !m_bDebug; }	// �f�o�b�O�\���ؑ�
private:
	static LPD3DXFONT m_pFont;	// �t�H���g�ւ̃|�C���^
	static char m_aStr[1024];	// ��������i�[����o�b�t�@
	static bool m_bDebug;		// �f�o�b�O�\���ؑ֗p
};
#endif