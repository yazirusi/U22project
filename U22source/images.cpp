#include"DxLib.h"
#include"images.h"
#include"EnemyMove.h"

//変数の定義
int p[12];	//プレイヤーのイラスト
int pa[4];//プレイヤーの攻撃イラスト
int P[4]; //Pefect判定（イラスト）
int G[2]; //Great判定
int pj[6];//プレイヤーのジャンプイラスト
int pd[8];//プレイヤーの死亡イラスト
int hpg;  //HPゲージイラスト
int ag;   //攻撃のゲージイラスト

int EnemyAttackImg;

int EnemyImg[7];	//敵イラスト
int EnemyImg2[7];	//敵イラスト

int Backimg;  //背景イラスト
int Backimg2;  //背景イラスト
int Backimg3;  //背景イラスト
int Backimg4;  //背景イラスト

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
	//判定のイラスト
	if ((P[0] = LoadGraph("images/Perfect(白色).png")) == -1) return -1;
	if ((P[1] = LoadGraph("images/Perfect(水色).png")) == -1) return -1;
	if ((P[2] = LoadGraph("images/Perfect(赤色).png")) == -1) return -1;
	if ((P[3] = LoadGraph("images/Perfect(黄色).png")) == -1) return -1;
	if ((G[0] = LoadGraph("images/great(白色).png")) == -1) return -1;
	if ((G[1] = LoadGraph("images/great(水色).png")) == -1) return -1;

	//プレイヤーのイラスト
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
	if ((pa[0] = LoadGraph("images/attack-1.png")) == -1) return -1;
	if ((pa[1] = LoadGraph("images/attack-2.png")) == -1) return -1;
	if ((pa[2] = LoadGraph("images/attack-1_m.png")) == -1) return -1;
	if ((pa[3] = LoadGraph("images/attack-2_m.png")) == -1) return -1;
	if ((pj[0] = LoadGraph("images/jump-1.png")) == -1) return -1;
	if ((pj[1] = LoadGraph("images/jump-2.png")) == -1) return -1;
	if ((pj[2] = LoadGraph("images/jump-3.png")) == -1) return -1;
	if ((pj[3] = LoadGraph("images/jump-1_m.png")) == -1) return -1;
	if ((pj[4] = LoadGraph("images/jump-2_m.png")) == -1) return -1;
	if ((pj[5] = LoadGraph("images/jump-3_m.png")) == -1) return -1;
	if ((pd[0] = LoadGraph("images/dead-1.png")) == -1) return -1;
	if ((pd[1] = LoadGraph("images/dead-2.png")) == -1) return -1;
	if ((pd[2] = LoadGraph("images/dead-3.png")) == -1) return -1;
	if ((pd[3] = LoadGraph("images/dead-4.png")) == -1) return -1;
	if ((pd[4] = LoadGraph("images/dead-1_m.png")) == -1) return -1;
	if ((pd[5] = LoadGraph("images/dead-2_m.png")) == -1) return -1;
	if ((pd[6] = LoadGraph("images/dead-3_m.png")) == -1) return -1;
	if ((pd[7] = LoadGraph("images/dead-4_m.png")) == -1) return -1;
	if ((hpg = LoadGraph("images/hg.png")) == -1)return -1;
	if ((ag = LoadGraph("images/ag.png")) == -1)return -1;

	//敵のイラスト
	if ((EnemyAttackImg = LoadGraph("images/音符.png")) == -1) return -1;
	if ((EnemyImg[0] = LoadGraph("images/e_idle-1.png")) == -1) return -1;
	if ((EnemyImg[1] = LoadGraph("images/e_walk-1.png")) == -1) return -1;
	if ((EnemyImg[2] = LoadGraph("images/e_walk-2.png")) == -1) return -1;
	if ((EnemyImg[3] = LoadGraph("images/e_walk-3.png")) == -1) return -1;
	if ((EnemyImg[4] = LoadGraph("images/e_walk-4.png")) == -1) return -1;
	if ((EnemyImg[5] = LoadGraph("images/e_walk-5.png")) == -1) return -1;
	if ((EnemyImg[6] = LoadGraph("images/e_walk-6.png")) == -1) return -1;
	if ((EnemyImg2[0] = LoadGraph("images/e2_idle-1.png")) == -1) return -1;
	if ((EnemyImg2[1] = LoadGraph("images/e2_walk-1.png")) == -1) return -1;
	if ((EnemyImg2[2] = LoadGraph("images/e2_walk-2.png")) == -1) return -1;
	if ((EnemyImg2[3] = LoadGraph("images/e2_walk-3.png")) == -1) return -1;
	if ((EnemyImg2[4] = LoadGraph("images/e2_walk-4.png")) == -1) return -1;
	if ((EnemyImg2[5] = LoadGraph("images/e2_walk-5.png")) == -1) return -1;
	if ((EnemyImg2[6] = LoadGraph("images/e2_walk-6.png")) == -1) return -1;

	//背景
	if ((Backimg = LoadGraph("images/bac.bmp")) == -1)return -1;
	if ((Backimg2 = LoadGraph("images/bac2.bmp")) == -1)return -1;
	if ((Backimg3 = LoadGraph("images/bac3.bmp")) == -1)return -1;
	if ((Backimg4 = LoadGraph("images/bac_3_2.bmp")) == -1)return -1;
	if ((roadimg = LoadGraph("images/road01.bmp")) == -1)return -1;
	if ((roadimg2 = LoadGraph("images/road02.bmp")) == -1)return -1;
	if ((roadimg3 = LoadGraph("images/road03.bmp")) == -1)return -1;

	//タイトルとか
	if ((Titleimg = LoadGraph("images/Title03.png")) == -1)return -1;
	if ((GameOverimg = LoadGraph("images/gameover.png")) == -1)return -1;

	return 0;
}