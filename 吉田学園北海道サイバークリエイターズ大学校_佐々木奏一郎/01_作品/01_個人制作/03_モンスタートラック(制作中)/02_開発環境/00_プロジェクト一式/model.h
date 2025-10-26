//***********************************
//
//	���f������ [model.h]
// Author:Sasaki Soichiro
//
//***********************************
#ifndef _MODEL_H_// ���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h
//**********************
#include"main.h"
#include"Xmodel.h"

//*********************
// ���f���N���X
//*********************
class CModel
{
public:
    CModel();// �R���X�g���N�^
    ~CModel();// �f�X�g���N�^
    static CModel*Create(D3DXVECTOR3 pos, const char* pFileName);// �C���X�^���X����
    void Init(D3DXVECTOR3 pos); // ������
    void Uninit(void);          // �I��
    void Update(void);          // �X�V
    void Draw(void);            // �`��
    void SetParent(CModel* pModel);// �e���f���̐ݒ�
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }               // �ʒu�̐ݒ�
    void SetOffSetPos(D3DXVECTOR3 pos) { m_offsetPos = pos; }   // �I�t�Z�b�g�̐ݒ�(�ʒu)
    void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }               // �����̐ݒ�
    void SetSize(D3DXVECTOR3 size) { m_size = size; }           // �傫���̐ݒ�
    void SetOffSetRot(D3DXVECTOR3 rot) { m_offsetRot = rot; }   // �I�t�Z�b�g�̐ݒ�(����)
    void SetIdxXFile(int nIdxXFile) { m_nIdxXFile = nIdxXFile; }
    D3DXVECTOR3 GetPos(void) { return m_pos; }                  // �ʒu���擾(�ʒu)
    D3DXVECTOR3 GetRot(void) { return m_rot; }                  // �ʒu���擾(����)
    D3DXVECTOR3 GetOffSetPos(void) { return m_offsetPos; }      // �I�t�Z�b�g���擾(�ʒu)
    D3DXVECTOR3 GetOffSetRot(void) { return m_offsetRot; }      // �I�t�Z�b�g���擾(����)
    D3DXVECTOR3 GetSize(void) { return m_size; }
    D3DXMATRIX GetMtxWorld(void);                               // ���[���h�}�g���b�N�X���̎擾
private:
    CXModel::XMODEL m_pXModel;  // ���f���ւ̃|�C���^
    D3DXVECTOR3 m_pos;          // �ʒu
    D3DXVECTOR3 m_offsetPos;    // �I�t�Z�b�g�̈ʒu
    D3DXVECTOR3 m_rot;          // ����
    D3DXVECTOR3 m_size;         // �傫��
    D3DXVECTOR3 m_offsetRot;    // �I�t�Z�b�g�̌���
    D3DXMATRIX m_mtxWorld;      // ���[���h�}�g���b�N�X
    CModel* m_pParent;          // �e�̃��f���ւ̃|�C���^
    int m_nIdxXFile;            // �g�����f���̔ԍ�
};
#endif