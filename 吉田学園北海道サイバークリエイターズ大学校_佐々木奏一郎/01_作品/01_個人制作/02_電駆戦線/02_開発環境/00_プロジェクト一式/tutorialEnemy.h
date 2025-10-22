//**************************************
//
// �G�l�~�[���� [enemy.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _TUTORIALENEMY_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TUTORIALENEMY_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"
#include "motion.h"
#include "enemyState.h"
#include "state.h"

class CEnemyLifeManager;

//********************
// �G�l�~�[�N���X
//********************
class CTutorialEnemy :public CObject
{
public:
	CTutorialEnemy(int nPriority = 4);				// �R���X�g���N�^
	~CTutorialEnemy();								// �f�X�g���N�^
	static CTutorialEnemy* Create(D3DXVECTOR3 pos);	// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetLife(int nLife) { m_nLife = nLife; }		// ���C�t�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// �������̎擾
	CMotion* GetMotion(void) { return m_pMotion; }		// ���[�V�������̎擾
	CModel* GetModel(int nIdx) { return m_apModel[nIdx]; }// ���f�����̎擾
	int GetLife(void) { return m_nLife; }				// ���C�t���̎擾
	static int GetNumAll(void) { return m_nNumAll; }	// ���݂̑����̎擾
	void LoadMotion(const char* pMotionScript);			// ���[�V�����e�L�X�g��ǂݍ���
	void SetMotion(int nType) { m_pMotion->SetMotion(nType); }// ���[�V�����̐ݒ�
	static void EnemyUpdate(void);
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_oldPos;	// �O�t���[���̈ʒu
	D3DXVECTOR3 m_move;		// ��������
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_fAngle;			// ����
	int m_nLife;			// ���C�t
	int m_nIdxXFile;		// �g�����f���̔ԍ�
	CMotion* m_pMotion;		// ���[�V�����ւ̃|�C���^
	CModel* m_apModel[15];	// ���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;		// �g���Ă��郂�f����
	int m_nHitCool;
	static int m_nNumAll;	// ���݂̑���
	CEnemyLifeManager* m_pLifeManager;// ���C�t�̃}�l�[�W���[
	static constexpr int initLife = 4;// �̗͂̏�����
	static constexpr float SPEED = 1.0f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 55.0f;

};

#endif