//**************************************
//
// ���U���g�X�R�A���� [resultScore.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RESULTSCORE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RESULTSCORE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

class CNumber;

//*****************
// �}�N����`
//*****************
#define MAX_DIGIT (8)// �ő包��

//**********************
// ���U���g�X�R�A�N���X
//**********************
class CResultScore :public CObject
{
public:
	CResultScore(int nPriority = 5);// �R���X�g���N�^
	~CResultScore();				// �f�X�g���N�^
	static CResultScore* Create(D3DXVECTOR3 pos);	// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);					// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	void Draw(void);								// �`��
	void SetPos(D3DXVECTOR3 pos);					// �ʒu
	void SetRot(D3DXVECTOR3 rot);					// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu���̎擾
	D3DXVECTOR2 GetSize(void) { return m_size; }	// �傫�����̎擾
	int Digit(int nScore);							// �������̎擾

private:
	int  m_nIdxTexture;						// �e�N�X�`���̃C���f�b�N�X
	static CNumber* m_apNumber[MAX_DIGIT];	// �i���o�[�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR2 m_size;						// �傫��
	int m_nScore;							// �X�R�A
};
#endif