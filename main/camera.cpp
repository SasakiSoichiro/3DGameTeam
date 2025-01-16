//========================================================
//
//			�J����	camera.cpp
//				ryuusei hirata
//
//========================================================
#include "main.h"
#include "camera.h"
#include "input.h"

//	�O���[�o��
Camera g_camera = {};	//�J�������

//====================
//	����������
//====================
void InitCamera(void)
{
	//	���_�E�����_�E�������ݒ肷��
	g_camera.posV = D3DXVECTOR3(0.0f, 150.0f, -400.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x) + (g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));
}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{

	//================================
	//		�����_�̐���
	//================================
	if (GetKeyboardPress(DIK_Q) == true)
	{
		//	��]��
		g_camera.rot.y -= 0.05f;

		//	�p�x�̐��K��
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{
		//	��]��
		g_camera.rot.y += 0.05f;

		//	�p�x�̐��K��
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	////================================
	////		���_�̐���
	////================================
	if (GetKeyboardPress(DIK_Z) == true)
	{
		//	��]��
		g_camera.rot.y += 0.05f;

		//	�p�x�̐��K��
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{
		//	��]��
		g_camera.rot.y -= 0.05f;

		//	�p�x�̐��K��
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
}

void SetCamera(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//	�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//	�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//	�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//	�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								//	����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//	�A�X�y�N�g��
		10.0f,												//	�ǂ�����ǂ��܂�
		1000.0f);											//	�J�����ŕ\�����邩

	//	�v���W�F�N�g�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

Camera* GetCamera(void)
{
	return &g_camera;
}