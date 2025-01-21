//==========================================
//
//		�v���C���[		Player.cpp
//			ryuusei hirata
//
//=========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//	�O���o�[��
Player g_player = {};

static KEY_INFO g_aKeyNeutral[] =
{
	//	�L�[1
	{40,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.69f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -0.66f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f}}},

	//	�L�[2
	{40,
	{{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.69f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, -0.66f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f}}}
};

static KEY_INFO g_aKeyMove[] =
{
	//	�L�[1
	{10,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.69f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.94f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.75f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.03f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.75f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.13f, 0.0f, 0.0f}}},

	//	�L�[2
	{10,
	{{0.0f, 0.0f, 0.0f,
	-0.25f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.09f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.75f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	1.07f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.82f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.28f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	-0.85f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.44f, 0.0f, 0.0f}}},

	//	�L�[3
	{10,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.75f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.79f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.82f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.03f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	0.69f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.13f, 0.0f, 0.0f}}},

	//	�L�[4
	{10,
	{{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.09f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	1.01f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.85f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-1.01f, -0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.79f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.25f, 0.0f, 0.0f}}},
};

//========================
//		����������
//========================
void InitPlayer(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.moverot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.MotionType = MOTIONTYPE_NEUTRAL;
	//g_player.nextKey = 1;
	//g_player.nKey = 0;
	//g_player.bLoopMotion = false;
	//g_player.nCntMotion = 0;

	//g_player.aMotionInfo[0].aKeyinfo[0] = g_aKeyNeutral[0];
	//g_player.aMotionInfo[0].aKeyinfo[1] = g_aKeyNeutral[1];

	//g_player.aMotionInfo[1].aKeyinfo[0] = g_aKeyMove[0];
	//g_player.aMotionInfo[1].aKeyinfo[1] = g_aKeyMove[1];
	//g_player.aMotionInfo[1].aKeyinfo[2] = g_aKeyMove[2];
	//g_player.aMotionInfo[1].aKeyinfo[3] = g_aKeyMove[3];

	////	X�t�@�C���̓ǂݍ���
	//D3DXLoadMeshFromX("data\\model\\player2\\00_body.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[0].pBuffMat,
	//	NULL,
	//	&g_player.aModel[0].dwNumMat,
	//	&g_player.aModel[0].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\01_head.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[1].pBuffMat,
	//	NULL,
	//	&g_player.aModel[1].dwNumMat,
	//	&g_player.aModel[1].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\02_armR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_player.aModel[2].dwNumMat,
	//	&g_player.aModel[2].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\03_handR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[3].pBuffMat,
	//	NULL,
	//	&g_player.aModel[3].dwNumMat,
	//	&g_player.aModel[3].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\04_armL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[4].pBuffMat,
	//	NULL,
	//	&g_player.aModel[4].dwNumMat,
	//	&g_player.aModel[4].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\05_handL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[5].pBuffMat,
	//	NULL,
	//	&g_player.aModel[5].dwNumMat,
	//	&g_player.aModel[5].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\06_legR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[6].pBuffMat,
	//	NULL,
	//	&g_player.aModel[6].dwNumMat,
	//	&g_player.aModel[6].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\07_footR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[7].pBuffMat,
	//	NULL,
	//	&g_player.aModel[7].dwNumMat,
	//	&g_player.aModel[7].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\08_legL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[8].pBuffMat,
	//	NULL,
	//	&g_player.aModel[8].dwNumMat,
	//	&g_player.aModel[8].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\09_footL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[9].pBuffMat,
	//	NULL,
	//	&g_player.aModel[9].dwNumMat,
	//	&g_player.aModel[9].pMesh);

	//g_player.nNumModel = 10;
	//g_player.nNumKey = 10;
	//g_player.nNumMotion = 10;

	////	�K�w�\���̐ݒ�
	////	��
	//g_player.aModel[0].nIdxModelParent = -1;
	//g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
	//g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	��
	//g_player.aModel[1].nIdxModelParent = 0;
	//g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 13.0f, 0.0f);
	//g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	�E�r
	//g_player.aModel[2].nIdxModelParent = 0;
	//g_player.aModel[2].pos = D3DXVECTOR3(-5.0f, 12.0f, 0.0f);
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	�E��
	//g_player.aModel[3].nIdxModelParent = 2;
	//g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	//g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	���r
	//g_player.aModel[4].nIdxModelParent = 0;
	//g_player.aModel[4].pos = D3DXVECTOR3(5.0f, 12.0f, 0.0f);
	//g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	����
	//g_player.aModel[5].nIdxModelParent = 4;
	//g_player.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	//g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	�E��
	//g_player.aModel[6].nIdxModelParent = 0;
	//g_player.aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);
	//g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	�E��
	//g_player.aModel[7].nIdxModelParent = 6;
	//g_player.aModel[7].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	����
	//g_player.aModel[8].nIdxModelParent = 0;
	//g_player.aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	//g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	����
	//g_player.aModel[9].nIdxModelParent = 8;
	//g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int nNumvtx;		//	���_��
	DWORD sizeFVF;		//	���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;		//	���_�o�b�t�@�ւ̃|�C���^

	//	���_���̎擾
	//nNumvtx = g_player.aModel->pMesh->GetNumVertices();

	//	���_�t�H�[�}�b�g�̃T�C�Y�擾
	//sizeFVF = D3DXGetFVFVertexSize(g_player.aModel->pMesh->GetFVF());

	//	���_�o�b�t�@�̃��b�N
	//g_player.aModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumvtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	//	��r	X
	//	if (vtx.x > g_player.vtxMax.x)
	//	{
	//		g_player.vtxMax.x = vtx.x;
	//	}
	//	else if (vtx.x < g_player.vtxMin.x)
	//	{
	//		g_player.vtxMin.x = vtx.x;
	//	}

	//	//	��r	Y
	//	if (vtx.y > g_player.vtxMax.y)
	//	{
	//		g_player.vtxMax.y = vtx.y;
	//	}
	//	else if (vtx.y < g_player.vtxMin.y)
	//	{
	//		g_player.vtxMin.y = vtx.y;
	//	}

	//	//	��r	Z
	//	if (vtx.z > g_player.vtxMax.z)
	//	{
	//		g_player.vtxMax.z = vtx.z;
	//	}
	//	else if (vtx.z < g_player.vtxMin.z)
	//	{
	//		g_player.vtxMin.z = vtx.z;
	//	}

	//	//	���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	//	pVtxBuff += sizeFVF;
	//}

	//g_player.vtxMax.z = (float)((int)g_player.vtxMax.z / 1);
	//g_player.vtxMin.z = (float)((int)g_player.vtxMin.z / 1);

	//	�A�����b�N
	//g_player.aModel->pMesh->UnlockVertexBuffer();

	//for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//{
	//	//	�e�N�X�`���̓ǂݍ���
	//	pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
	//	{
	//		if (pMat[nCntMat].pTextureFilename != NULL)
	//		{
	//			D3DXCreateTextureFromFile(pDevice,
	//				pMat[nCntMat].pTextureFilename,
	//				&g_player.aModel[nCntModel].apTexture[nCntMat]);
	//		}
	//	}
	//}
}

