#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//	—ñ‹“Œ^
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_TITLE,
	GAMESTATE_TUTORIAL,
	GAMESTATE_RESULT,
	GAMESTATE_RETRY,
	GAMESTATE_QUIT,
	GAMESTATE_MAX
}GAMESTATE;

void InitGame(void);
void UinitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetEnablePause(bool bPause);
void SetGameState(GAMESTATE state);
bool GetEditState(void);

#endif // !_GAME_H_
