//==================================
//		げーむの処理	game.cpp
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
<<<<<<< HEAD
#include "billboard.h"
=======
#include "pause.h"
>>>>>>> 0982182f75b1e4b257d3d80362920d25963a9782

// ゲームの状態
GAMESTATE g_gameState = GAMESTATE_NONE;

// 状態管理カウンター
int g_nCounterGameState = 0;

//	ポーズ
bool g_bPause = false;

//---------------
//	初期化処理
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
	InitTime();
<<<<<<< HEAD
	InitBillboard();
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_0);
=======
	InitPause();

>>>>>>> 0982182f75b1e4b257d3d80362920d25963a9782
}

//---------------
//	終了処理
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
<<<<<<< HEAD
	UninitBillboard();
=======
	UninitPause();
>>>>>>> 0982182f75b1e4b257d3d80362920d25963a9782
}

//---------------
//	更新処理
//---------------
void UpdateGame(void)
{
<<<<<<< HEAD
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
=======
	if (KeybordTrigger(DIK_TAB) == true)
>>>>>>> 0982182f75b1e4b257d3d80362920d25963a9782
	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{
		UpdatePause();
	}

	if (g_bPause == false)
	{
		UpdataMeshfield();
		UpdateMeshWall();
		UpdateCamera();
		UpdateLight();
		UpdateBlock();
		UpdatePlayer();
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

	switch (g_gameState)
	{
	case GAMESTATE_RESULT:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;	// 何もしていない
			SetResult(RESULT_GAMEOVER);
			SetFade(MODE_RESULT);
			g_nCounterGameState = 0;
		}
		break;

	case GAMESTATE_RETRY:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 30)
		{
			g_gameState = GAMESTATE_NONE;	// 何もしていない
			SetFade(MODE_GAME);
			g_nCounterGameState = 0;
		}

		break;

	case  GAMESTATE_QUIT:
		g_nCounterGameState++;
		if (g_nCounterGameState >= 40)
		{
			g_gameState = GAMESTATE_NONE;	// 何もしていない
			SetFade(MODE_TITLE);
			g_nCounterGameState = 0;
		}

		break;

	default:
		break;
	}
}

//---------------
//	描画処理
//---------------
void DrawGame(void)
{
	DrawMeshfield();
	DrawBlock();
	Drawitem();
	DrawPlayer();
	DrawMeshWall();
	DrawTime();
<<<<<<< HEAD
	DrawBillboard();
=======

	if (g_bPause == true)
	{
		DrawPause();
	}
}

//	ぽず
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

void SetGameState(GAMESTATE state)
{
	g_gameState = state;
>>>>>>> 0982182f75b1e4b257d3d80362920d25963a9782
}