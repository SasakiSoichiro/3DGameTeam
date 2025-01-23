#include "meshwall.h"
#include "meshfan.h"
#include "player.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureMeshFan = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshFan = NULL;//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshFan = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MeshFan g_MeshFan;

void InitMeshFan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Fan004.png",
		&g_pTextureMeshFan);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CORNERCNT+1,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshFan,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * CORNERCNT+1,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshFan,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^


//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshFan->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPOS = 0;
	int radius = 400;
	float Vmesh = (float)(VMESH);
	float Hmesh = (float)(HMESH);
	D3DXVECTOR3 nor;
	D3DXVECTOR3 vec1, vec2; // �x�N�g��
	// �O�ς����߂�

	int nCnt = 0;
	pVtx[nCnt].pos = D3DXVECTOR3(0.0f,400.0f,0.0f);

	for (nCnt = 1; nCnt < CORNERCNT + 1; nCnt++)
	{
			float Angle = ((D3DX_PI * 2) / (CORNERCNT) * -nCnt) + D3DX_PI;
			pVtx[nCnt].pos = D3DXVECTOR3(sinf(-Angle) * radius, OBJ_V, cosf(-Angle) * radius);
			nor = pVtx[nCnt].pos - g_MeshFan.pos;
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
			pVtx[nCnt].tex = D3DXVECTOR2((1.0f / Vmesh) * nCnt, ((1.0f / Hmesh) * nCnt));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshFan->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	g_pIdxBuffMeshFan->Lock(0, 0, (void**)&pIdx, 0);


	for (nCnt = 0; nCnt < CORNERCNT + 1; nCnt++)
	{
		pIdx[nCnt] = nCnt;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshFan->Unlock();

}

void UninitMeshFan(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureMeshFan != NULL)
	{
		g_pTextureMeshFan->Release();
		g_pTextureMeshFan = NULL;
	}


	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshFan != NULL)
	{
		g_pVtxBuffMeshFan->Release();
		g_pVtxBuffMeshFan = NULL;
	}


	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshFan != NULL)
	{
		g_pIdxBuffMeshFan->Release();
		g_pIdxBuffMeshFan = NULL;
	}

}
void UpdateMeshFan(void)
{

}

void DrawMeshFan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshFan.mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshFan.rot.y, g_MeshFan.rot.x, g_MeshFan.rot.z);
	D3DXMatrixMultiply(&g_MeshFan.mtxWorld, &g_MeshFan.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshFan.pos.x, g_MeshFan.pos.y, g_MeshFan.pos.z);
	D3DXMatrixMultiply(&g_MeshFan.mtxWorld, &g_MeshFan.mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_MeshFan.mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshFan, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshFan);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshFan);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, CORNERCNT, 0, POLYCNT);
}
