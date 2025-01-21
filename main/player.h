//=============================================================================
//
//	プレイヤー処理 [player.h]
// Author : 佐々木奏一郎
//
//=============================================================================

#ifndef _PLAYER_H_//このマクロ定義がされていなかったら
#define _PLAYER_H_//2銃インクルード防止のマクロ定義

#include "main.h"
#include "model.h"
#include "motion.h"

#define GRAVI (0.05f)			//重力
#define JUMP (2.0f)
#define OBJ_P (20.0f)
#define PARTS_MAX (20)
#define USEPARTS_MAX (20)

typedef enum
{
	RED = 0,
	BLUE,
	GREEN,
	PTYPE_MAX
}PTYPE;

typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_DAMAGE,
	PLAYERSTATE_MOVE,
	PLAYERSTATE_JUMP,
	PLAYERSTATE_ACTION,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 Offpos;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	D3DXMATRIX SwordmtxWorld;
	int nLife;
	int nType;
	PLAYERSTATE pState;
	Motion motion;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetMatrix(void);
void SetMotion(int nType);
Player* GetPlayer(void);
void ReadScriptPlayer(int nType);

#endif