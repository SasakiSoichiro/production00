//************************************
//
// �Q�[���V�[������ [game.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _GAME_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"


class CBlockManager;
class CObject3D;			// object3D�ւ̃|�C���^
class CMesh;				// ���b�V���ւ̃|�C���^
class CPlayer;				// �v���C���[�ւ̃|�C���^
class CWave;				// �E�F�[�u�ւ̃|�C���^
class CSlow;				// �X���[�ւ̃|�C���^
class CSnagManager;			// ��Q���}�l�[�W���[�ւ̃|�C���^
class CPauseManager;		// �|�[�Y�}�l�[�W���[�ւ̃|�C���^
class CRailManager;			// ���[���}�l�[�W���[�ւ̃|�C���^


//********************
// �Q�[���V�[���N���X
//********************
class CGame:public CScene
{
public:
	// ���
	typedef enum
	{
		STATE_NONE=0,	// �����Ȃ�
		STATE_NORMAL,	// �ʏ�
		STATE_END,		// �I��
		STATE_MAX
	}STATE;
	CGame();		// �R���X�g���N�^
	~CGame();		// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ������
	void Uninit(void);					// �I��
	void Update(void);					// �X�V
	void Draw(void);					// �`��
	void SetPos(D3DXVECTOR3 pos) {};	// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};	// ����
	D3DXVECTOR3 GetPos(void) { return NONE; }								// �ʒu���擾
	static CObject3D* GetCObject3D(void) { return m_pObject3D; }			// ���擾
	static CMesh* GetCMesh(void) { return m_pMesh; }						// ���擾
	static CPlayer* GetCPlayer(void) { return m_pPlayer; }					// ���擾
	static CSlow* GetCSlow(void) { return m_pSlow; }						// ���擾
	static CBlockManager* GetCBlockManager(void) { return m_pBlockManager; }// ���擾
	static CSnagManager* GetCSnagManager(void) { return m_pSnagManager; }	// ���擾
	static void SetState(STATE state) { m_State = state; }					// ��Ԑݒ�
	static STATE GetState(void) { return m_State; }							// ��ԏ��擾
private:
	static CObject3D* m_pObject3D;			// object3D�ւ̃|�C���^
	static CMesh* m_pMesh;					// ���b�V���ւ̃|�C���^
	static CPlayer* m_pPlayer;				// �v���C���[�ւ̃|�C���^
	static CWave* m_pWave;					// �E�F�[�u�ւ̃|�C���^
	static CSlow* m_pSlow;					// �X���[�ւ̃|�C���^
	static STATE m_State;					// ��Ԃւ̃|�C���^
	static CBlockManager* m_pBlockManager;	// �u���b�N�}�l�[�W���ւ̃|�C���^
	static CSnagManager* m_pSnagManager;	// ��Q���}�l�[�W���[�ւ̃|�C���^
	static CPauseManager* m_pPauseManager;	// �|�[�Y�}�l�[�W���ւ̃|�C���^
	static CRailManager* m_pRailManager;	// �|�[�Y�}�l�[�W���ւ̃|�C���^
	int m_nCnt;
	D3DXVECTOR3 m_pos;
};
#endif