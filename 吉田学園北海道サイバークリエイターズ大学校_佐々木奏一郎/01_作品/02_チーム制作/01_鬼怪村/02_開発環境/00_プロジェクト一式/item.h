//=============================================================================
//
// �A�C�e������ [item.h]
// Author : HRT ryuusei
//
//=============================================================================

#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

// �}�N����`
#define MAX_ITEM (6)

// ��ނ̗񋓌^
typedef enum
{
    ITEMTYPE_ONE = 0,    // ���̏㕔
    ITEMTYPE_TWO,        // ���̉���
    ITEMTYPE_THREE,      // �������v
    ITEMTYPE_FOUR,       // �Ȃ��Ȃ�
    ITEMTYPE_FIVE,       // �~�}��
    ITEMTYPE_SIX,        // �����d��
    ITEMTYPE_MAX
}ITEMTYPE;

// ���f���񋓌^
static const char* ITEM_MODEL[ITEMTYPE_MAX] =
{
    "data\\model\\key_top.x",
    "data\\model\\key_bottom.x",
    "data\\model\\pocketwatch000.x",
    "data\\model\\naginata.x",
    "data\\model\\recovery.x",
    "data\\model\\flashlight.x",
};

typedef struct
{
    LPD3DXMESH pMesh;                   //  ���_���̃|�C���^�[
    LPDIRECT3DTEXTURE9 pTexture[128];   //  �e�N�X�`���̃|�C���^�[
    LPD3DXBUFFER pBufferMat;            //  �}�e���A���̃|�C���^�[
    DWORD dwNuMat;                      //  �}�e���A���̐�
}ITEMINFO;

// �A�C�e���\����
typedef struct
{
    D3DXVECTOR3 pos;
    D3DXVECTOR3 rot;
    D3DXMATRIX mtxWorld;
    int nType;
    bool bUse;
    bool bHave;
    bool bOldHave;
    bool bHold;
    int nIdxUI;
}ITEM;

// �v���g�^�C�v�錾
void Inititem(void);
void Uninititem(void);
void Updateitem(void);
void Drawitem(void);
ITEM* Getitem(void);
void Setitem(D3DXVECTOR3 pos, int nType);
bool IsNeed();

#endif // !_ITEM_H_