#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"
#include"main.h"
#include"images.h"

//エアーマンの変数
Airman airman[MAXEnemy];
AIR Air[MAXEnemy];

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {

	for (int i = 0; i < MAXEnemy; i++) {
		Air[0].ReloadCount = i;
		airman[i].AirmanMove();

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
		else if(Enemy[i].HP > 0){
			Enemy[i].drawf = true;
		}

		//敵が死ぬか、表示フラグが非表示なら
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//ここから下の処理をしない
		}

		if (Enemy[i].type == 0) {//白い敵
			if (debug == true) {
				DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
					(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size), 0xff0000, FALSE);//敵の判定描画
			}
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
		if (Enemy[i].type == 2) {//ラスボス
			//敵の判定描画
			if (debug == true) {
				DrawBox((Enemy[i].x + sx), (Enemy[i].y - Enemy[i].size),
					(Enemy[i].x + sx + Enemy[i].size), (Enemy[i].y + Enemy[i].size + 80), 0xff0000, FALSE);
			}
			//イラストの反映
			DrawGraph(Enemy[i].x + sx + 3, Enemy[i].y - Enemy[i].size, lasboss[0], TRUE);
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
			static int barlen;
			if (Enemy[0].type == 2) {//らすぼすだったら
				barlen = (200 * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			}
			else {
				barlen = (Enemy[i].size * (Enemy[i].HP * 100) / Enemy[i].MaxHP[Enemy[i].type]) / 100;
			}
			//敵のHPバー
			DrawBox(Enemy[i].x + sx, Enemy[i].y - 80, Enemy[i].x + sx + barlen, Enemy[i].y - 60, 0xFF0000, TRUE);
		}
	}
}
/**************
*Airmanの初期化
**************/
void Airman::Airmaninit() {
	x = 0;

	static int intt = 0;
	static int innt = 0;

	Perception = 12 * 40;//感知範囲を初期化

	for (int j = intt; j < MAPHEIGHT; j++) {
		for (int k = innt; k < MAPWIDTH; k++) {
			if (g_StageData[g_stage][j][k] == 4) {
				/*MapX = k;
				MapY = j;*/
				x = (k * 40);
				y = (j * 40);
				HP = 80;
				intt = j;
				innt = k + 1;
				break;
			}
		}
	}
}
/***************
*Airmanの動き
****************/
void Airman::AirmanMove() {

	const int Gravity = 1;

	if (x != 0 && y != 0 && direction == false) {
		//DrawBox((x - Move + sx), (y), (x + size - Move + sx), (y + size), 0xffffff, TRUE);//敵の描画
		DrawTurnGraph(x + sx + 3, y - size, EnemyImg3[0], TRUE);
	}
	if (x != 0 && y != 0 && direction == true){
		DrawGraph(x + sx + 3, y - size, EnemyImg3[0], TRUE);
	}

	//JumpCount++;

	/*if (JumpCount == 180 && JumpFlg == false) {
		JumpFlg = true;
	}*/

	if (JumpFlg == false) {
		Jump -= Gravity;
		y -= Jump;
	}

	if (Hitcheck(x, y + size - Jump, 0, false) == 1 && JumpFlg == false) {
		//y -= Jump;
		Jump = 20;
		JumpFlg = true;
	}
	if (JumpFlg == true)
	{
		JumpCount++;
		if (JumpCount == 180) {
			JumpCount = 0;
			JumpFlg = false;
		}
	}
	//攻撃間隔
	if (AttackInterval > 0) {
		AttackInterval--;
	}

	//HP表示
	if (HPdrawf == true) {
		int barlen;
		barlen = (size * HP * 100 / 80) / 100;
		//敵のHPバー
		DrawBox(x + sx, y - 80, x + sx + barlen, y - 60, 0xFF0000, TRUE);
	}

	/*else if (Hitcheck(x, y + size - Jump, 0, false) == 1 && JumpFlg == true)
	{
		y -= 0;
		Jump = 20;
		JumpCount = 0;
		JumpFlg = false;
	}*/
}
/*************
*Airの初期化
*************/
void AIR::AirInit() {
	for (int j = 0; j < Air_MAX; j++) {
		DispFlg[j] = false;
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

	return g_StageData[g_stage][y][x];//マップチップ上での座標を返す

	return 0;
}
/**************************************
*敵の初期化
***************************************/
void EnemyInit() {

	static int width;

	//敵の初期化
	for (int i = 0; i < MAXEnemy; i++) {
		Enemy[i].x = 0;
		Enemy[i].drawf = false;
		Enemy[i].HP = 0;
	}
	//マップチップに合わせて座標を設定する
	if (g_stage == 0) {
		width = MAPWIDTH;
	}
	else {
		width = 33;
	}

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < width; x++) {
			/*if (g_StageData[g_stage][y][x] == 3) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].drawf == false) {	//空きのある配列に代入する
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
			if (g_StageData[g_stage][y][x] == 5) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].drawf == false) {	//空きのある配列に代入する
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
			}*/
			for (int i = 0,e = g_StageData[g_stage][y][x];
				i < MAXEnemy && (e == 3 || e == 5 || e == 6) ; i++) {
				if (Enemy[i].drawf == false) {	//空きのある配列に代入する
					Enemy[i].MapX = x;//敵のマップ上のｘ座標を入れる
					Enemy[i].MapY = y;//敵のマップ上のy座標を入れる
					Enemy[i].x = (x * 40);//敵の初期x座標
					Enemy[i].y = (y * 40);//敵の初期y座標
					Enemy[i].direction = 0;
					Enemy[i].drawf = true;
					Enemy[i].HPdrawf = false;	//敵のHP表示フラグ
					if(e == 3)Enemy[i].type = 0;	//上に攻撃飛ばすやつ
					if(e == 5)Enemy[i].type = 1;	//自キャラに攻撃飛ばすやつ
					if (e == 6) {
						Enemy[i].type = 2;	//ラスボス
						Enemy[i].HPdrawf = true;	//敵のHP表示フラグ
					}
					Enemy[i].HP = Enemy[i].MaxHP[Enemy[i].type];
					break;
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