//==========================================
//
//		�X�e�[�W			stage.cpp
//			ryuusei hirata
//
//=========================================
#include "stage.h"
#include "block.h"

void LoadStage(void)
{
	//��000
	SetBlock(D3DXVECTOR3(0.0f, 0.0f, 0.0f),BLOCK_HOUSE00);

	//��01
	SetBlock(D3DXVECTOR3(200.0f, 0.0f, -200.0f), BLOCK_HOUSE01);

}