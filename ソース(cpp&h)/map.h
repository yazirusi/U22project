#pragma once
#include "DxLib.h"
#define STAGE 1	//�X�e�[�W��
#define HEIGHT 19	//�}�b�v�`�b�v�̏c
#define WIDTH 200	//�}�b�v�`�b�v�̉�

//�ϐ��̐錾

extern int map[HEIGHT][WIDTH];
extern int mx;		//�}�b�v�̈ړ�
extern int g_stage;   //�X�e�[�W�Ǘ�

extern int	g_StageData[STAGE][HEIGHT][WIDTH];

//�֐��̐錾
void DrawMap();      //�}�b�v�`��