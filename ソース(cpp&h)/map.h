#pragma once
#include "DxLib.h"
#define STAGE 1	//ステージ数
#define HEIGHT 19	//マップチップの縦
#define WIDTH 200	//マップチップの横

//変数の宣言

extern int map[HEIGHT][WIDTH];
extern int mx;		//マップの移動
extern int g_stage;   //ステージ管理

extern int	g_StageData[STAGE][HEIGHT][WIDTH];

//関数の宣言
void DrawMap();      //マップ描画