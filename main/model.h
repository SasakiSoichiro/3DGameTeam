//=============================================================================
//
//	���f������ [model.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _MODEL_H_//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"

<<<<<<< HEAD
=======
//�}�N����`
#define MAX_MODEL (128)

typedef enum
{
	MODELTYPE_0,
	MODELTYPE_1,
	MODELTYPE_2,
	MODELTYPE_MAX
}Mtype;

static const char* MODEL[MODELTYPE_MAX] =
{
	"data\\model\\house000.x",
	"data\\model\\flashlight.x",
};

>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat;//�}�e���A���̐�
	int nIdxModelParent;//�e���f���̃C���f�b�N�X
	D3DXVECTOR3 pos;//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 posFirst;//�ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rotFirst;//����
<<<<<<< HEAD
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 apTexture[128];
	D3DCOLORVALUE Diffuse, firstDiffuse;

}Model;
//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

#endif
=======
	D3DXVECTOR3 vtxMin, vtxMax;
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 apTexture[256];
	D3DCOLORVALUE Diffuse, firstDiffuse;
	bool bUse;
	int nType;

}Model;

////�v���g�^�C�v�錾
//void InitModel(void);
//void UninitModel(void);
//void UpdateModel(void);
//void DrawModel(void);
//void SetModel(D3DXVECTOR3 pos,int nType);

#endif
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
