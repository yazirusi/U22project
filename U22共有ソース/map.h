#pragma once
#include "DxLib.h"
#define STAGE 1	//ステージ数
#define MAPHEIGHT 19	//マップチップの縦
#define MAPWIDTH 200	//マップチップの横

//変数の宣言

extern int map[MAPHEIGHT][MAPWIDTH];
extern int g_stage;   //ステージ管理

extern int	g_StageData[STAGE][MAPHEIGHT][MAPWIDTH];

extern int msx;	//マップスクロール用変数

//関数の宣言
void DrawMap();      //マップ描画