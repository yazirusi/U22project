#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"
#include"main.h"
#include"images.h"

//エアーマンの変数
Airman airman;
AIR Air;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	airman.AirmanMove();

	for (int i = 0; i < MAXEnemy; i++) {

		//敵が動くときカウント
		if (Enemy[i].MoveFlg == true) {
			Enemy[i].Imgcnt++;
		}
		else {
			Enemy[i].Imgcnt = 0;
		}

		//敵が画面外だったら非表示
		if ((-sx) > Enemy[i].x + Enemy[i].size || (-sx) + WIDTH < Enemy[i].x) {
			Enemy[i].drawf = false;
		}
		else {
			Enemy[i].drawf = true;
		}

		//敵が死ぬか、表示フラグが非表示なら
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//ここから下の処理をしない
		}

		if (Enemy[i].type == 0) {//白い敵
			DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
				(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);//敵の判定描画

			//イラストの描画
			if (Enemy[i].MoveFlg == true) {	//動いていたら
				if (Enemy[i].direction == true) {
					DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[Enemy[i].Imgcnt / 15 % 6 + 1], TRUE);
				}
				else {
					DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[Enemy[i].Imgcnt / 15 % 6 + 1], TRUE);
				}
			}
			else {
				if (Enemy[i].direction == true) {
					DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[0], TRUE);
				}
				else {
					DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg[0], TRUE);
				}
			}
		}
		if (Enemy[i].type == 1) {//赤い敵
			//敵の判定描画
			DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
				(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);

			//イラストの反映
			if (Enemy[i].direction == true) {
				DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg2[0], TRUE);
			}
			else {
				DrawTurnGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, EnemyImg2[0], TRUE);
			}
		}

		//プレイヤーの方に振り向く
		if (Enemy[i].type == 1) {
			if (player.px < Enemy[i].x) {
				Enemy[i].direction = false;
			}
			if (player.px > Enemy[i].x + 40) {
				Enemy[i].direction = true;
			}
		}

		//赤色の敵は動かない
		if (Enemy[i].type != 1) {
			//敵の座標とマップチップの当たり判定を調べる
			if (Enemy[i].direction == false && Enemy[i].MoveFlg == true) {//左に移動してる時の処理
				if (Hitcheck(Enemy[i].x, Enemy[i].y, Enemy[i].direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
					Enemy[i].x -= (Enemy[i].speed);//おｋなら移動してくる
				}
				else
				{
					Enemy[i].direction = true;//右にするためのフラグ
				}
			}

			if (Enemy[i].direction == TRUE && Enemy[i].MoveFlg == true) {//右に移動してる時の処理
				if (Hitcheck(Enemy[i].x + Enemy[i].size, Enemy[i].y, Enemy[i].direction, false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
					Enemy[i].x += (Enemy[i].speed);//おｋなら移動してくる
				}
				else
				{
					Enemy[i].direction = false;//左にするためのフラグ
				}
			}
		}
		if (Enemy[i].HPdrawf == true) {
			int barlen = (Enemy[i].size * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			//敵のHPバー
			DrawBox(Enemy[i].x + sx, Enemy[i].y - 70, Enemy[i].x + sx + barlen, Enemy[i].y - 60, 0xFF0000, TRUE);
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

	Airman::Perception = 12 * 40;//感知範囲を初期化
}
/***************
*Airmanの動き
****************/
void Airman::AirmanMove() {
	DrawBox((Airman::x - Airman::Move + sx), (Airman::y),
		(Airman::x + Airman::size - Airman::Move + sx), (Airman::y + Airman::size), 0xffffff, TRUE);//敵の描画

	//エアーマンの左側の感知範囲
	if (Airman::x - Airman::Perception < player.px + 40) {
		//敵の攻撃が描画されてるか見る
		for (int i = 0; i < Air_MAX; i++)
		{
			if (Air.DispFlg[i] == true) {
				Air.FlgCount = 0;//描画されてるなら抜ける
				break;
			}
			else
			{
				Air.FlgCount = 1;//描画されてないのなら１を入れる
			}
		}
		//敵の攻撃がすべて消えていたのなら攻撃の情報を入れる
		if (Air.FlgCount == 1)
		{
			Air.ReloadCount++;
			if (Air.ReloadCount == 120) {
				for (int i = 0; i < Air_MAX; i++)
				{
					Airman::AttackX[i] = Airman::x /*+ sx*/ - 40 - i * 120;//敵の攻撃座標xをいれる
					Airman::AttackY[i] = Airman::y - (i % 2) * 120;//敵の攻撃座標yを入れる
					Air.DispFlg[i] = true;//感知範囲に入ったらエネミー攻撃フラグをtrueにする
					Air.ReloadCount = 0;
				}
			}
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
/**************************************
*敵の初期化
***************************************/
void EnemyInit() {

	//敵の初期化
	for (int i = 0; i < MAXEnemy; i++) {
		Enemy[i].x = 0;
		Enemy[i].drawf = false;
	}

	//マップチップに合わせて座標を設定する
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//空きのある配列に代入する
						Enemy[i].type = 0;	//上に攻撃を飛ばすやつ
						Enemy[i].MapX = x;//敵のマップ上のｘ座標を入れる
						Enemy[i].MapY = y;//敵のマップ上のy座標を入れる
						Enemy[i].x = (x * 40);//敵の初期x座標
						Enemy[i].y = (y * 40);//敵の初期y座標
						Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
						Enemy[i].direction = 0;
						Enemy[i].drawf = true;
						Enemy[i].HPdrawf = false;	//敵のHP表示フラグ
						break;
					}
				}
			}
			if (g_StageData[0][y][x] == 5) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//空きのある配列に代入する
						Enemy[i].type = 1;	//自キャラに攻撃飛ばすやつ
						Enemy[i].MapX = x;//敵のマップ上のｘ座標を入れる
						Enemy[i].MapY = y;//敵のマップ上のy座標を入れる
						Enemy[i].x = (x * 40);//敵の初期x座標
						Enemy[i].y = (y * 40);//敵の初期y座標
						Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
						Enemy[i].direction = 0;
						Enemy[i].drawf = true;
						Enemy[i].HPdrawf = false;	//敵のHP表示フラグ
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < MAXAttack; i++) {
		Attackheight[i] = 25;
		AttackFlg[i] = false;//攻撃するためのフラグ:0なら範囲外：１なら範囲内
		AttackType[i] = 0;
	}
}