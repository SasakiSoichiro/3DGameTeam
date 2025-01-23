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
	//InitItem();
	//SetItem(D3DXVECTOR3(100.0f, 0.0f, 200.0f), ITEMTYPE_FIVE);
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
	//UinitItem();
}

//---------------
//	更新処理
//---------------
void UpdateGame(void)
{
	UpdataMeshfield();
	UpdateMeshWall();
	UpdateCamera();
	UpdateLight();
	UpdateBlock();
	UpdatePlayer();
	//UpdateItem();

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
			g_gameState = GAMESTATE_NONE;	// 何もしていない
			SetFade(MODE_RESULT);
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
	//DrawItem();
	DrawPlayer();
	DrawMeshWall();
}