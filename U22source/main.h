#pragma once
#include "DxLib.h"
#include <time.h>
#include <stdio.h>
#define WIDTH 1280 //画面サイズ
#define HEIGHT 850

/***********************************************
 * グローバル変数の宣言
 ***********************************************/
extern int g_KeyFlg;
extern int g_OldKey;
extern int g_NowKey;

extern int counter, FpsTime[2], FpsTime_i;
extern double Fps;

extern double t, ave, f[60];
extern int count;
extern bool debug;

typedef struct {
	int month;         //月
	int day;         //日
	int hour;      //時
	int min;        //分
} SaveData_t;
