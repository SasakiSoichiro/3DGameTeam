//======================================================
//
//				���C�g	light.cpp
//					ryuusei hirata
//
//======================================================
#include "light.h"
#include "main.h"

//	�O���[�o��
D3DLIGHT9 g_light[MAX_LIGHT] = {};	//	���C�g���

void InitLighr(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//	���C�g���N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9) * MAX_LIGHT);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//	���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//	���C�g�̊g�U��
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

		//	���C�g�̕���
		vecDir[0] = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(0.3f, -0.8f, 0.4f);
		vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

		//	���K������
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//	���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//	���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void UninitLight(void)
{

}

void UpdateLight(void)
{

}