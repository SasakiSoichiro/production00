//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : Sasaki Soichiro
//
//=============================================================================
#ifndef _OBJECT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//******************
// �}�N����`
//******************
#define MAX_OBJ (512)	// �I�u�W�F�N�g�̍ő吔
#define MAX_PRI (8)		// �`�揇�̍ő吔

//********************
// �I�u�W�F�N�g�N���X
//********************
class CObject
{
public:
	// ���
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G
		TYPE_BOLT,		// �{���g
		TYPE_PAUSE,		// �|�[�Y
		TYPE_SCENE,		// �V�[��
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
	static void ReleaseAll(void);				// �S�ă����[�X
	static void UpdateAll(void);				// �S�čX�V
	static void DrawAll(void);					// �S�ĕ`��
	void SetType(TYPE type);					// ��ނ̐ݒ�
	TYPE GetType(void) { return m_type; }		// ��ޏ��̎擾
	static int GetNumAll(void) { return m_nNumAll; }// �I�u�W�F�N�g�̑����擾
	static int GetNumPriority(int nPriority) { return m_nNumPriority[nPriority]; }// �`�揇���Ƃ̑����擾
	static CObject* GetTop(int nPriority) { return m_apTop[nPriority]; }// �g�b�v���擾(���X�g�\��)
	CObject* GetNext(void) { return m_pNext; }							// �l�N�X�g���擾(���X�g�\��)
	static void Destroy(CObject* pObject);
protected:
	void Release(void);					// �����[�X
private:
	static int m_nNumAll;				// �I�u�W�F�N�g�̑���
	static int m_nNumPriority[MAX_PRI];	// �`�揇���Ƃ̑���
	TYPE m_type;						// ���
	int m_nPriority;					// �D�揇�ʂ̈ʒu
	static CObject* m_apTop[MAX_PRI];	// �g�b�v�ւ̃|�C���^(���X�g�\��)
	static CObject* m_apCur[MAX_PRI];	// ���݂ւ̃|�C���^(���X�g�\��)
	CObject* m_pNext;					// �l�N�X�g�ւ̃|�C���^(���X�g�\��)
	CObject* m_pPrev;					// �O�̃|�C���^(���X�g�\��)
	bool m_bDeath;						// ���S�t���O
};	
#endif