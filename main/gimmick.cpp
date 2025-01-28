//=============================================
//
// author chikada shouya
//
//=============================================

#include "gimmick.h"
#include "camera.h"
#include "Input.h"
#include "enemy.h"
#include "game.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureDoor[MAX_DOOR] = {};//�e�N�X�`���ւ̃|�C���^
BLOCK g_Door[MAX_DOOR];
bool isGoal;
bool isBill;
//bool isMove;
//================================
//����������
//================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �\���̕ϐ��̏�����
	for(int nCnt = 0;nCnt < MAX_DOOR;nCnt++)
	{
		//�e��ϐ��̏�����
		g_Door[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].dwNumMat = 0;
		g_Door[nCnt].bUse = false;
		//g_Block[nCnt1][nCnt].bGoal = false;
		//g_Block[nCnt1][nCnt].bMove = false;

		// ���f���ǂݍ���
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\door.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Door[nCnt].pBuffMat,
			NULL,
			&g_Door[nCnt].dwNumMat,
			&g_Door[nCnt].pMesh);

		isGoal = false;
		isBill = false;
		// �T�C�Y���̎擾
		int nNumVtx;	//���_��
		DWORD sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
		D3DXMATERIAL* pMat;	//�}�e���A���ւ̃|�C���^


		//���_���̎擾
		nNumVtx = g_Door[nCnt].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_Door[nCnt].pMesh->GetFVF());
		//���_�o�b�t�@�̃��b�N
		g_Door[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x > g_Door[nCnt].vtxMax.x)
			{//����X�̒l���傫��������
				g_Door[nCnt].vtxMax.x = vtx.x;
			}
			else if (vtx.x < g_Door[nCnt].vtxMin.x)
			{//����X�̒l��������������
				g_Door[nCnt].vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Door[nCnt].vtxMax.y)
			{//����Y�̒l���傫��������
				g_Door[nCnt].vtxMax.y = vtx.y;
			}
			else if (vtx.y < g_Door[nCnt].vtxMin.y)
			{//����Y�̒l��������������
				g_Door[nCnt].vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Door[nCnt].vtxMax.z)
			{//����Z�̒l���傫��������
				g_Door[nCnt].vtxMax.z = vtx.z;
			}
			else if (vtx.z < g_Door[nCnt].vtxMin.z)
			{//����Z�̒l��������������
				g_Door[nCnt].vtxMin.z = vtx.z;
			}

			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//�T�C�Y����
		g_Door[nCnt].size.x = g_Door[nCnt].vtxMax.x - g_Door[nCnt].vtxMin.x;
		g_Door[nCnt].size.y = g_Door[nCnt].vtxMax.y - g_Door[nCnt].vtxMin.y;
		g_Door[nCnt].size.z = g_Door[nCnt].vtxMax.z - g_Door[nCnt].vtxMin.z;

		//���_�o�b�t�@�̃A�����b�N
		g_Door[nCnt].pMesh->UnlockVertexBuffer();

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Door[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Door[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C�������݂���
					//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureDoor[nCntMat]);
			}
		}
		
	}
	
}
//================================
//�I������
//================================
void UninitBlock(void)
{

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		//���b�V���̔j��
		if (g_Door[nCnt].pMesh != NULL)
		{	  
			g_Door[nCnt].pMesh->Release();
			g_Door[nCnt].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (g_Door[nCnt].pBuffMat != NULL)
		{
			g_Door[nCnt].pBuffMat->Release();
			g_Door[nCnt].pBuffMat = NULL;
		}
		// �e�N�X�`���̔j��
		if (g_apTextureDoor[nCnt] != NULL)
		{			  
			g_apTextureDoor[nCnt]->Release();
			g_apTextureDoor[nCnt] = NULL;
		}
	}

}
//================================
//�X�V����
//================================
void UpdateBlock(void)
{
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();

	for (int n = 0; n < BLOCKTYPE_MAX; n++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			if (g_Block[n][nCnt].bUse == true)
			{
				//���a�̎Z�o�ϐ�
				float PRadiusPos = 50.0f;
				float BRadiusPos = 50.0f;

				//�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				//�G�ƃv���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - g_Block[4][nCnt].pos;

				//�͈͌v�Z
				float fDisX = PlayerPos.x - g_Block[4][nCnt].pos.x;
				float fDisY = PlayerPos.y - g_Block[4][nCnt].pos.y;
				float fDisZ = PlayerPos.z - g_Block[4][nCnt].pos.z;

				//��̔��a�����߂�
				float fRadX = PRadiusPos + BRadiusPos;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					isBill = true;
					if (g_Block[n][nCnt].nType == BLOCKTYPE_KEYHOLE)
					{
						if (KeyboardTrigger(DIK_F) == true)
						{
							isGoal = true;
						}
					}
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) >= (fRadX * fRadX))
				{
					isBill = false;
				}

				if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
				{
					if (g_Block[n][nCnt].move.y == 0.0f && g_Block[n][nCnt].move.y <= 10.0f)
					{
						g_Block[n][nCnt].move.y += 1.0f;
					}
					else if (g_Block[n][nCnt].move.y >= 10.0f)
					{
						g_Block[n][nCnt].move.y -= 1.0f;
					}

					g_Block[n][nCnt].rot.y += 0.15f;
					if (g_Block[n][nCnt].rot.y >= 12.5f)
					{
						g_Block[n][nCnt].rot.y = 0.0f;
					}
					/*if (g_Block[n][nCnt].rot.y <= 15.0f)
					{
						g_Block[n][nCnt].rot.y = 0.0f;
					}*/
				}
				if (g_Block[n][nCnt].nType == BLOCKTYPE_TUTORIAL)
				{

					if (pEnemy->nCounterEnemy >= 1)
					{
						g_Block[n][nCnt].bUse = false;
					}
				}

				/*if (g_Block[n][nCnt].nType == BLOCKTYPE_TUTORIAL1)
				{

					if (pEnemy->nCounterEnemy >= 2)
					{
						g_Block[n][nCnt].bUse = false;
					}
				}*/
				/*if (g_Block[n][nCnt].nType == BLOCKTYPE_1)
				{
					g_Block[n][nCnt].rot.y += 0.0314f;

					if (g_Block[n][nCnt].rot.y >= 3.14f)
					{
						g_Block[n][nCnt].rot.y = 0.0f;
					}
				}*/
			}
		}
	}
}
//================================
//�`�揈��
//================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt1 = 0; nCnt1 < BLOCKTYPE_MAX; nCnt1++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			if (g_Block[nCnt1][nCnt].bUse == true)
			{// ���g�p�������牺�̏�����ʂ��Ȃ�
							//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Block[nCnt1][nCnt].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCnt1][nCnt].rot.y, g_Block[nCnt1][nCnt].rot.x, g_Block[nCnt1][nCnt].rot.z);
				D3DXMatrixMultiply(&g_Block[nCnt1][nCnt].mtxWorld, &g_Block[nCnt1][nCnt].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Block[nCnt1][nCnt].pos.x, g_Block[nCnt1][nCnt].pos.y, g_Block[nCnt1][nCnt].pos.z);
				D3DXMatrixMultiply(&g_Block[nCnt1][nCnt].mtxWorld, &g_Block[nCnt1][nCnt].mtxWorld, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCnt1][nCnt].mtxWorld);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Block[nCnt1][nCnt].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Block[nCnt1][nCnt].dwNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

					//���f��(�p�[�c)�̕`��
					g_Block[nCnt1][nCnt].pMesh->DrawSubset(nCntMat);
				}
				//�ۑ����Ă����}�e���A�����B��
				//pDevice->SetMaterial(NULL);
				pDevice->SetMaterial(&matDef);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
			}

		}
	}
}
//================================================
//�u���b�N�̐ݒ菈��
//================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BLOCKTYPE Type)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (g_Block[Type][nCnt].bUse == false)
		{//�ǂ��g�p����Ă��Ȃ�
			//���_���W�̐ݒ�
			g_Block[Type][nCnt].pos = pos;
			g_Block[Type][nCnt].rot = rot;
			g_Block[Type][nCnt].nType = Type;
			g_Block[Type][nCnt].bUse = true;
			break;
		}

	}
}
//================================================
//�u���b�N�����蔻��
//================================================
bool CollisionBlock(void)
{
	bool bLanding = false;	//���n���Ă��邩�ǂ���

	// �v���C���[�̎擾
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();

	for (int n = 0; n < BLOCKTYPE_MAX; n++)
	{
		for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
		{
			if (g_Block[n][nCnt].bUse == true)
			{
				//================================
				//�v���C���[�̓����蔻��
				//================================
				if (pPlayer->posOld.y < (g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f)
					&& (pPlayer->posOld.y + pPlayer->size.y * 2.0f) >= (g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f))
				{
					//�O��
					if ((pPlayer->pos.x - pPlayer->size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
						&& (pPlayer->pos.x + pPlayer->size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f))
					{
						//������
						if ((pPlayer->posOld.z + pPlayer->size.z * 0.5f) <= (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f)
							&& (pPlayer->pos.z + pPlayer->size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
						{
							//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
							//bLanding = true;
							if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
							{
								isGoal = true;
							}

							else
							{
								pPlayer->pos.z = -g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f - pPlayer->size.z * 0.5f - 0.5f;

							}

						}
						//��O����
						else if ((pPlayer->posOld.z - pPlayer->size.z * 0.5f) > (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
							&& (pPlayer->pos.z - pPlayer->size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f))
						{
							//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
							//bLanding = true;
							if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
							{

								isGoal = true;
							}

							else
							{
								pPlayer->pos.z = g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f + pPlayer->size.z * 0.5f + 0.5f;

							}


						}
						//���E
						if ((pPlayer->pos.z - pPlayer->size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
							&& (pPlayer->pos.z + pPlayer->size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
						{
							//�E
							if ((pPlayer->posOld.x - pPlayer->size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
								&& (pPlayer->pos.x + pPlayer->size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f))
							{
								//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
								//bLanding = true;
								if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
								{

									isGoal = true;
								}

								else
								{
									pPlayer->pos.x = g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f - pPlayer->size.x * 0.5f + 0.5f;

								}
							}
							//��
							else if ((pPlayer->posOld.x + pPlayer->size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
								&& (pPlayer->pos.x - pPlayer->size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f))
							{
								//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
								//bLanding = true;
								if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
								{

									isGoal = true;
								}

								else
								{
									pPlayer->pos.x = g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f + pPlayer->size.x * 0.5f + 0.5f;

								}

							}

						}

					}
				}
				//�ォ��
				if ((pPlayer->pos.x - pPlayer->size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
					&& (pPlayer->pos.x + pPlayer->size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
					&& (pPlayer->pos.z - pPlayer->size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
					&& (pPlayer->pos.z + pPlayer->size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
				{
					if ((pPlayer->posOld.y > g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f)
						&& (pPlayer->pos.y < g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f))
					{


						if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
						{

							isGoal = true;
						}

						else
						{
							bLanding = true;
							pPlayer->pos.y = pPlayer->posOld.y;

						}


					}
				}
				//������
				if ((pPlayer->pos.x - pPlayer->size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
					&& (pPlayer->pos.x + pPlayer->size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
					&& (pPlayer->pos.z - pPlayer->size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
					&& (pPlayer->pos.z + pPlayer->size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
				{
					if ((pPlayer->posOld.y * 5.0f < g_Block[n][nCnt].pos.y - g_Block[n][nCnt].size.y)
						&& (pPlayer->pos.y * 5.0f > g_Block[n][nCnt].pos.y - g_Block[n][nCnt].size.y))
					{
						if (g_Block[n][nCnt].nType == BLOCKTYPE_GOAL)
						{

							isGoal = true;
						}

						else
						{
							pPlayer->pos.y = pPlayer->posOld.y;

						}
					}
				}
				//================================
				//�G�̓����蔻��
				//================================
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy[nCntEnemy].posOld.y < (g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f)
						&& (pEnemy[nCntEnemy].posOld.y + pEnemy->size.y * 0.5f) >= (g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f))
					{
						//�O��
						if ((pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
							&& (pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f))
						{
							//������
							if ((pEnemy[nCntEnemy].posOld.z + pEnemy[nCntEnemy].size.z * 0.5f) <= (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f)
								&& (pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
							{
								//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
								//bLanding = true;
								pEnemy[nCntEnemy].pos.z = -g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f - pEnemy->size.z * 0.5f - 0.5f;
								//pPlayer->move.z = 0.0f;

							}
							//��O����
							else if ((pEnemy[nCntEnemy].posOld.z - pEnemy[nCntEnemy].size.z * 0.5f) > (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
								&& (pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f))
							{
								//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
								//bLanding = true;
								pEnemy[nCntEnemy].pos.z = g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f + pEnemy->size.z * 0.5f + 0.5f;
								//pPlayer->move.z = 0.0f;

							}
							//���E
							if ((pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
								&& (pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
							{
								//�E
								if ((pEnemy[nCntEnemy].posOld.x - pEnemy[nCntEnemy].size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
									&& (pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f))
								{
									//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
									//bLanding = true;
									pEnemy[nCntEnemy].pos.x = g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f - pEnemy->size.x * 0.5f + 0.5f;
									//pPlayer->move.x = 0.0f;
								}
								//��
								else if ((pEnemy[nCntEnemy].posOld.x + pEnemy[nCntEnemy].size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
									&& (pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f))
								{
									//�g�p���Ă���u���b�N���ׂĂ��`�F�b�N����
									//bLanding = true;
									pEnemy[nCntEnemy].pos.x = g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f + pEnemy->size.x * 0.5f + 0.5f; /*g_Block.pos.x -g_Block.vtxMax.x * 1.0f - pPlayer->vtxMax.x * 1.0f;*/


								}

							}

						}
					}
					//�ォ��
					if ((pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
						&& (pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
						&& (pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
						&& (pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
					{
						if ((pEnemy[nCntEnemy].posOld.y > g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f)
							&& (pEnemy[nCntEnemy].pos.y < g_Block[n][nCnt].pos.y + g_Block[n][nCnt].size.y * 0.5f))
						{
							bLanding = true;
							pEnemy[nCntEnemy].pos.y = pEnemy[nCntEnemy].posOld.y;


						}
					}
					//������
					if ((pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].size.x * 0.5f) < (g_Block[n][nCnt].pos.x + g_Block[n][nCnt].size.x * 0.5f)
						&& (pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].size.x * 0.5f) > (g_Block[n][nCnt].pos.x - g_Block[n][nCnt].size.x * 0.5f)
						&& (pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].size.z * 0.5f) < (g_Block[n][nCnt].pos.z + g_Block[n][nCnt].size.z * 0.5f)
						&& (pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].size.z * 0.5f) > (g_Block[n][nCnt].pos.z - g_Block[n][nCnt].size.z * 0.5f))
					{
						if ((pEnemy[nCntEnemy].posOld.y < g_Block[n][nCnt].pos.y - g_Block[n][nCnt].size.y)
							&& (pEnemy[nCntEnemy].pos.y > g_Block[n][nCnt].pos.y - g_Block[n][nCnt].size.y))
						{
							pEnemy[nCntEnemy].pos.y = pEnemy[nCntEnemy].posOld.y;
						}
					}
				}
			}
		}
	}
	return bLanding;
}
BLOCK* GetBlock(void)
{
	return &g_Block[0][0];
}

bool IsGoal()
{
	return isGoal;
}
bool IsBill()
{
	return isBill;
}