//**********************************************
// 
// ���b�V���̕ҏW���� [edit.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _EDITMESH_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _EDITMESH_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include <vector>
#include "object.h"

class CModel;

//****************************
// �G�f�B�b�g���b�V���N���X
//****************************
class CEditMesh:public CObject
{
public:
	CEditMesh();	// �R���X�g���N�^
	~CEditMesh();	// �f�X�g���N�^
	static CEditMesh* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���̎擾
private:
	D3DXVECTOR3 m_pos;
	float m_caldera;
	static CModel* m_pModel;
};
#endif