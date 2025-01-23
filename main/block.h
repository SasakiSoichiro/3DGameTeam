//=============================================================================
//
//	�u���b�N���� [block.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _BLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "player.h"
#define NUM_BLOCK (128)
typedef enum
{
	BLOCK_NORMAL=0,		//���ʂ̃u���b�N
	BLOCK_PRESSUREPLATERED,//������
	BLOCK_PRESSUREPLATEBLUE,
	BLOCK_PRESSUREPLATEGREEN,
	BLOCK_WALL,			//��
	BLOCK_MAX
}BLOCKTYPE;

typedef struct
{
	bool red;
	bool blue;
	bool green;
}BoolPressurePlate;

typedef struct
{
	LPD3DXMESH pMesh;					//���b�V���i���_���)�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 apTexture[128];	//�e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//�}�e���A���̐�
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin, vtxMax;			//���f���̍ŏ��l,�ő�l
	int nType;
	bool bUse;

}BLOCK;

static const char* X_BLOCK[BLOCK_MAX] =
{
	"data\\MODEL\\OBJ\\box000.x",
	"data\\MODEL\\OBJ\\pressureplate.x",
	"data\\MODEL\\OBJ\\pressureplate_blue.x",
	"data\\MODEL\\OBJ\\pressureplate_green.x",
	"data\\MODEL\\OBJ\\wall001.x"
};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld);
void GimmickBlock(int nType);
BoolPressurePlate GetPlate(void);

#endif