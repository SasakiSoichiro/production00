//*****************************************
//
// �u���b�N���� [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "attackbolt.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
const D3DXVECTOR3 CAttackBolt::ROT_MOVE = D3DXVECTOR3(0.08f, 0.05f, 0.1f);

//*****************
// �R���X�g���N�^
//*****************
CAttackBolt::CAttackBolt(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_move = NONE;
	m_fAngle = 0.0f;
	m_nLife = 0;
	SetType(TYPE_BOLT);
}

//*****************
// �f�X�g���N�^
//*****************
CAttackBolt::~CAttackBolt()
{
}

//******************
// �C���X�^���X����
//*******************
CAttackBolt* CAttackBolt::Create(D3DXVECTOR3 pos,float fAngle)
{
	CAttackBolt* pAttackBolt;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pAttackBolt = new CAttackBolt;	
		pAttackBolt->Init(pos);			
		pAttackBolt->SetAngle(fAngle);

		return pAttackBolt;				
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CAttackBolt::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\bolt.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);
	m_move.y = jump;
	m_nLife = maxLife;

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CAttackBolt::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CAttackBolt::Update(void)
{
	// ���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// ���[�u�l�����߂�
	m_move.x = sinf(m_fAngle) * speed;
	m_move.y -= horizon;
	m_move.z = cosf(m_fAngle) * speed;

	// �ʒu�X�V
	pos += m_move;
	rot += ROT_MOVE;

	// �l�𔽉f
	SetRot(rot);
	SetPos(pos);

	// �����ŏI��
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CAttackBolt::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CAttackBolt::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CAttackBolt::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CAttackBolt::GetPos(void)
{
	return CObjectX::GetPos();
}
D3DXVECTOR3 CAttackBolt::GetRot(void)
{
	return CObjectX::GetRot();
}