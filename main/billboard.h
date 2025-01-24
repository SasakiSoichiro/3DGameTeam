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
	ITEMTYPE_0,
	ITEMTYPE_1,
	ITEMTYPE_MAX
}TYPE;

static const char* ITEM_TEXTURE[ITEMTYPE_MAX] =
{
	"data\\TEXTURE\\reta.png",

};
//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き(角度)
	D3DXVECTOR3 VtxMaxItem;
	D3DXVECTOR3 VtxMinItem;
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	TYPE nType;
	bool bUse;				//使用しているかどうか
}Item;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType);
#endif