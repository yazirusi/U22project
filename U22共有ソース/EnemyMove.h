#pragma once
#include"DxLib.h"

//敵の構造体
struct ENEMY
{
	int x = 0, y = 0;//敵の座標
	int MapX = 0, MapY = 0;//マップチップ上の座標
	const int size = 40;//敵のサイズ
	int speed = 1;//敵の動く速さ
	int direction = 1;//敵の向いている方向:1なら左:-1なら右
	int Move = 0;//移動量
	int MoveD = 0;//マップチップ上での座標
	bool Attck = false;//攻撃するためのフラグ:0なら範囲外：１なら範囲内
	int Moveflg = 0;//
	int Perception = 9 * 40;//敵の感知範囲
	int ax = 0;
	int Attackimage[1];
};extern ENEMY Enemy;

void EnemyMove();
int Hitcheck(int hx, int hy, int direction/*, int Move*/);