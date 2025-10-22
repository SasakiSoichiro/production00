//**************************************
//
// �����_�����O���� [renderer.h]
// Author:SasakiSoichiro
//
//**************************************
#ifndef _RENDERER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RENDERER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//********************
// �����_�����O�N���X
//********************
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);	// ������
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
	void Draw(void);						// �`��
	LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�̎擾
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void) { return m_pTextureMT[0]; }

private:
	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3D�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTextureMT[2];	// �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	LPDIRECT3DSURFACE9 m_pRenderMT[2];	// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_pZBuffMT;		// �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9 m_viewportMT;			// �e�N�X�`�������_�����O�p�r���[�|�[�g
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuffMT;// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@

};
#endif