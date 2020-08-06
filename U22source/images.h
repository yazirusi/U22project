#pragma once
#include "DxLib.h"

extern int p[12]; //プレイヤーのイラスト
extern int P[4]; //Pefect判定（イラスト）
extern int G[2]; //Great判定


extern int Backimg;  //背景イラスト
extern int Backimg2; //背景イラスト
extern int Backimg3; //背景イラスト

extern int roadimg;  //足場イラスト上
extern int roadimg2; //足場イラスト中
extern int roadimg3; //足場イラスト下

extern int Titleimg;
extern int GameOverimg;

int LoadImages();	//画像読み込み
