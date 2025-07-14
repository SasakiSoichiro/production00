//**************************************
//
// �X�R�A���� [score.h]
// AuthorSasaki Soichiro
//
//**************************************
#ifndef _SCORE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "number.h"

//*****************
// �}�N����`
//*****************
#define MAX_DIGIT (8)

//********************
// �I�u�W�F�N�g�N���X
//********************
class CScore :public CObject
{
public:
	CScore(int nPriority = 5);	// �R���X�g���N�^
	~CScore();					// �f�X�g���N�^
	static CScore* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���̎擾
	D3DXVECTOR2 GetSize(void) { return m_size; };	// �傫�����̎擾
	static void SetScore(int nScore);	// �X�R�A�̐ݒ�
	static void Add(int nValue);		// �X�R�A���Z
	int Digit(int nScore);				// �������̎擾
	static int GetScore(void) { return m_nScore; }// �X�R�A���̎擾

private:
	int  m_nIdxTexture;						// �e�N�X�`���̃C���f�b�N�X
	static CNumber* m_apNumber[MAX_DIGIT];	// �i���o�[�ւ̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR2 m_size;		// �傫��
	static int m_nScore;	// �X�R�A
};
#endif