//========================
//		�I������
//========================
void UninitPlayer(void)
{
	//	���b�V���̔j��
	//for (int count = 0; count < g_player.nNumModel; count++)
	//{
	//	if (g_player.aModel[count].pMesh != NULL)
	//	{
	//		g_player.aModel[count].pMesh->Release();
	//		g_player.aModel[count].pMesh = NULL;
	//	}

	//	//	�}�e���A���̔j��
	//	if (g_player.aModel[count].pBuffMat != NULL)
	//	{
	//		g_player.aModel[count].pBuffMat->Release();
	//		g_player.aModel[count].pBuffMat = NULL;
	//	}
	//}
}

//========================
//		�X�V����
//========================
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();
	float diff = 0.0f;
	//g_player.Oldpos = g_player.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * 4.0f;
		g_player.move.z += cosf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y) * 4.0f;
		g_player.move.z -= cosf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = 0.0f;
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x -= cosf(pCamera->rot.y) * 4.0f;
		g_player.move.z += sinf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_player.move.x += cosf(pCamera->rot.y) * 4.0f;
		g_player.move.z -= sinf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = -D3DX_PI * 0.5f;
	}

	//	�p�x�̐��K��
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y - D3DX_PI;
		g_player.rot.y = -D3DX_PI - g_player.rot.y;

	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y + D3DX_PI;
		g_player.rot.y = D3DX_PI + g_player.rot.y;
	}

	diff = g_player.rotDest.y - g_player.rot.y;

	if (diff > D3DX_PI)
	{
		diff = diff - D3DX_PI * 2.0f;
	}
	else if (diff < -D3DX_PI)
	{
		diff = diff + D3DX_PI * 2.0f;
	}

	g_player.rot.y += diff * 0.2f;


	//UpdateMotion(1);

	g_player.move = g_player.move * 0.6f;
	g_player.pos += g_player.move;

}

