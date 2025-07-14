//=============================================================================
//
//    �����Q�[�W���� [gauge.h]
//    Author : Chikada
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

// �Q�[�W�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	bool bUse;			// �g�p���Ă��邩�ǂ���
	float fCnt;
	float fCnt1;
	bool bKeyhave;
}Gauge;

// �v���g�^�C�v�錾
void InitGauge(void);
void UinitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void SetGauge(D3DXVECTOR3 pos);

#endif // !_GAUGE_H_
