#pragma once
#include"DxLib.h"
#define Attack_MAX 10
#define Air_MAX 4
#define Air_Speed 2
#include "EnemyAttck.h"

const int MAXEnemy = 100;

//敵の構造体
struct ENEMY
{
	int x = 0, y = 0;//敵の座標
	int MapX = 0, MapY = 0;//マップチップ上の座標
	const int size = 40;//敵のサイズ
	int speed = 1;//敵の動く速さ
	bool direction = false;//左:false 右:true
	int Move = 0;//移動量
	int MoveD = 0;//マップチップ上での座標
	//bool Attack[MAXAttack];//攻撃するためのフラグ:0なら範囲外：１なら範囲内
	bool MoveFlg = false;//敵が動くためのフラグ:trueなら動く：falseなら止まる
	//int Moveflg = 0;*/
	int Perception = 7 * 40;//敵の感知範囲
	//int ax[3] = { 0,0,0 };
	//int Attackimage[1] = { 0 };
	//int count = 0;
	bool drawf = true;	//FALSE非表示　TRUE表示
	//int move = 0;	//敵のノーツ一回分の移動量
	int AttackY[Attack_MAX], AttackX[Attack_MAX];//攻撃の座標
	int AttackInterval = 0;	//敵の攻撃間隔変数
	const int MAXAttackInterval[3] = { 90,150,150 };	//攻撃間隔
	int MaxHP[3] = { 100,30 ,500};		//敵の最大HP
	int HP = 0;			//敵のHP
	bool HPdrawf = false;	//敵のHP表示フラグ
	int type = 0;	//敵の種類
	int Imgcnt = 0;	//敵のイラストカウント
	int Jump = 20;
	bool JumpFlg = false;
	int JumpCount = 0;
}; extern ENEMY Enemy[MAXEnemy];

//エアーマンの構造体
struct Airman :public ENEMY
{
	void Airmaninit();
	void AirmanMove();
	void AirmanAttack();
};

struct AIR
{
	int Downx, Downy;
	int Upx, Upy;
	int ReloadCount = 0;
	int FlgCount = 0;
	bool DispFlg[Air_MAX];
	void AirInit();
	int AirMove(int X, int Y);
};

extern Airman airman[MAXEnemy];
extern AIR Air[MAXEnemy];

void EnemyMove();
int Hitcheck(int hx, int hy, int direction, bool pf/*, int Move*/);
void EnemyInit();