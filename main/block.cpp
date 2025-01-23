#include "block.h"
//�O���[�o���ϐ��錾
BLOCK g_Block[BLOCK_MAX][NUM_BLOCK];
BoolPressurePlate g_bPlate;
//����������
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_bPlate.red = true;
	g_bPlate.blue = false;
	g_bPlate.green = false;

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			//�e��ϐ��̏�����
			g_Block[i][nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[i][nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[i][nCnt].nType = BLOCK_NORMAL;
			g_Block[i][nCnt].bUse = false;
		}

	}
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			//x�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(X_BLOCK[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Block[i][nCnt].pBuffMat,
				NULL,
				&g_Block[i][nCnt].dwNumMat,
				&g_Block[i][nCnt].pMesh);

		}

	}

	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			nNumVtx = g_Block[i][nCnt].pMesh->GetNumVertices();
			sizeFVF = D3DXGetFVFVertexSize(g_Block[i][nCnt].pMesh->GetFVF());
			//���_�o�b�t�@�̃��b�N
			g_Block[i][nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
			
			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
				//X============================
				if (vtx.x > g_Block[i][nCnt].vtxMax.x)
				{
					g_Block[i][nCnt].vtxMax.x = vtx.x;
				}

				if (vtx.x < g_Block[i][nCnt].vtxMin.x)
				{
					g_Block[i][nCnt].vtxMin.x = vtx.x;
				}
				//Y============================
				if (vtx.y > g_Block[i][nCnt].vtxMax.y)
				{
					g_Block[i][nCnt].vtxMax.y = vtx.y;
				}

				if (vtx.y < g_Block[i][nCnt].vtxMin.y)
				{
					g_Block[i][nCnt].vtxMin.y = vtx.y;
				}
				//Z=============================
				if (vtx.z > g_Block[i][nCnt].vtxMax.z)
				{
					g_Block[i][nCnt].vtxMax.z = vtx.z;
				}

				if (vtx.z < g_Block[i][nCnt].vtxMin.z)
				{
					g_Block[i][nCnt].vtxMin.z = vtx.z;
				}

				//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}
			//���_�o�b�t�@�̃A�����b�N
			g_Block[i][nCnt].pMesh->UnlockVertexBuffer();

			D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Block[i][nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Block[i][nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`���t�@�C�������݂���
						//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Block[i][nCnt].apTexture[nCntMat]);
				}
			}

		}

	}
}
void UninitBlock(void)
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{

		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			if (g_Block[i][nCnt].pMesh != NULL)
			{
				g_Block[i][nCnt].pMesh->Release();
				g_Block[i][nCnt].pMesh = NULL;

			}
			//���_�o�b�t�@�̉��
			if (g_Block[i][nCnt].pBuffMat != NULL)
			{
				g_Block[i][nCnt].pBuffMat->Release();
				g_Block[i][nCnt].pBuffMat = NULL;
			}

		}
	}
}
void UpdateBlock(void)
{

}
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���̕ۑ��p
	D3DMATERIAL9 matDef;//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
	for (int i = 0; i < BLOCK_MAX; i++)
	{

		for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
		{
			if (g_Block[i][nCntBlock].bUse == true)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Block[i][nCntBlock].mtxWorld);
				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[i][nCntBlock].rot.y, g_Block[i][nCntBlock].rot.x, g_Block[i][nCntBlock].rot.z);
				D3DXMatrixMultiply(&g_Block[i][nCntBlock].mtxWorld, &g_Block[i][nCntBlock].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Block[i][nCntBlock].pos.x, g_Block[i][nCntBlock].pos.y, g_Block[i][nCntBlock].pos.z);
				D3DXMatrixMultiply(&g_Block[i][nCntBlock].mtxWorld, &g_Block[i][nCntBlock].mtxWorld, &mtxTrans);

				pDevice->SetTransform(D3DTS_WORLD, &g_Block[i][nCntBlock].mtxWorld);

				pDevice->GetMaterial(&matDef);
				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Block[i][nCntBlock].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Block[i][nCntBlock].dwNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_Block[i][nCntBlock].apTexture[nCntMat]);

					//���f���i�p�[�c�j�̕`��
					g_Block[i][nCntBlock].pMesh->DrawSubset(nCntMat);
				}
				pDevice->SetMaterial(&matDef);

			}

		}

	}
}


void SetBlock(D3DXVECTOR3 pos,int nType)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		if (g_Block[nType][nCnt].bUse == false)
		{
			g_Block[nType][nCnt].pos = pos;
			g_Block[nType][nCnt].nType = nType;
			g_Block[nType][nCnt].bUse = true;
			break;
		}
	}
}
void CollisionBlock(D3DXVECTOR3* pPos,		//���݂̈ʒu
					D3DXVECTOR3* pPosOld)	//�O��̈ʒu
{					
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3* posOld = pPosOld;		//�O�t���[���̃v���C���[�̈ʒu
	D3DXVECTOR3* pos = pPos;			//���t���[���̃v���C���[�̈ʒu



	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			if (g_Block[i][nCnt].bUse == true)
			{
				//���E��O���̂߂荞�ݔ���
				if (pos->y< g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y)
				{
					//���E�̂߂荞�ݔ���
					if (pos->z - OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z)//�v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
					{

						if (posOld->x + OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)//�w��������E�ɂ߂荞��
						{
							//pPlayer->pos�����f���̍����ɂ�������
							pos->x = g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x - OBJ_P - 0.1f;

							GimmickBlock(i);

						}
						if (posOld->x - OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x - OBJ_P < g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x)//�w��������E�ɂ߂荞��
						{
							//pPlayer->pos�����f���̉E���ɂ�������
							pos->x = g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x + OBJ_P + 0.1f;
							GimmickBlock(i);
						}
					}

					//��O���̂߂荞�ݔ���
					if (pos->x - OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)//�v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
					{

						if (posOld->z + OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z)//Z���������ɂ߂荞��
						{
							//pPlayer->pos�����f���̎�O���ɂ�������
							pos->z = g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z - OBJ_P - 0.1f;
							GimmickBlock(i);
						}
						if (posOld->z - OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z - OBJ_P < g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z)//Z���ォ�牺�ɂ߂荞��
						{
							//pPlayer->pos�����f���̉����ɂ�������
							pos->z = g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z + OBJ_P + 0.1f;
							GimmickBlock(i);
						}
					}

				}
				if (pos->z - OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z
					&& pos->x - OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)
				{
					if (posOld->y + (OBJ_P * 2.0f) < g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y)//�w��������E�ɂ߂荞��
					{
						//pPlayer->pos�����f���̉����ɂ�������
						pos->y = g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
						GimmickBlock(i);
					}
					if (posOld->y > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y && pos->y < g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y)//�w��������E�ɂ߂荞��
					{
						//pPlayer->pos�����f���̏㑤�ɂ�������
						pos->y = g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y + 0.1f;
						GimmickBlock(i);
					}

				}

			}

		}

	}


}

void GimmickBlock(int nType)
{
	int Type = nType;
	switch(Type)
	{
	case BLOCK_PRESSUREPLATERED:
		g_bPlate.red = true;
		g_bPlate.blue = false;
		g_bPlate.green = false;

		break;
	case BLOCK_PRESSUREPLATEBLUE:
		g_bPlate.red = false;
		g_bPlate.blue = true;
		g_bPlate.green = false;
		break;
	case BLOCK_PRESSUREPLATEGREEN:
		g_bPlate.red = false;
		g_bPlate.blue = false;
		g_bPlate.green = true;
		break;
	default:
		break;
	}
}

BoolPressurePlate GetPlate(void)
{
	return g_bPlate;
}
