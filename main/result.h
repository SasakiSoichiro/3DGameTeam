#pragma once
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "game.h"
#include "input.h"

//	óÒãìå^
typedef enum
{
	RESULT_CLEAR = 0,
	RESULT_GAMEOVER,
	RESULT_MAX
}RESULT;

//	ç\ë¢ëÃ
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	bool bUse;			// égÇÌÇÍÇƒÇÈÇ©
	float fHeight;		// çÇÇ≥
	float fWidth;		// ïù
}Result;

void InitResult(void);
void UinitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(RESULT type);
RESULT GetResult();

#endif // !_RESULT_H_
