#include"DxLib.h"
#include"images.h"
#include"EnemyMove.h"

//変数の定義
int p[12];	//プレイヤーのイラスト
int P[4]; //Pefect判定（イラスト）
int G[2]; //Great判定

int Backimg;  //背景イラスト
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

	if ((Backimg = LoadGraph("images/backimg.bmp")) == -1)return -1;

	if ((Titleimg = LoadGraph("images/kadaiTitle.png")) == -1)return -1;

	if ((GameOverimg = LoadGraph("images/kuriahaikei.png")) == -1)return -1;

	return 0;
}