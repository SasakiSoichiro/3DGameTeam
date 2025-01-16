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
	GAMESTATE_MAX
}GAMESTATE;

void InitGame(void);
void UinitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif // !_GAME_H_
