#include"DxLib.h"
#include"EnemyMove.h"
#include"map.h"

ENEMY Enemy;

/***************************************
*エネミーの動き
***************************************/
void EnemyMove(void) {
	//Enemy.x = (Enemy.Mapx * 40) + Enemy.direction * Enemy.speed;
	//Enemy.y = Enemy.MapY * 40;
	//Enemy.x = Enemy.x + (Enemy.speed * Enemy.direction);
	if (Enemy.Attck == false) {
		//敵の座標とマップチップの当たり判定を調べる
		if (Enemy.direction == false) {//左に移動してる時の処理
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction, Enemy.MoveD) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
			//if (g_StageData[0][Enemy.y/40][Enemy.x+Enemy.speed - Enemy.Move]) {
				Enemy.x -= (Enemy.speed);//おｋなら移動してくる
			}
			else
			{
				Enemy.direction = true;//右にするためのフラグ
			}
		}

		if (Enemy.direction == TRUE) {//右に移動してる時の処理
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction, Enemy.MoveD) != 1) {//当たり判定の関数に敵の座標とスクロール量を送る
				Enemy.x += (Enemy.speed);//おｋなら移動してくる
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
***************************************/
int Hitcheck(int hx, int hy, int direction, int Move)
{
	int x = 0;//初期化
	int y = 0;//初期化

	y = hy / 40;//敵のｙ座標をマップチップに当てはめる
	x = (hx + Move) / 40;//敵のｘ座標をマップチップに当てはめる

	return g_StageData[0][y][x];//マップチップ上での座標を返す

	return 0;
}