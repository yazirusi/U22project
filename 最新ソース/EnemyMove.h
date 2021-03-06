#pragma once
#include"DxLib.h"

//敵の構造体
struct ENEMY
{
	int x = 0, y = 0;//敵の座標
	int MapX = 0, MapY = 0;//マップチップ上の座標
	const int size = 40;//敵のサイズ
	int speed = 1;//敵の動く速さ
	int direction = 0;//敵の向いている方向:1なら左:-1なら右
	int Move = 0;//移動量
	int MoveD = 0;//マップチップ上での座標
	bool Attck = false;//攻撃するためのフラグ:0なら範囲外：１なら範囲内
	bool MoveFlg = false;//敵が動くためのフラグ:trueなら動く：falseなら止まる
	int Moveflg = 0;//
	int Perception = 9 * 40;//敵の感知範囲
	//int ax[3] = { 0,0,0 };
	int Attackimage[1] = { 0 };
	//int count = 0;
	int drawf = 1;	//0非表示　１表示
	int move = 0;	//敵のノーツ一回分の移動量
	bool AttckFlg = false;	//敵のノーツの攻撃フラグ
};extern ENEMY Enemy;

void EnemyMove();
int Hitcheck(int hx, int hy, int direction ,bool pf/*, int Move*/);