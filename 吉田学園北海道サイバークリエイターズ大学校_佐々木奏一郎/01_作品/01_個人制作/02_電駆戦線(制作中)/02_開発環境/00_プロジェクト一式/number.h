//********************************
// 
// �i���o�[�N���X
// Author Sasaki Soichiro
// 
//********************************
#ifndef _NUMBER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//****************
// �C���N���[�h
//****************
#include "main.h"

//******************
// �i���o�[�N���X
//******************
class CNumber
{
public:
	CNumber();// �R���X�g���N�^
	~CNumber();// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Draw(void);	// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetNumber(int nNum);		// �i���o�[�̐ݒ�
	void SetSize(D3DXVECTOR2 size);	// �傫���̐ݒ�
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR2 m_size;	// �傫��
	int nNum;			// �����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
};

//****************
// �L���N���X
//****************
class CSymbol
{
public:
	CSymbol();	// �R���X�g���N�^
	~CSymbol();	// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Draw(void);	// �`��
	void SetPos(D3DXVECTOR3 pos);					// �ʒu�̐ݒ�
	void SetSize(D3DXVECTOR2 size);					// �傫���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���̐ݒ�
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR2 m_size;	// �傫��
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
};
#endif