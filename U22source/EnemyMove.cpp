#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"

//エアーマンの変数
Airman airman;
AIR Air;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	airman.AirmanMove();
	//敵の死亡判定	0:死亡　1:表示
	if (Enemy.drawf == 0) {
		return;
	}

	if (Enemy.drawf == 1) {
		DrawBox((Enemy.x - Enemy.Move + sx), (Enemy.y),
			(Enemy.x + Enemy.size - Enemy.Move + sx), (Enemy.y + Enemy.size), 0x00ffff, TRUE);//敵の描画
	}

	/*//プレイヤーが動いたフラグ＆キーを押してるか
	if (Enemy.Moveflg == 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		Enemy.Move -= 2;//敵キャラの移動に加算するスクロール量
		if (Enemy.Attck == true) {
			Enemy.MoveD -= 2;
		}
		Enemy.Moveflg = 0;//フラグを初期化
	}
	//プレイヤーが動いたフラグ＆キーを押してるか
	else if (Enemy.Moveflg == 2 && CheckHitKey(KEY_INPUT_LEFT) != 1)
	{
		Enemy.Move += 2;//敵キャラの移動に加算するスクロール量
		if (Enemy.Attck == true) {
			Enemy.MoveD += 2;
		}
		Enemy.Moveflg = 0;
	}*/

	if (Enemy.MoveFlg == true) {

		//敵の座標とマップチップの当たり判定を調べる
		if (Enemy.direction == false) {//左に移動してる時の処理
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x -= (Enemy.speed);//おｋなら移動してくる
				Enemy.move -= (Enemy.speed);
			}
			else
			{
				Enemy.direction = true;//右にするためのフラグ
			}
		}

		if (Enemy.direction == TRUE) {//右に移動してる時の処理
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x += (Enemy.speed);//おｋなら移動してくる
				Enemy.move -= (Enemy.speed);
			}
			else
			{
				Enemy.direction = false;//左にするためのフラグ
			}
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