//=======================
//		�`�揈��
//=======================
void DrawPlayer(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//	���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_player.mtxWold);

	//	�������f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	//D3DXMatrixMultiply(&g_player.mtxWold, &g_player.mtxWold, &mtxRot);

	//	�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	//D3DXMatrixMultiply(&g_player.mtxWold, &g_player.mtxWold, &mtxTrans);

	//	���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWold);

	//	���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//{
	//	D3DXMATRIX mtxRotModel, mtxTransModel;	//	�v�Z�p
	//	D3DXMATRIX mtxParent;	//	�e�̃}�g���b�N�X

	//	//	�p�[�c�̏�����
	//	D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

	//	//	�������f
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

	//	//	�ʒu�̔��f
	//	D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

	//	//	�e�̃p�[�c�ݒ�
	//	if (g_player.aModel[nCntModel].nIdxModelParent != -1)
	//	{
	//		mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
	//	}
	//	else
	//	{
	//		mtxParent = g_player.mtxWold;
	//	}

	//	//	�Z�o�����}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
	//		&g_player.aModel[nCntModel].mtxWorld,
	//		&mtxParent);

	//	//	�p�[�c�̃}�g���b�N�X�̐ݒ�
	//	pDevice->SetTransform(D3DTS_WORLD,
	//		&g_player.aModel[nCntModel].mtxWorld);

	//	//	�}�e���A���f�[�^�ւ̃|�C���^���擾
	//	pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
	//	{
	//		//	�}�e���A���̐ݒ�
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//		//	�e�N�X�`���̐ݒ�
	//		pDevice->SetTexture(0, g_player.aModel[nCntModel].apTexture[nCntMat]);

	//		//	���f���̕`��
	//		g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
	//	}
	//}

	//	�ۑ������}�e���A����߂�		
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer(void)
{
	return &g_player;
}

//	���[�V����
void UpdateMotion(int count)
{
	KEY sabun;
	KEY motomeru;

	//for (int nCnt1 = 0; nCnt1 < 10; nCnt1++)
	//{
	//	sabun.fposx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposx - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposx;
	//	sabun.fposy = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposy - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposy;
	//	sabun.fposz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposz - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposz;

	//	sabun.frotx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotx - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].frotx;
	//	sabun.froty = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].froty - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].froty;
	//	sabun.frotz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotz - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].frotz;

	//	//motomeru.fposx = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposx + sabun.fposx * (float)(g_player.nCntMotion / 120.0f);
	//	//motomeru.fposy = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposy + sabun.fposy * (float)(g_player.nCntMotion / 120.0f);
	//	//motomeru.fposz = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposz + sabun.fposz * (float)(g_player.nCntMotion / 120.0f);

	//	motomeru.frotx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotx + sabun.frotx * ((float)(g_player.nCntMotion / 20.0f));
	//	motomeru.froty = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].froty + sabun.froty * ((float)(g_player.nCntMotion / 20.0f));
	//	motomeru.frotz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotz + sabun.frotz * ((float)(g_player.nCntMotion / 20.0f));

	//	//g_player.aModel[nCnt1].pos.x = motomeru.fposx;
	//	//g_player.aModel[nCnt1].pos.y = motomeru.fposy;
	//	//g_player.aModel[nCnt1].pos.z = motomeru.fposz;

	//	g_player.aModel[nCnt1].rot.x = motomeru.frotx;
	//	g_player.aModel[nCnt1].rot.y = motomeru.froty;
	//	g_player.aModel[nCnt1].rot.z = motomeru.frotz;
	//}

	//g_player.nCntMotion++;

	//if (g_player.nCntMotion >= 20)
	//{
	//	g_player.nCntMotion = 0;
	//	g_player.nextKey++;
	//	g_player.nKey++;

	//	if (g_player.nextKey >= 4)
	//	{
	//		g_player.nextKey = 0;
	//	}

	//	if (g_player.nKey >= 4)
	//	{
	//		g_player.nKey = 0;
	//	}
	//}
}