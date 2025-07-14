//==========================================
//
//		ステージ			stage.cpp
//			ryuusei hirata
//
//=========================================
#include "stage.h"
#include "block.h"

void LoadStage(void)
{
	//家000
	SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f),BLOCK_HOUSE000_L);

	////家01
	//SetBlock(D3DXVECTOR3(200.0f, 0.0f, -200.0f), BLOCK_HOUSE01);

	////	ウォールマリア
	//SetBlock(D3DXVECTOR3(1100.0f, 0.0f, 500.0f), BLOCK_WALL00);
	//SetBlock(D3DXVECTOR3(-500.0f, 0.0f, -1500.0f), BLOCK_WALL01);

	//SetBlock(D3DXVECTOR3(-2100.0f, 0.0f, -2500.0f), BLOCK_WALL00);
	//SetBlock(D3DXVECTOR3(2500.0f, 0.0f, 2500.0f), BLOCK_WALL01);

}