//***************************************
// 
// �t�F�[�h���� [fade.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _FADE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _FADE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"

//************************
// �t�F�[�h�N���X
//************************
class CFade
{
public:
	// ���
	typedef enum
	{
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_IN,		// �t�F�[�h�C�����
		STATE_OUT,		// �t�F�[�h�A�E�g���
		STATE_MAX
	}STATE;

	CFade();	// �R���X�g���N�^
	~CFade();	// �f�X�g���N�^
	HRESULT Init(void);			// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	void Draw(void);			// �`��
	static void Set(CScene::MODE modeNext);
	STATE Get(void) { return m_state; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_col;
	static STATE m_state;
	static CScene::MODE m_modeNext;
};
#endif