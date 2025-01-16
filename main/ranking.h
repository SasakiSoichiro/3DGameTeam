#pragma once
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//マクロ定義
#define MAX_RANK (5)					//表示順位数
#define MAX_RANKSCORE_NUM (8)			//表示スコア桁数
#define MAX_RANKSCORE_HEIGHT (100)		//ランキングUIの高さ
#define MAX_RANKSCORE_WIDTH (50)		//ランキングUIの幅
#define MAX_RANK_WIDTH (50)				//ランクUIの幅
#define MAX_RANK_SCORE_ANIM_TIME (30)	//点滅アニメーションの時間

#define FILE_TXT_SCORE "date\\ranking\\ranking.txt"	//スコアのCSVデータファイル

//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(const char* DateScore);
void SetRanking(int nScore);

#endif // !_RANKING_H_
