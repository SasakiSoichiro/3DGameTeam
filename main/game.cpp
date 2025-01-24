//==================================
//		���[�ނ̏���	game.cpp
//			ryuusei.hirata 
//==================================
#include "input.h"
#include "game.h"
#include "fade.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "model.h"
#include "player.h"
#include "motion.h"
#include "stage.h"
#include "item.h"
#include "block.h"
#include "time.h"
#include "billboard.h"

// �Q�[���̏��
GAMESTATE g_gameState = GAMESTATE_NONE;

// ��ԊǗ��J�E���^�[
int g_nCounterGameState = 0;

//	�|�[�Y
bool g_bPause = false;

//---------------
//	����������
//---------------
void InitGame(void)
{
	InitCamera();
	InitLighr();
	InitMeshWall();
	InitMeshfield();
	InitBlock();
	InitPlayer();
	LoadStage();
	Inititem();
	Setitem(D3DXVECTOR3(100.0f, 50.0f, 200.0f), ITEMTYPE_FOUR);
	InitTime();
	InitBillboard();
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_0);
}

//---------------
//	�I������
//---------------
void UinitGame(void)
{
	UninitLight();
	UninitMeshfield();
	UninitMeshWall();
	UninitCamera();
	UninitBlock();
	UninitPlayer();
	Uinititem();
	UninitTime();
	UninitBillboard();
}

//---------------
//	�X�V����
//---------------
void UpdateGame(void)
{
	UpdataMeshfield();
	UpdateMeshWall();
	UpdateCamera();
	UpdateLight();
	UpdateBlock();
	UpdatePlayer();
	Updateitem();
	UpdateTime();
	UpdateBillboard();

	if (KeybordTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true)
	{
		SetResult(RESULT_CLEAR);
		SetFade(MODE_RESULT);
	}

	if (KeybordTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_B) == true)
	{
		SetResult(RESULT_GAMEOVER);
		SetFade(MODE_RESULT);
	}


	switch (g_gameState)
	{
	case GAMESTATE_RESULT:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 100)
		{
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�
			SetFade(MODE_RESULT);
			g_nCounterGameState = 0;
		}
		break;

	default:
		break;
	}
}

//---------------
//	�`�揈��
//---------------
void DrawGame(void)
{
	DrawMeshfield();
	DrawBlock();
	Drawitem();
	DrawPlayer();
	DrawMeshWall();
	DrawTime();
	DrawBillboard();
}