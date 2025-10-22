//*****************************************
//
// ��̏��� [skydoom.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "humansatellite.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//******************
// �}�N����`
//******************
#define SPEED (0.0015f)

//*****************
// �R���X�g���N�^
//*****************
CHumanSatellite::CHumanSatellite(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_fAngle = 0.0f;
}

//*****************
// �f�X�g���N�^
//*****************
CHumanSatellite::~CHumanSatellite()
{
}

//******************
// �C���X�^���X����
//*******************
CHumanSatellite* CHumanSatellite::Create(D3DXVECTOR3 pos)
{
	CHumanSatellite* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CHumanSatellite;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CHumanSatellite::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\satellite.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);

	SetRot(D3DXVECTOR3(0.2f, 0.5f, 0.3f));

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CHumanSatellite::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CHumanSatellite::Update(void)
{
	D3DXVECTOR3 pos = NONE;

	// �X�e�[�W�̎��������
	pos.x = sinf(m_fAngle) * 1200.0f;
	pos.y = 400.0f + cosf(m_fAngle) * 1200.0f;
	// �p�x��i�߂�
	m_fAngle += 0.005f;
	// �ʒu�ݒ�
	SetPos(pos);
}

//*****************
// �`�揈��
//*****************
void CHumanSatellite::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CHumanSatellite::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CHumanSatellite::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CHumanSatellite::GetPos(void)
{
	return CObjectX::GetPos();
}
D3DXVECTOR3 CHumanSatellite::GetRot(void)
{
	return CObjectX::GetRot();
}