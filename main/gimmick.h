#pragma once
#ifndef _GIMMICK_H_
#define _GIMMICK_H_


#include "main.h"
#include "player.h"

#define MAX_DOOR (1)	//�h�A�̍ő吔

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 move;				//�ړ�
	D3DXVECTOR3 size;				//�T�C�Y
	D3DXVECTOR3 vtxMin, vtxMax;	//���_�̍ŏ��ő�
	D3DXMATRIX mtxWorld;			//�}�g���b�N�X
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD dwNumMat;
	bool bLanding;
	bool bUse;
	//bool bGoal;
	bool bMove;
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
bool CollisionBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
BLOCK* GetBlock(void);
bool IsGoal();
bool IsBill();

#endif
