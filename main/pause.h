#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

// ç\ë¢ëÃ
typedef struct
{
	D3DXVECTOR3 pos;	// à íu
}Pause;

// óÒãì
typedef enum
{
	PAUSEMENYU_COTINUE = 0,
	PAUSEMENYU_RETRY,
	PAUSEMENYU_QUIT,
	PAUSEMENYU_MAX
}PAUSEMENYU;

void InitPause(void);
void UninitPause(void);
void DrawPause(void);
void UpdatePause(void);

#endif // !_PAUSE_H_
