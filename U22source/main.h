#pragma once
#include "DxLib.h"
#include <time.h>
#include <stdio.h>
#define WIDTH 1280 //��ʃT�C�Y
#define HEIGHT 850

/***********************************************
 * �O���[�o���ϐ��̐錾
 ***********************************************/
extern int g_KeyFlg;
extern int g_OldKey;
extern int g_NowKey;

extern int counter, FpsTime[2], FpsTime_i;
extern double Fps;

extern double t, ave, f[60];
extern int count;

typedef struct {
	int month;         //��
	int day;         //��
	int hour;      //��
	int min;        //��
} SaveData_t;
