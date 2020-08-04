#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"map.h"

ENEMY Enemy;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	//DrawFormatString(50, 130, 0xffffff, "%d", Enemy.x);//敵のｘ座標

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
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction,false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x -= (Enemy.speed);//おｋなら移動してくる
				Enemy.move -= (Enemy.speed);
			}
			else
			{
				Enemy.direction = true;//右にするためのフラグ
			}
		}

		if (Enemy.direction == TRUE) {//右に移動してる時の処理
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction,false) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
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
/**************************************
*当たり判定
*hx:敵キャラのｘ座標
*hy:敵キャラのｙ座標
*Move：画面のスクロール量
*pf:プレイヤーとの判定フラグ
***************************************/
int Hitcheck(int hx, int hy, int direction ,bool pf/*, int Move*/)
{
	if (pf == true) {
		if (hx > player.px && hx < player.px + 40
		&&  hy > player.py - 40 && hy < player.py + 40) {
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