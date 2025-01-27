//=============================================================================
//
//	�G�f�B�b�g���� [edit.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _EDIT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "player.h"
#define NUM_EDIT (64)
#define EDITTEXTURE (128)	//�e�N�X�`���̍ő吔
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"
typedef enum
{
	EDIT_HOUSE00 = 0,		//���ʂ̃u���b�N
	EDIT_HOUSE01,
	EDIT_WALL00,
	EDIT_WALL01,
	EDIT_MAX
}EDITTYPE;

typedef struct
{
	LPD3DXMESH pMesh;					//���b�V���i���_���)�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 apTexture[EDITTEXTURE];	//�e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;				//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;						//�}�e���A���̐�
}EDITTEX;

typedef struct
{
	EDITTEX tex[EDIT_MAX];				//�e�N�X�`�����
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 move;					//�ʒu
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin, vtxMax;			//���f���̍ŏ��l,�ő�l
	int nType;
	bool bUse;

}EDITINFO;

static const char* X_EDIT[EDIT_MAX] =
{
	"data\\model\\house000.x",
	"data\\model\\house01.x",
	"data\\model\\wallmaria.x",
	"data\\model\\wallmaria2.x",
};

//�v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveEdit(void);
void LoadEdit(void);
void ReloadEdit(void);
#endif