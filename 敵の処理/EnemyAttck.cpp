#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {

	//プレイヤーが一定範囲に入ってきたら動きを止める
	if (Enemy.x - Enemy.Move - Enemy.Perception < px + 40
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//攻撃の座標
		Enemy.Attck = true;//攻撃を描画するためのフラグ
	}
	//プレイヤーが敵の攻撃範囲内に入ったら攻撃
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD, Enemy.y, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
		Enemy.ax -= (2);//攻撃を移動する
	}
}