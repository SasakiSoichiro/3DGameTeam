//==========================================
//
//		���f��			model.cpp
//			ryuusei hirata
//
//=========================================
#include "main.h"
#include "model.h"
#include "input.h"

//	�O���o�[��
LPD3DXMESH g_pMeshModeel = NULL;				//	���_���̃|�C���^�[
LPDIRECT3DTEXTURE9 g_apTextureModel[128] = {};	//	�e�N�X�`���̃|�C���^�[
LPD3DXBUFFER g_pBufferMatModel = NULL;			//	�}�e���A���̃|�C���^�[
DWORD g_dwNuMatModel = 0;						//	�}�e���A���̐�
D3DXVECTOR3 g_posModel;							//	�ʒu
D3DXVECTOR3 g_rotModel;							//	����
D3DXMATRIX g_mtxWoldModel;						//	���[���h�}�g���b�N�X

//========================
//		����������
//========================
void InitModel(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	g_posModel = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\model\\house000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatModel,
		NULL,
		&g_dwNuMatModel,
		&g_pMeshModeel);

	//	�e�N�X�`���̓ǂݍ���
	pMat = (D3DXMATERIAL*)g_pBufferMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNuMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}
}

//========================
//		�I������
//========================
void UninitModel(void)
{
	//	���b�V���̔j��
	if (g_pMeshModeel != NULL)
	{
		g_pMeshModeel->Release();
		g_pMeshModeel = NULL;
	}

	//	�}�e���A���̔j��
	if (g_pBufferMatModel != NULL)
	{
		g_pBufferMatModel->Release();
		g_pBufferMatModel = NULL;
	}
}

//========================
//		�X�V����
//========================
void UpdateModel(void)
{

}

//=======================
//		�`�揈��
//=======================
void DrawModel(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//	���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWoldModel);

	//	�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWoldModel, &g_mtxWoldModel, &mtxRot);

	//	�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWoldModel, &g_mtxWoldModel, &mtxTrans);

	//	���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoldModel);

	//	���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//	�}�e���A���f�[�^�ւ̃|�C���^���[���擾
	pMat = (D3DXMATERIAL*)g_pBufferMatModel->GetBufferPointer();

	//	�`��
	for (int nCntMat = 0; nCntMat < (int)g_dwNuMatModel; nCntMat++)
	{
		//	�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//	�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//	���f���̕`��
		g_pMeshModeel->DrawSubset(nCntMat);
	}

	//	�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}