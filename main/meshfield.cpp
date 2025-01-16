//===============================================================-
//
//			���b�V���t�B�[���h			meshfield.cpp
//
//				Athor : ryuuseivhirata
//
//================================================================
#include "main.h"
#include "meshfield.h"

//	�O���[�o���錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	//	���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureMeshfield = NULL;		//	�e�N�X�`���̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//	�C���f�b�N�X�̃|�C���^
MESHFIELD g_MeshField = {};

//==================
//	����������
//==================
void InitMeshfield(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_T,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//	�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\ground.png",
		&g_apTextureMeshfield);

	//	�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_I,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//	pVtx�̏�����
	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	//	���_�o�b�t�@�̃��b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_MeshField.pos = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	g_MeshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int count = 0;

	for (int nCntZ = 0; nCntZ <= MESHFIELD_Z; nCntZ++)
	{
		//	�l�ɂ�鏈������

		for (int nCntX = 0; nCntX <= MESHFIELD_X; nCntX++)
		{
			//	���_���̐ݒ�
			pVtx[count].pos.x = 50.0f * nCntX;
			pVtx[count].pos.y = 0.0f;
			pVtx[count].pos.z = -50.0f * nCntZ;

			//	�e�N�X�`��
			pVtx[count].tex.x = 0.5f * nCntX;
			pVtx[count].tex.y = 0.5f * nCntZ;

			//	�e���_�̖@���̐ݒ�
			pVtx[count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//	���_�J���[
			pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	��q
			count++;
		}
	}

	//	���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	//	�C���f�b�N�X�̃��b�N
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//	�C���f�b�N�X�̐ݒ�
	int count2 = 0;
	int count3 = 0;
	int count4 = MESHFIELD_X + 1;
	int nCntZ = 0;

	//	�C���f�b�N�X�̐ݒ�
	for (int nCntX = 0; nCntX < MESHFIELD_X; nCntX++)
	{
		for (nCntZ = 0; nCntZ <= MESHFIELD_Z; nCntZ++)
		{
			pIdx[count2] = count4;
			pIdx[count2 + 1] = count3;

			count2 += 2;
			count3++;
			count4++;
		}

		if (nCntZ <= MESHFIELD_Z)
		{
			pIdx[count2] = count3 - 1;
			pIdx[count2 + 1] = count4;
			count2 += 2;
		}
	}

	//	�C���f�b�N�X�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();
}

//==================
//	�I������
//==================
void UninitMeshfield(void)
{
	//	���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	if (g_apTextureMeshfield != NULL)
	{
		g_apTextureMeshfield->Release();
		g_apTextureMeshfield = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================
//	�X�V����
//==================
void UpdataMeshfield(void)
{

}

//==================
//	�`�揈��
//==================
void DrawMeshfield(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	�v�Z�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//	���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	//	�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxRot);

	//	�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);

	//	���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorld);

	//	���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//	�C���f�b�N�X���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//	�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureMeshfield);

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//	�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_T, 0, MESHFIELD_P);
}
