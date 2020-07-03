#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {
	
	//プレイヤーが一定範囲に入ってきたら動きを止める
	if (Enemy.x - Enemy.Move - Enemy.MoveD - Enemy.Perception < px + 40/*&&Enemy.x + Enemy.Perception > px*/
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - Enemy.MoveD - 40;//攻撃の座標
		Enemy.Attck = true;//攻撃を描画するためのフラグ
	}
	if (Enemy.Attck == true) {
		DrawBox(Enemy.ax, Enemy.y, Enemy.ax + 40, Enemy.y + 40, 0xffffff, TRUE);//攻撃を描画する
		Enemy.ax -= (1);//攻撃を移動する
	}
}