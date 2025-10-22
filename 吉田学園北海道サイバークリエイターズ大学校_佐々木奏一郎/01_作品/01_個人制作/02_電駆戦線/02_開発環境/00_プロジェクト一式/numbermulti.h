//********************************
// 
// �}���`�e�N�X�`���Ńi���o�[�N���X
// Author Sasaki Soichiro
// 
//********************************
#ifndef _NUMBERMULTI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _NUMBERMULTI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//****************
// �C���N���[�h
//****************
#include "main.h"
#include "object2DMulti.h"

//******************
// �i���o�[�N���X
//******************
class CNumberMulti:public CObject2DMulti
{
public:
	CNumberMulti(int nPriority = 5);	// �R���X�g���N�^
	~CNumberMulti();					// �f�X�g���N�^
	static CNumberMulti* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) ;	// �ʒu
	void SetRot(D3DXVECTOR3 rot) ;	// ����
	void SetCol(D3DXCOLOR col);		// �F
	D3DXVECTOR3 GetPos(void);		// �ʒu���
	void SetNumber(int nNum);		// �i���o�[�̐ݒ�
	void SetGauge(int nGauge);		// �Q�[�W�̐ݒ�
	void SetSize(D3DXVECTOR2 size);	// �傫���̐ݒ�
private:
	int m_nIdxTexture[2];	// �g���e�N�X�`���̔ԍ�
	int m_nNum;				// ��
};
#endif