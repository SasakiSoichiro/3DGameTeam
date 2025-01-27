//=============================================================================
//
// スローモーション処理 [slow.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _SLOW_H_
#define _SLOW_H_
#include "main.h"

#define SLOW (4);

//構造体
typedef struct
{
	float fMulti;
	float fDivi;
	int nMulti;
	int nDivi;
	bool bUse;
}Slow;

//プロトタイプ宣言
void InitSlow(void);
void SetSlow(void);
Slow*GetSlow(void);

#endif