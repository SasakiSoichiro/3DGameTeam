//=============================================================================
//
// タイマー処理 [time.h]
// Author:Marina Harada
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include"main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TIME (2)
#define MAX_TEX  (2)
#define MAX_MIN (2)

//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int ntime);
void SubTime(int nValue);
void Subtime(int nValue);
int GetTime(void);
int Gettime(void);

#endif