#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "model.h"

#define PLAYER_SSIZE_X (float)(30.0f)
#define PLAYER_SSIZE_Z (float)(30.0f)

//	���[�V�����^�C�v
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//	�j���[�g����
	MOTIONTYPE_MOVE,		//	�ړ�
	MOTIONTYPE_ACTION,		//	�U��
	MOTIONTYPE_JUNP,		//	�W�����v
	MOTIONTYPE_LANDING,		//	���n
	MOTIONTYPE_MAX
}MOTIONTYPE;

//	�L�[�̍\����
typedef struct
{
	float fposx;	//	�ʒu
	float fposy;
	float fposz;
	float frotx;	//	����
	float froty;
	float frotz;
}KEY;

//	�L�[���̍\����
typedef struct
{
	int nFrame;		//	�t���[����
	KEY aKey[10];	//	�e�p�[�c�̗v�f
}KEY_INFO;

//	���[�V�������̍\����
typedef struct
{
	bool bLoop;					//	���[�v���邩�ǂ���
	int nNumKey;				//	�L�[�̑���
	KEY_INFO aKeyinfo[10];		//	�L�[���
}MOTION_INFO;

//	�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Oldpos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 moverot;
	int nIndxShadow;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	Model aModel[10];
	int nNumModel;
	D3DXMATRIX mtxWold;				//	���[���h�}�g���b�N�X
	MOTION_INFO aMotionInfo[10];	//	���[�V�������
	int nNumMotion;					//	���[�V�����̑���
	MOTIONTYPE MotionType;
	int nNumKey;					//	�L�[����
	bool bLoopMotion;				//	���[�v���邩
	int nKey;						//	���݃L�[�i���o�[
	int nextKey;
	int nCntMotion;					//	���[�V�����J�E���^�[
}Player;

//	�v���g�^�C�v
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void UpdateMotion(int count);
void DrawPlayer(void);
Player* GetPlayer(void);

#endif // !_PLAYER_H_