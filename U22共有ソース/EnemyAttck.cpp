#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {
	
	//プレイヤーが一定範囲に入ってきたら動きを止める
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//攻撃の座標
		Enemy.Attck = true;//攻撃を描画するためのフラグ
	}
	
	//プレイヤーが敵の攻撃範囲内に入ったら攻撃
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
		Enemy.ax -= (4);//攻撃を移動する
	}
	if (Enemy.ax >= WIDTH || Enemy.ax + 40 <= 0 - msx)
	{
		//DeleteGraph(Enemy.Attackimage[0]);
		Enemy.Attck = false;
	}
}