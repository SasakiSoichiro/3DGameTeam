//=================================================================
//
//
//
//				���@���@�ā@�ށ@���@���@�I�I
//
//
//
//==================================================================
#include "item.h"
#include "player.h"

ITEM g_item[MAX_ITEM] = {};
LPD3DXMESH g_pMeshItem[MAX_ITEM] = { NULL };				//	���_���̃|�C���^�[
LPDIRECT3DTEXTURE9 g_apTextureItem[128] = {};	//	�e�N�X�`���̃|�C���^�[
LPD3DXBUFFER g_pBufferMatItem[MAX_ITEM] = { NULL };			//	�}�e���A���̃|�C���^�[
DWORD g_dwNuMatItem[MAX_ITEM] = { 0 };						//	�}�e���A���̐�

//	����������
void InitItem(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	for (int count = 0; count < MAX_ITEM; count++)
	{
		g_item[count].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[count].bUse = false;

		//	X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\Item\\house000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBufferMatItem[count],
			NULL,
			&g_dwNuMatItem[count],
			&g_pMeshItem[count]);

		//	�e�N�X�`���̓ǂݍ���
		pMat = (D3DXMATERIAL*)g_pBufferMatItem[count]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNuMatItem; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureItem[nCntMat]);
			}
		}
	}
}

//	�I������
void UinitItem(void)
{

}

//	�X�V����
void UpdateItem(void)
{

}

//	�`�揈��
void DrawItem(void)
{

}

//	�擾����
ITEM* GetItem(void)
{
	return &g_item[0];
}