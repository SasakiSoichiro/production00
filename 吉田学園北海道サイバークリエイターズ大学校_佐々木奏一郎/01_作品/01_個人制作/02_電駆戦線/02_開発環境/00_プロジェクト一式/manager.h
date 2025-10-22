//************************************
//
// �}�l�[�W������ [manager.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _MANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"

class CRenderer;		
class CInputKeyboard;	
class CInputMouse;		
class CInputJoypad;		
class CSound;			
class CDebugProc;		
class CTexture;			
class CCamera;			
class CLight;			
class CXModel;			
class CScene;			
class CBlurManager;		
class CPauseManager;
class CFade;

//********************
// �}�l�[�W���N���X
//********************
class CManager
{
public:
	CManager();		// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);	// ������
	void Uninit(void);											// �I��
	void Update(void);											// �X�V
	void Draw(void);											// �`��
	static CRenderer* GetCRenderer(void) { return m_pRenderer; }				// �����_���[���擾
	static CInputKeyboard* GetCInputKeyboard(void) { return m_pInputKeyboard; }	// �L�[�{�[�h���擾
	static CInputMouse* GetCInputMouse(void) { return m_pInputMouse; }			// �}�E�X���擾
	static CInputJoypad* GetCInputJoypad(void) { return m_pInputJoypad; }		// �W���C�p�b�h���擾
	static CSound* GetCSound(void) { return m_pSound; }							// �T�E���h���擾
	static CDebugProc* GetCDebugProc(void) { return m_pDebugProc; }				// �f�o�b�O�\�����擾
	static CTexture* GetCTexture(void) { return m_pTexture; }					// �e�N�X�`�����擾
	static CCamera* GetCCamera(void) { return m_pCamera; }						// �J�������擾
	static CLight* GetCLight(void) { return m_pLight; }							// ���C�g���擾
	static CXModel* GetCXModel(void) { return m_pXModel; }						// ���f�����擾
	static CBlurManager* GetCBlurManager(void) { return m_pBlur; }				// �u���[���擾
	static CPauseManager* GetCPauseManager(void) { return m_pPauseManager; }	// �|�[�Y�}�l�[�W���[���擾
	static CFade* GetFade(void) { return m_pFade; }								// �t�F�[�h���擾
	static void SetMode(CScene::MODE mode);										// �V�[���̐ݒ�
	static CScene::MODE GetMode(void);											// ���[�h���擾
private:
	static CRenderer* m_pRenderer;				// �����_���[�ւ̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;	// �L�[�{�[�h�ւ̃|�C���^
	static CInputMouse* m_pInputMouse;			// �}�E�X�ւ̃|�C���^
	static CInputJoypad* m_pInputJoypad;		// �W���C�p�b�h�ւ̃|�C���^
	static CSound* m_pSound;					// �T�E���h�ւ̃|�C���^
	static CDebugProc* m_pDebugProc;			// �f�o�b�O�\���ւ̃|�C���^
	static CTexture* m_pTexture;				// �e�N�X�`���ւ̃|�C���^
	static CCamera* m_pCamera;					// �J�����ւ̃|�C���^
	static CLight* m_pLight;					// ���C�g�ւ̃|�C���^
	static CXModel* m_pXModel;					// ���f���ւ̃|�C���^
	static CScene* m_pScene;					// �V�[���ւ̃|�C���^
	static CBlurManager* m_pBlur;				// �u���[�ւ̃|�C���^
	static CPauseManager* m_pPauseManager;		// �|�[�Y�}�l�[�W���[�ւ̃|�C���^
	static CFade* m_pFade;						// �t�F�[�h�ւ̃|�C���^
};
#endif