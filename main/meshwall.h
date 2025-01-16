#pragma once
#ifndef _MESHWALL_H_

#include "main.h"

//	�}�N���錾
#define SUIHEI (8)
#define SUITYOKU (1)
#define MESHWALL_T ((SUIHEI + 1) * (SUITYOKU + 1))		//	���_��
#define MESHWALL_P ((SUIHEI * SUITYOKU * 2 + (SUITYOKU - 1) * 4))		//	�|���S����
#define MESHWALL_I ((SUIHEI + 1) * 2 * SUITYOKU + (SUITYOKU - 1) * 2)	//	�C���f�b�N�X��

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
}MESHWALL;

//	�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdataMeshWall(void);
void DrawMeshWall(void);

#endif // !_MESHWALL_H_
