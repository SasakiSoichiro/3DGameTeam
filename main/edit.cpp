
//#include "edit.h"
////�O���[�o���ϐ��錾
//EDITINFO g_Edit[NUM_BLOCK];
//EDITTEX g_EditTex[EDIT_MAX];
////����������
//void InitBlock(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	pDevice = GetDevice();
//
//
//	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//	{
//		//�e��ϐ��̏�����
//		g_Edit[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Edit[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Edit[nCnt].nType = BLOCK_HOUSE00;
//		g_Edit[nCnt].bUse = false;
//	}
//
//
//	for (int nCnt = 0; nCnt <EDIT_MAX; nCnt++)
//	{
//		//x�t�@�C���̓ǂݍ���
//		D3DXLoadMeshFromX(X_EDIT[nCnt],
//			D3DXMESH_SYSTEMMEM,
//			pDevice,
//			NULL,
//			&g_EditTex[nCnt].pBuffMat,
//			NULL,
//			&g_EditTex[nCnt].dwNumMat,
//			&g_EditTex[nCnt].pMesh);
//	}
//
//	//�}�e���A���̎擾
//	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
//	{
//
//			D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^
//
//			//�}�e���A���f�[�^�ւ̃|�C���^���擾
//			pMat = (D3DXMATERIAL*)g_EditTex[nCnt].pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_EditTex[nCnt].dwNumMat; nCntMat++)
//			{
//				if (pMat[nCntMat].pTextureFilename != NULL)
//				{//�e�N�X�`���t�@�C�������݂���
//						//�e�N�X�`���̓ǂݍ���
//					D3DXCreateTextureFromFile(pDevice,
//						pMat[nCntMat].pTextureFilename,
//						&g_EditTex[nCnt].apTexture[nCntMat]);
//				}
//			}
//
//	}
//}
//void UninitBlock(void)
//{
//	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
//	{
//
//		for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
//		{
//			if (g_EditTex[nCntTex].apTexture[nCntTexture] != NULL)
//			{
//				g_EditTex[nCntTex].apTexture[nCntTexture]->Release();
//				g_EditTex[nCntTex].apTexture[nCntTexture] = NULL;
//
//			}
//		}
//		if (g_EditTex[nCntTex].pMesh != NULL)
//		{
//			g_EditTex[nCntTex].pMesh->Release();
//			g_EditTex[nCntTex].pMesh = NULL;
//
//		}
//		//���_�o�b�t�@�̉��
//		if (g_EditTex[nCntTex].pBuffMat != NULL)
//		{
//			g_EditTex[nCntTex].pBuffMat->Release();
//			g_EditTex[nCntTex].pBuffMat = NULL;
//		}
//
//	}
//	for (int nCntEdit = 0; nCntEdit < NUM_EDIT; nCntEdit++)
//	{
//		for (int nCntType = 0; nCntType < EDIT_MAX; nCntType++)
//		{
//			for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
//			{
//				if (g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] != NULL)
//				{
//					g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] = NULL;
//
//				}
//			}
//
//			if (g_Edit[nCntEdit].tex[nCntType].pMesh != NULL)
//			{
//				g_Edit[nCntEdit].tex[nCntType].pMesh = NULL;
//
//			}
//			//���_�o�b�t�@�̉��
//			if (g_Edit[nCntEdit].tex[nCntType].pBuffMat != NULL)
//			{
//				g_Edit[nCntEdit].tex[nCntType].pBuffMat = NULL;
//			}
//
//		}
//	}
//
//
//
//
//}
//void UpdateBlock(void)
//{
//
//}
//void DrawBlock(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	//�v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxRot, mtxTrans;
//	//���݂̃}�e���A���̕ۑ��p
//	D3DMATERIAL9 matDef;//���݂̃}�e���A���̕ۑ��p
//	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
//
//
//	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
//	{
//		if (g_Edit[i][nCntBlock].bUse == true)
//		{
//			//���[���h�}�g���b�N�X�̏�����
//			D3DXMatrixIdentity(&g_Edit[i][nCntBlock].mtxWorld);
//			//�����𔽉f
//			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Edit[i][nCntBlock].rot.y, g_Edit[i][nCntBlock].rot.x, g_Edit[i][nCntBlock].rot.z);
//			D3DXMatrixMultiply(&g_Edit[i][nCntBlock].mtxWorld, &g_Edit[i][nCntBlock].mtxWorld, &mtxRot);
//
//			//�ʒu�𔽉f
//			D3DXMatrixTranslation(&mtxTrans, g_Edit[i][nCntBlock].pos.x, g_Edit[i][nCntBlock].pos.y, g_Edit[i][nCntBlock].pos.z);
//			D3DXMatrixMultiply(&g_Edit[i][nCntBlock].mtxWorld, &g_Edit[i][nCntBlock].mtxWorld, &mtxTrans);
//
//			pDevice->SetTransform(D3DTS_WORLD, &g_Edit[i][nCntBlock].mtxWorld);
//
//			pDevice->GetMaterial(&matDef);
//			//�}�e���A���f�[�^�ւ̃|�C���^���擾
//			pMat = (D3DXMATERIAL*)g_Edit[i][nCntBlock].pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_Edit[i][nCntBlock].dwNumMat; nCntMat++)
//			{
//				//�}�e���A���̐ݒ�
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//�e�N�X�`���̐ݒ�
//				pDevice->SetTexture(0, g_Edit[i][nCntBlock].apTexture[nCntMat]);
//
//				//���f���i�p�[�c�j�̕`��
//				g_Edit[i][nCntBlock].pMesh->DrawSubset(nCntMat);
//			}
//			pDevice->SetMaterial(&matDef);
//
//		}
//
//	}
//
//}
//
//
//void SetBlock(D3DXVECTOR3 pos, int nType)
//{
//	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//	{
//		if (g_Edit[nType][nCnt].bUse == false)
//		{
//			g_Edit[nType][nCnt].pos = pos;
//			g_Edit[nType][nCnt].nType = nType;
//			g_Edit[nType][nCnt].bUse = true;
//			break;
//		}
//	}
//}
//void CollisionBlock(D3DXVECTOR3* pPos,		//���݂̈ʒu
//	D3DXVECTOR3* pPosOld)	//�O��̈ʒu
//{
//	Player* pPlayer = GetPlayer();
//	D3DXVECTOR3* posOld = pPosOld;		//�O�t���[���̃v���C���[�̈ʒu
//	D3DXVECTOR3* pos = pPos;			//���t���[���̃v���C���[�̈ʒu
//
//
//
//	for (int i = 0; i < BLOCK_MAX; i++)
//	{
//		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//		{
//			if (g_Edit[i][nCnt].bUse == true)
//			{
//				//���E��O���̂߂荞�ݔ���
//				if (pos->y< g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y)
//				{
//					//���E�̂߂荞�ݔ���
//					if (pos->z - OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z)//�v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
//					{
//
//						if (posOld->x + OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)//�w��������E�ɂ߂荞��
//						{
//							//pPlayer->pos�����f���̍����ɂ�������
//							pos->x = g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x - OBJ_P - 0.1f;
//
//						}
//						if (posOld->x - OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x - OBJ_P < g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x)//�w��������E�ɂ߂荞��
//						{
//							//pPlayer->pos�����f���̉E���ɂ�������
//							pos->x = g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x + OBJ_P + 0.1f;
//						}
//					}
//
//					//��O���̂߂荞�ݔ���
//					if (pos->x - OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)//�v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
//					{
//
//						if (posOld->z + OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z)//Z���������ɂ߂荞��
//						{
//							//pPlayer->pos�����f���̎�O���ɂ�������
//							pos->z = g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z - OBJ_P - 0.1f;
//						}
//						if (posOld->z - OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z - OBJ_P < g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z)//Z���ォ�牺�ɂ߂荞��
//						{
//							//pPlayer->pos�����f���̉����ɂ�������
//							pos->z = g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z + OBJ_P + 0.1f;
//						}
//					}
//
//				}
//				if (pos->z - OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z
//					&& pos->x - OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)
//				{
//					if (posOld->y + (OBJ_P * 2.0f) < g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y)//�w��������E�ɂ߂荞��
//					{
//						//pPlayer->pos�����f���̉����ɂ�������
//						pos->y = g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
//					}
//					if (posOld->y > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y && pos->y < g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y)//�w��������E�ɂ߂荞��
//					{
//						//pPlayer->pos�����f���̏㑤�ɂ�������
//						pos->y = g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y + 0.1f;
//					}
//
//				}
//
//			}
//
//		}
//
//	}
//
//
//}
