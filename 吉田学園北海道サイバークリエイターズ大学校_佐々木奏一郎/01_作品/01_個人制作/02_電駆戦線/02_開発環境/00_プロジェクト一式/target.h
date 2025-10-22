//***************************************
// 
// ���U���gUI���� [resultUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _TARGET_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TARGET_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// ���U���gUI�N���X
//************************
class CTarget :public CObject2D
{
public:
	CTarget(int nPriority = 5);	// �R���X�g���N�^
	~CTarget();					// �f�X�g���N�^
	static CTarget* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture[3];			// �e�N�X�`���̃C���f�b�N�X
	int m_nCnt;
	int m_nType;
	static constexpr int cool = 180;
};
#endif