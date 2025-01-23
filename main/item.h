#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#define MAX_ITEM (6)

typedef enum
{
	ITEMTYPE_ONE = 0,	//	åÆÇÃè„ïî
	ITEMTYPE_TWO,		//	åÆÇÃâ∫ïî
	ITEMTYPE_THREE,		//	åÆ
	ITEMTYPE_FOUR,		//	Ç»Ç¨Ç»ÇΩ
	ITEMTYPE_FIVE,		//	ã~ã}î†
	ITEMTYPE_SIX,		//	â˘íÜéûåv
	ITEMTYPE_MAX
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	
	bool bUse;
	ITEMTYPE type;
}ITEM;

void InitItem(void);
void UinitItem(void);
void UpdateItem(void);
void DrawItem(void);
ITEM* GetItem(void);

#endif // !_ITEM_H_