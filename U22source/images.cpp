#include"DxLib.h"
#include"images.h"
#include"EnemyMove.h"

//変数の定義
int p[12];	//プレイヤーのイラスト
int P[4]; //Pefect判定（イラスト）
int G[2]; //Great判定

int Backimg;  //背景イラスト
int Backimg2;  //背景イラスト
int Backimg3;  //背景イラスト

int roadimg;
int roadimg2;
int roadimg3;


int Titleimg;
int GameOverimg;

/**********************************************
*  画像読み込み
***********************************************/
int LoadImages()
{
	if ((P[0] = LoadGraph("images/Perfect(白色).png")) == -1) return -1;

	if ((P[1] = LoadGraph("images/Perfect(水色).png")) == -1) return -1;

	if ((P[2] = LoadGraph("images/Perfect(赤色).png")) == -1) return -1;

	if ((P[3] = LoadGraph("images/Perfect(黄色).png")) == -1) return -1;

	if ((G[0] = LoadGraph("images/great(白色).png")) == -1) return -1;

	if ((G[1] = LoadGraph("images/great(水色).png")) == -1) return -1;

	if ((p[0] = LoadGraph("images/idle-1.png")) == -1) return -1;

	if ((p[1] = LoadGraph("images/run-1.png")) == -1) return -1;

	if ((p[2] = LoadGraph("images/run-3.png")) == -1) return -1;

	if ((p[3] = LoadGraph("images/run-4.png")) == -1) return -1;

	if ((p[4] = LoadGraph("images/run-5.png")) == -1) return -1;

	if ((p[5] = LoadGraph("images/run-6.png")) == -1) return -1;

	if ((p[6] = LoadGraph("images/Iidle-1.png")) == -1) return -1;

	if ((p[7] = LoadGraph("images/Irun-1.png")) == -1) return -1;

	if ((p[8] = LoadGraph("images/Irun-3.png")) == -1) return -1;

	if ((p[9] = LoadGraph("images/Irun-4.png")) == -1) return -1;

	if ((p[10] = LoadGraph("images/Irun-5.png")) == -1) return -1;

	if ((p[11] = LoadGraph("images/Irun-6.png")) == -1) return -1;

	if ((Enemy.Attackimage[0] = LoadGraph("images/音符.png")) == -1) return -1;

	if ((Backimg = LoadGraph("images/bac.bmp")) == -1)return -1;

	if ((Backimg2 = LoadGraph("images/bac2.bmp")) == -1)return -1;

	if ((Backimg3 = LoadGraph("images/bac3.bmp")) == -1)return -1;

	if ((roadimg = LoadGraph("images/road01.bmp")) == -1)return -1;

	if ((roadimg2 = LoadGraph("images/road02.bmp")) == -1)return -1;

	if ((roadimg3 = LoadGraph("images/road03.bmp")) == -1)return -1;


	if ((Titleimg = LoadGraph("images/Title03.png")) == -1)return -1;

	if ((GameOverimg = LoadGraph("images/gameover.png")) == -1)return -1;

	return 0;
}