//***************************************
//
// �I�u�W�F�N�g���� [object.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _OBJECT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//******************
// �}�N����`
//******************
#define MAX_OBJ (512)	// �`�揇���Ƃ̃I�u�W�F�N�g�̍ő吔
#define MAX_PRI (8)		// �`�揇�̍ő吔

//********************
// �I�u�W�F�N�g�N���X
//********************
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G
		TYPE_EBULLET,	// �G�̒e
		TYPE_PBULLET,	// �v���C���[�̒e
		TYPE_BG,		// �w�i
		TYPE_MAX
	}TYPE;
	CObject(int nPriority=3);			// �R���X�g���N�^
	virtual ~CObject();					// �f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 pos)=0;	// ������(�������z�֐�)
	virtual void Uninit(void)=0;				// �I��(�������z�֐�)
	virtual void Update(void)=0;				// �X�V(�������z�֐�)
	virtual void Draw(void)=0;					// �`��(�������z�֐�)
	virtual void SetPos(D3DXVECTOR3 pos) = 0;	// �ʒu(�������z�֐�)
	virtual void SetRot(D3DXVECTOR3 rot) = 0;	// ����(�������z�֐�)
	virtual D3DXVECTOR3 GetPos(void) = 0;		// �ʒu���(�������z�֐�)
	static void ReleaseAll(void);			// �S�ẴI�u�W�F�N�g�I��
	static void UpdateAll(void);			// �S�ẴI�u�W�F�N�g�X�V
	static void DrawAll(void);				// �S�ẴI�u�W�F�N�g�`��
	void SetType(TYPE type);				// ��ސݒ�
	TYPE GetType(void) { return m_type; }	// ��ނ̏��擾
	static CObject* GetObject(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; }	// �I�u�W�F�N�g���擾
	static int GetNumAll(void) { return m_nNumAll; }											// ���݂̃I�u�W�F�N�g�����擾
	static int GetNumPriority(int nPriority) { return m_nNumPriority[nPriority]; }				// �`�揇���Ƃ̃I�u�W�F�N�g�����擾
protected:
	void Release(void);// 1�̏I��
private:
	static CObject* m_apObject[MAX_PRI][MAX_OBJ];	// �I�u�W�F�N�g�̃|�C���^
	static int m_nNumAll;							// �I�u�W�F�N�g�̑���
	static int m_nNumPriority[MAX_PRI];				// �`�揇���Ƃ̑���
	int m_nID;			// �������g��ID
	TYPE m_type;		// ���
	int m_nPriority;	// �D�揇�ʂ̈ʒu
};	
#endif