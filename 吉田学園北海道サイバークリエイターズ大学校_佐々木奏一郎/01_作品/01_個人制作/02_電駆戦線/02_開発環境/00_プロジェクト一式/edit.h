//************************************
//
// �G�f�B�^�[���� [edit.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _EDIT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"

class CEditCamera;
class CMesh;
class CEditMesh;

//********************
// �G�f�B�^�[�N���X
//********************
class CEdit :public CScene
{
public:
	CEdit();	// �R���X�g���N�^
	~CEdit();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ������
	void Uninit(void);					// �I��
	void Update(void);					// �X�V
	void Draw(void);					// �`��
	void SetPos(D3DXVECTOR3 pos) {};	// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};	// ����
	D3DXVECTOR3 GetPos(void) { return NONE; }	// �ʒu���
	static CMesh* GetMesh(void) { return m_pMesh; }
private:
	static CEditCamera* m_pEditCamera;
	static CMesh* m_pMesh;
	static CEditMesh* m_pEditMesh;
};
#endif