#pragma once
#include "DxLib.h"
#define STAGE 2	//�X�e�[�W��
#define MAPHEIGHT 19	//�}�b�v�`�b�v�̏c
#define MAPWIDTH 200	//�}�b�v�`�b�v�̉�

//�ϐ��̐錾

extern int map[MAPHEIGHT][MAPWIDTH];
extern int g_stage;   //�X�e�[�W�Ǘ�

extern int	g_StageData[STAGE][MAPHEIGHT][MAPWIDTH];

extern int sx;///�}�b�v�`��̃X�N���[���ϐ�

extern int msx;	//�}�b�v�X�N���[���p�ϐ�

extern int sx_c;//�w�i�X�N���[����

//�֐��̐錾
void DrawMap();      //�}�b�v�`��