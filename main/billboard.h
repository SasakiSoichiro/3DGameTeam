//====================================================
//
// 木の処理 [billboard.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BILLBOARD (11)

//アイテムの種類
typedef enum
{
	BILLBOARDTYPE_0,
	BILLBOARDTYPE_1,
	BILLBOARDTYPE_2,
	BILLBOARDTYPE_3,
	BILLBOARDTYPE_MAX
}TYPE;

static const char* ITEM_TEXTURE[BILLBOARDTYPE_MAX] =
{
	"data\\texture\\Wood.png",
	"data\\texture\\itembilbord.jpg",
	"data\\texture\\batu.png",
	"data\\texture\\maru.png",

};
//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き(角度)
	D3DXVECTOR3 VtxMaxBillboard;
	D3DXVECTOR3 VtxMinBillboard;
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	TYPE nType;
	bool bUse;				//使用しているかどうか
}Billboard;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitBillboard();
void UninitBillboard();
void UpdateBillboard();
void DrawBillboard();
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size);
#endif