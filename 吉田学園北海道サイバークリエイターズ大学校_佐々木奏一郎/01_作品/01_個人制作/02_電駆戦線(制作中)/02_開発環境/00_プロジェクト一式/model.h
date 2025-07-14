#pragma once
#include"main.h"
#include"Xmodel.h"
class CModel
{
public:
    CModel();
    ~CModel();
    static CModel*Create(D3DXVECTOR3 pos, const char* pFileName);
    void Init(D3DXVECTOR3 pos);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void SetParent(CModel* pModel);
    void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
    void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
    D3DXMATRIX GetMtxWorld();
private:
    CXModel::XMODEL m_pXModel;
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_rot;
    D3DXMATRIX m_mtxWorld;
    CModel* m_pParent;
    int m_nIdxXFile;
};
             