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
#include "object.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "Xmodel.h"
#include "object3D.h"
#include "mesh.h"

class CRenderer;

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
	static CXModel* GetCXModel(void) { return m_pXModel; }
	static CObject3D* GetCObject3D(void) { return m_pObject3D; }
	static CMesh* GetCMesh(void) { return m_pMesh; }
	static CPlayer* GetCPlayer(void) { return m_pPlayer; }

private:
	static CRenderer* m_pRenderer;
	static CInputKeyboard* m_pInputKeyboard;
	static CInputMouse* m_pInputMouse;
	static CInputJoypad* m_pInputJoypad;
	static CSound* m_pSound;
	static CDebugProc* m_pDebugProc;
	static CTexture* m_pTexture;
	static CCamera* m_pCamera;
	static CLight* m_pLight;
	static CXModel* m_pXModel;
	static CObject3D* m_pObject3D;
	static CMesh* m_pMesh;
	static CPlayer* m_pPlayer;
};
#endif