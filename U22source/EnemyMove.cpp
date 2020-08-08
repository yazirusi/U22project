#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"
#include"main.h"

//エアーマンの変数
Airman airman;
AIR Air;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	airman.AirmanMove();
	for (int i = 0; i < MAXEnemy; i++) {

		//敵が画面外だったら非表示
		if ((-sx) < Enemy[i].x + Enemy[i].size && (-sx) + WIDTH < Enemy[i].x) {
			Enemy[i].drawf = 0;
		}
		else {
			Enemy[i].drawf = 1;
		}

		//敵が死ぬか、表示フラグが非表示なら
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == 0) {
			continue;	//ここから下の処理をしない
		}

		DrawBox((Enemy[i].x - Enemy[i].Move + sx), (Enemy[i].y),
		(Enemy[i].x + Enemy[i].size - Enemy[i].Move + sx), (Enemy[i].y + Enemy[i].size), 0x00ffff, TRUE);//敵の描画

		//敵の座標とマップチップの当たり判定を調べる
		if (Enemy[i].direction == false) {//左に移動してる時の処理
			if (Hitcheck(Enemy[i].x, Enemy[i].y, Enemy[i].direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy[i].x -= (Enemy[i].speed);//おｋなら移動してくる
			}
			else
			{
				Enemy[i].direction = true;//右にするためのフラグ
			}
		}

		if (Enemy[i].direction == TRUE) {//右に移動してる時の処理
			if (Hitcheck(Enemy[i].x + Enemy[i].size, Enemy[i].y, Enemy[i].direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy[i].x += (Enemy[i].speed);//おｋなら移動してくる
			}
			else
			{
				Enemy[i].direction = false;//左にするためのフラグ
			}
		}
		if (Enemy[i].HPdrawf == true) {
			int barlen = (Enemy[i].size * (Enemy[i].HP * 100) / Enemy[i].MaxHP) / 100;
			//敵のHPバー
			DrawBox(Enemy[i].x + sx, Enemy[i].y - 30, Enemy[i].x + sx + barlen, Enemy[i].y - 20, 0xFF0000, TRUE);
		}
	}
}
/**************
*Airmanの初期化
**************/
void Airman::Airmaninit() {
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 4) {
				Airman::MapX = x;//敵のマップ上のｘ座標を入れる
				Airman::MapY = y;//敵のマップ上のy座標を入れる
				Airman::x = (x * 40);//敵の初期x座標
				Airman::y = (y * 40);//敵の初期y座標
			}
		}
	}

	for (int i = 0; i < Air_MAX; i++) {
		Airman::AttackX[i] = 0;//攻撃座標ｘを初期化
		Airman::AttackY[i] = 0;//攻撃座標ｙを初期化
	}

	Airman::Perception = 10 * 40;//感知範囲を初期化
}
/***************
*Airmanの動き
****************/
void Airman::AirmanMove() {
	DrawBox((Airman::x - Airman::Move + sx), (Airman::y),
		(Airman::x + Airman::size - Airman::Move + sx), (Airman::y + Airman::size), 0xffffff, TRUE);//敵の描画

	//エアーマンの左側の感知範囲
	if (Airman::x - Airman::Perception < player.px + 40 && Air.DispFlg[0] == false) {
		for (int i = 0; i < Air_MAX; i++)
		{
			Airman::AttackX[i] = Airman::x /*+ sx*/ - 40 - i * 80;//敵の攻撃座標xをいれる
			Airman::AttackY[i] = Airman::y - (i % 2) * 120;//敵の攻撃座標yを入れる
			Air.DispFlg[i] = true;//感知範囲に入ったらエネミー攻撃フラグをtrueにする
		}
	}
	//エアーマンの右側の感知範囲
	if (Airman::x + Airman::Perception < player.px) {

	}
}
/*************
*Airの初期化
*************/
void AIR::AirInit() {
	for (int i = 0; i < Air_MAX; i++)
	{
		Air.DispFlg[i] = false;
	}
}
/**************************************
*当たり判定
*hx:敵キャラのｘ座標
*hy:敵キャラのｙ座標
*Move：画面のスクロール量
*pf:プレイヤーとの判定フラグ
***************************************/
int Hitcheck(int hx, int hy, int direction, bool pf/*, int Move*/)
{
	if (pf == true) {
		if (hx > player.px && hx < player.px + 40
			&& hy > player.py - 40 && hy < player.py + 40) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int x = 0;//初期化
	int y = 0;//初期化

	y = hy / 40;//敵のｙ座標をマップチップに当てはめる
	x = (hx /*+ Move*/) / 40;//敵のｘ座標をマップチップに当てはめる

	return g_StageData[0][y][x];//マップチップ上での座標を返す

	return 0;
}