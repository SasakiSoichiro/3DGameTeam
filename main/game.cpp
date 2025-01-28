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
#include "pause.h"
#include "enemy.h"
#include "edit.h"
#include "sound.h"

// �Q�[���̏��
GAMESTATE g_gameState = GAMESTATE_NONE;

// ��ԊǗ��J�E���^�[
int g_nCounterGameState = 0;

//	�|�[�Y
bool g_bPause = false;

bool g_bEdit = false;

//---------------
//	����������
//---------------
void InitGame(void)
{
	//BGM��炷
	PlaySound(SOUND_LABEL_BGM2);

	InitLighr();
	InitCamera();
	InitMeshfield();
	InitPlayer();
	Inititem();
	InitTime();
	InitEnemy();
	InitEdit();
	LoadEdit();
	InitBlock();
	Setitem(D3DXVECTOR3(50.0f, 40.0f, 0.0f), ITEMTYPE_ONE);
	Setitem(D3DXVECTOR3(50.0f, 40.0f, 0.0f), ITEMTYPE_FOUR);

	InitBillboard();
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_0,D3DXVECTOR3(15.0f,35.0f,0.0f));
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_1, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	SetEnemy(D3DXVECTOR3(20.0f, 0.0f, 0.0f),0);

	InitPause();

	//����������
	g_bEdit = false;
}

//---------------
//	�I������
//---------------
void UinitGame(void)
{
	//���y���~�߂�
	StopSound();

	UninitLight();
	UninitMeshfield();
	UninitCamera();
	UninitBlock();
	UninitPlayer();
	UninitEnemy();
	Uinititem();
	UninitTime();
	UninitEdit();
	UninitBillboard();
	UninitPause();

}

//---------------
//	�X�V����
//---------------
void UpdateGame(void)
{

	if (KeybordTrigger(DIK_TAB) == true)

	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{
		UpdatePause();
	}
	if (g_bEdit == true&&KeybordTrigger(DIK_F1))
	{
		g_bEdit = false;

		InitBlock();
		LoadEdit();
	}
	else if (g_bEdit == false && KeybordTrigger(DIK_F1))
	{
		g_bEdit = true;

	}
	if (g_bPause == false)
	{
		if (g_bEdit == false)
		{
			UpdateMeshfield();
			UpdateCamera();
			UpdateLight();
			UpdateBlock();
			UpdatePlayer();
			UpdateEnemy();
			UpdateBillboard();
			Updateitem();
			UpdateTime();


			if (KeybordTrigger(DIK_O) == true || JoyPadTrigger(JOYKEY_A) == true)
			{
				SetResult(RESULT_CLEAR);
				SetFade(MODE_RESULT);
			}

			if (KeybordTrigger(DIK_P) == true || JoyPadTrigger(JOYKEY_B) == true)
			{
				SetResult(RESULT_GAMEOVER);
				SetFade(MODE_RESULT);
			}

		}
		else if (g_bEdit == true)
		{
			UpdateCamera();
			UpdateEdit();
		}

	}

	switch (g_gameState)
	{
	case GAMESTATE_RESULT:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�
			SetResult(RESULT_GAMEOVER);
			SetFade(MODE_RESULT);
			g_nCounterGameState = 0;
		}
		break;

	case GAMESTATE_RETRY:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�
			SetFade(MODE_GAME);
			g_nCounterGameState = 0;
		}

		break;

	case  GAMESTATE_QUIT:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 40)
		{
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�
			SetFade(MODE_TITLE);
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
	DrawEnemy();
	DrawTime();

	DrawBillboard();


	if (g_bPause == true)
	{
		DrawPause();
	}
	if (g_bEdit == true)
	{
		DrawEdit();
	}
}

//	�ۂ�
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

bool GetEditState(void)
{
	return g_bEdit;
}