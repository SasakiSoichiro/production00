//**********************************
//
// ���[������ [rail.h]
// Author:SasakiSoichiro
//
//**********************************
#ifndef _RAIL_H_// ���̃}�N����`������Ă��Ȃ�������
#define _RAIL_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//******************
// �}�N����`
//******************
#define BLOCK_TEXTURE (128)			//�u���b�N�̃e�N�X�`���̍ő吔
#define CONTROLL (4)				// �ŏ��̐���_�̌�
#define RAILBLOCK_NUM (CONTROLL+1)	// �u���b�N�̑���
#define MAX_POINT (32)				// �_�̍ő吔

class CRailBlock;
class CRailMesh;

//*********************
// ���[���N���X
//*********************
class CRail:public CObject
{
public:
	typedef enum
	{
		TYPE_CHARGE=0,
		TYPE_DISCHARGE,
		TYPE_MAX
	}TYPE;
	CRail();	// �R���X�g���N�^
	~CRail();	// �f�X�g���N�^
	static CRail* Create(D3DXVECTOR3 point0, D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3, int nType);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	D3DXVECTOR3 Curve(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, float t);// �J�[�u
	void AddPoint(D3DXVECTOR3 pos);					// ����_�ǉ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// �����̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu���擾
	bool Collision(D3DXVECTOR3 pos);				// �����蔻��
	void SetMesh(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);// ���b�V���̐ݒ�
	float GetAngle(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);// �_����_�̊p�x
	static void Change(void);
	static void InitAll(void) { m_nCntAll = 0; }
	void Save(void);	// �ۑ�
	void Load(void);	// �ǂݍ���

private:
	CRailBlock* m_pBlock[MAX_POINT];// ����_
	CRailBlock* m_pPrev;			// �ǂ���ʂ��Ă��邩�̊m�F
	int m_nNumPoint;				// ����_�̐�
	float m_fTime;					// ����
	float m_fTension;				// �e���V����
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	int m_nCurrentIdx;				// ���݂̈ʒu
	static int m_nPlayerCurrentIdx;		// ���݂̃v���C���[�̈ʒu
	static float m_fPlayerCurrentT;		// ���݂̃v���C���[�̎���
	int m_nCnt;						// ���[���𓮂����J�E���g
	int m_nIdx;						// ���[���̃C���f�b�N�X
	int m_nType;					// ���
	static int m_nCntAll;			// ���[�������݂��Ă��鐔
	static int m_nUse;				// ���ݐG��Ă��郌�[���̃C���f�b�N�X
	static int m_nOldUse;			// �O�t���[���ŐG�ꂽ���[���̃C���f�b�N�X
	CRailMesh* m_pMesh;				// ���[�����b�V���ւ̃|�C���^
	int m_nEffectCnt;				// �G�t�F�N�g�̏o��J�E���g
	static constexpr int effectCool = 3;// �G�t�F�N�g���o��N�[���^�C��
};

#endif