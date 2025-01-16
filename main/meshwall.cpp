//=============================================================
//
//			��			meshwall.cpp
//
//		Athor : ryuusei hirata
//
//==============================================================
#include "main.h"
#include "meshwall.h"

//	�O���[�o��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	//	���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;		//	�e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	//	�C���f�b�N�X�̃|�C���^
MESHWALL g_MeshWall = {};

//---------------
//	����������	
//---------------
void InitMeshWall(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHWALL_T,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//	�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\ground02.png",
		&g_apTextureMeshWall);

	//	�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHWALL_I,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	//	pVtx�̏�����
	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	//	���_�o�b�t�@�̃��b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int count = 0;
	float radius = 200.0f;
	D3DXVECTOR3 unti;

	for (int nCntZ = 0; nCntZ <= SUITYOKU; nCntZ++)
	{
		//	�l�ɂ�鏈������

		for (int nCntX = 0; nCntX <= SUIHEI; nCntX++)
		{
			//	�p�x
			float Angle = D3DX_PI * 2.0f / (float)SUIHEI * -1.0f;

			//	���W
			pVtx[count].pos = D3DXVECTOR3(sinf(Angle * nCntX) * radius,
											nCntZ * 100.0f,
											cosf(Angle * nCntX) * radius);

			//	�@��
			unti = pVtx[count].pos - g_MeshWall.pos;
			D3DXVec3Normalize(&pVtx[count].nor, &unti);

			//	�J���[
			pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	�e�N�X�`��
			pVtx[count].tex.x = 0.125f * nCntX;
			pVtx[count].tex.y = 0.125f * nCntZ;

			//	��q
			count++;
		}
	}

	//	���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshWall->Unlock();

	//	�C���f�b�N�X�̃��b�N
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//	�C���f�b�N�X�̐ݒ�
	int count2 = 0;
	int count3 = 0;
	int count4 = SUIHEI + 1;

	//	�C���f�b�N�X�̐ݒ�
	for (int nCntX = 0; nCntX < SUITYOKU; nCntX++)
	{
		for (int nCntZ = 0; nCntZ <= SUIHEI; nCntZ++)
		{
			pIdx[count2] = count4;
			pIdx[count2 + 1] = count3;

			count2 += 2;
			count3++;
			count4++;
		}

		pIdx[count2] = count3 - 1;
		pIdx[count2 + 1] = count4;
		count2 += 2;
	}

	//	�C���f�b�N�X�̃A�����b�N
	g_pIdxBuffMeshWall->Unlock();

}

//---------------
//	�I������	
//---------------
void UninitMeshWall(void)
{
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//---------------
//	�X�V����	
//---------------
void UpdataMeshWall(void)
{

}

//---------------
//	�`�揈��	
//---------------
void DrawMeshWall(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	�v�Z�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//	���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshWall.mtxWorld);

	//	�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxRot);

	//	�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxTrans);

	//	���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorld);

	//	���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//	�C���f�b�N�X���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//	�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureMeshWall);

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//	�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHWALL_T, 0, MESHWALL_P);
}