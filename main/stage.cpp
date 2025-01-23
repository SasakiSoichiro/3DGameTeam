//==========================================
//
//		ステージ			stage.cpp
//			ryuusei hirata
//
//=========================================
#include "stage.h"
#include "model.h"


void LoadStage(void)
{
	//家000
	SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f),MODELTYPE_0);

	//家01
	SetModel(D3DXVECTOR3(500.0f, 0.0f, -500.0f), MODELTYPE_1);



}