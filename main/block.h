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
#define NUM_BLOCK (16)
typedef enum
{
	BLOCK_HOUSE00=0,		//���ʂ̃u���b�N
	BLOCK_HOUSE01,
	BLOCK_WALL00,
	BLOCK_WALL01,
	BLOCK_MAX
}BLOCKTYPE;

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
	"data\\model\\house000.x",
	"data\\model\\house01.x",
	"data\\model\\wallmaria.x",
	"data\\model\\wallmaria2.x",
};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld);

#endif