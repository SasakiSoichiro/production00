//************************************
//
// ���U���g���� [result.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _RESULT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"

//********************
// �}�l�[�W���N���X
//********************
class CResult :public CScene
{
public:
	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);				// ������
	void Uninit(void);							// �I��
	void Update(void);							// �X�V
	void Draw(void);							// �`��
	void SetPos(D3DXVECTOR3 pos) {};			// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};			// ����
	D3DXVECTOR3 GetPos(void) { return NONE; }	// �ʒu���
private:
};
#endif