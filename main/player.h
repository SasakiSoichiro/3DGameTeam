#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

#define PLAYER_SSIZE_X (float)(30.0f)
#define PLAYER_SSIZE_Z (float)(30.0f)

//	モーションタイプ
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//	ニュートラル
	MOTIONTYPE_MOVE,		//	移動
	MOTIONTYPE_ACTION,		//	攻撃
	MOTIONTYPE_JUNP,		//	ジャンプ
	MOTIONTYPE_LANDING,		//	着地
	MOTIONTYPE_MAX
}MOTIONTYPE;

//	キーの構造体
typedef struct
{
	float fposx;	//	位置
	float fposy;
	float fposz;
	float frotx;	//	向き
	float froty;
	float frotz;
}KEY;

//	キー情報の構造体
typedef struct
{
	int nFrame;		//	フレーム数
	KEY aKey[10];	//	各パーツの要素
}KEY_INFO;

//	モーション情報の構造体
typedef struct
{
	bool bLoop;					//	ループするかどうか
	int nNumKey;				//	キーの総数
	KEY_INFO aKeyinfo[10];		//	キー情報
}MOTION_INFO;

//	構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Oldpos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 moverot;
	int nIndxShadow;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	Model aModel[10];
	int nNumModel;
	D3DXMATRIX mtxWold;				//	ワールドマトリックス
	MOTION_INFO aMotionInfo[10];	//	モーション情報
	int nNumMotion;					//	モーションの総数
	MOTIONTYPE MotionType;
	int nNumKey;					//	キー総数
	bool bLoopMotion;				//	ループするか
	int nKey;						//	現在キーナンバー
	int nextKey;
	int nCntMotion;					//	モーションカウンター
}Player;

//	プロトタイプ
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void UpdateMotion(int count);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif // !_PLAYER_H_