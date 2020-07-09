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
		 ) {
		if (Enemy.Attck == false&&Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 && Enemy.drawf == 1) {
			Enemy.ax = Enemy.x - Enemy.Move - 40;//攻撃の座標
			Enemy.Attck = true;//攻撃を描画するためのフラグ
			Enemy.MoveFlg = true;//エネミーの動きを止める
		}
	}
	else 
	{
		Enemy.MoveFlg = false;//エネミーを動かす
	}
	
	//プレイヤーが敵の攻撃範囲内に入ったら攻撃
	if (Enemy.Attck == true) {
		//敵の攻撃が壁に当たったら消す処理
		if (Hitcheck(Enemy.ax, Enemy.y, Enemy.direction) != 1) {
			DrawGraph(Enemy.ax - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
			Enemy.ax -= (4);//攻撃を移動する
		}
		else {
			Enemy.Attck = false;
		}
	}
	//敵の攻撃が画面外に行ったら消す処理
	if (Enemy.ax >= WIDTH || Enemy.ax + 40 <= 0 - msx)
	{
		//DeleteGraph(Enemy.Attackimage[0]);
		Enemy.Attck = false;
	}
}