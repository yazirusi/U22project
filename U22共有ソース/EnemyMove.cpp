#include"DxLib.h"
#include"EnemyMove.h"
#include"map.h"

ENEMY Enemy;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	DrawFormatString(50, 100, 0xffffff, "%d", Enemy.ax);//敵の攻撃のｘ座標
	DrawFormatString(50, 130, 0xffffff, "%d", Enemy.x);//敵のｘ座標

	//プレイヤーが動いたフラグ＆キーを押してるか
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
	}

	//if (Enemy.Attck == false) {
		//敵の座標とマップチップの当たり判定を調べる
		if (Enemy.direction == false) {//左に移動してる時の処理
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x -= (Enemy.speed);//おｋなら移動してくる
			}
			else
			{
				Enemy.direction = true;//右にするためのフラグ
			}
		}

		if (Enemy.direction == TRUE) {//右に移動してる時の処理
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x += (Enemy.speed);//おｋなら移動してくる
			}
			else
			{
				Enemy.direction = false;//左にするためのフラグ
			}
		}
	//}
}
/**************************************
*当たり判定
*hx:敵キャラのｘ座標
*hy:敵キャラのｙ座標
*Move：画面のスクロール量
***************************************/
int Hitcheck(int hx, int hy, int direction/*, int Move*/)
{
	int x = 0;//初期化
	int y = 0;//初期化

	y = hy / 40;//敵のｙ座標をマップチップに当てはめる
	x = (hx /*+ Move*/) / 40;//敵のｘ座標をマップチップに当てはめる

	return g_StageData[0][y][x];//マップチップ上での座標を返す

	return 0;
}