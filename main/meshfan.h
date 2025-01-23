//=============================================================================
//
//	���b�V���t�@������ [meshfan.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _MESHFAN_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHFAN_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"

//�}�N����`
#define CORNERCNT (5)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 VtxPos[CORNERCNT+1];
	D3DXMATRIX mtxWorld;
}MeshFan;
//�v���g�^�C�v�錾
void InitMeshFan(void);
void UninitMeshFan(void);
void UpdateMeshFan(void);
void DrawMeshFan(void);
#endif