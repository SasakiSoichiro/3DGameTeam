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

//�}�N����`
#define NUM_EDIT (64)
#define EDITTEXTURE (128)	//�e�N�X�`���̍ő吔
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"

typedef enum
{
	//��1
	EDIT_HOUSE00 = 0,		//���ʂ̃u���b�N
	EDIT_HOUSE00_L,
	EDIT_HOUSE00_R,
	EDIT_HOUSE00_B,

	//��2
	EDIT_HOUSE01,
	EDIT_HOUSE01_L,
	EDIT_HOUSE01_R,
	EDIT_HOUSE01_B,

	//��3
	EDIT_HOUSE02,
	EDIT_HOUSE02_L,
	EDIT_HOUSE02_R,
	EDIT_HOUSE02_B,

	//��3
	EDIT_HOUSE03,
	EDIT_HOUSE03_L,
	EDIT_HOUSE03_R,
	EDIT_HOUSE03_B,

	//��
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
	//��1��
	"data\\model\\house.x",
	"data\\model\\house_L.x",
	"data\\model\\house_R.x",
	"data\\model\\house_B.x",

	//��2��
	"data\\model\\house000.x",
	"data\\model\\house000_L.x",
	"data\\model\\house000_r.x",
	"data\\model\\house000_b.x",

	//��3��
	"data\\model\\house01.x",
	"data\\model\\house01_L.x",
	"data\\model\\house01_R.x",
	"data\\model\\house01_B.x",

	//��4��
	"data\\model\\house04.x",
	"data\\model\\house04_L.x",
	"data\\model\\house04_R.x",
	"data\\model\\house04_B.x",


	//��
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