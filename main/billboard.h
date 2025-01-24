//====================================================
//
// �؂̏��� [billboard.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BILLBOARD (11)

//�A�C�e���̎��
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
//�A�C�e���̍\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����(�p�x)
	D3DXVECTOR3 VtxMaxItem;
	D3DXVECTOR3 VtxMinItem;
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	TYPE nType;
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Item;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType);
#endif