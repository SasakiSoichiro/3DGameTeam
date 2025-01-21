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
	InitModel();
	InitPlayer();
	
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
	UninitModel();
	UninitPlayer();

}

//---------------
//	�X�V����
//---------------
void UpdateGame(void)
{
	UpdataMeshfield();
	UpdataMeshWall();
	UpdateCamera();
	UpdateLight();
	UpdateModel();
	UpdatePlayer();

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
	SetCamera();
	DrawModel();
	DrawPlayer();

}