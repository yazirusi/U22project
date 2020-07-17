#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

const int AttackSpeed = 3;
const int AttackAmount = 3;
int count = 0;
int j = 0;

/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {
	SetFontSize(30);
	DrawFormatString(100, 300, 0xffffff, "%d", count);
	DrawFormatString(100, 330, 0xffffff, "%d", j);
	DrawFormatString(100, 360, 0xffffff, "%d", Enemy.Attck);
	//プレイヤーが一定範囲に入ってきたら動きを止める
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		 ) {
		if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
			&& Enemy.drawf == 1) {
			for (int i = 0; i < AttackAmount; i++)
			{
				Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//攻撃の座標
			}
			Enemy.Attck = true;//攻撃を描画するためのフラグ
			Enemy.speed = 0;//敵の移動量を０にする
			//Enemy.MoveFlg = true;//エネミーの動きを止める
			//count++;
		}
	}
	else 
	{
		Enemy.speed = 1;//敵の移動量を戻す
		//Enemy.MoveFlg = false;//エネミーを動かす
	}
	
	//プレイヤーが敵の攻撃範囲内に入ったら攻撃
	if (Enemy.Attck == true) {
		//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//敵の攻撃が壁に当たったら消す処理
			if (count < 60 * AttackAmount) {
				count++;
				if (count % 60 == 0) {
					j++;
				}
			}
			for (int i = 0; i < j; i++)
			{
				DrawGraph(Enemy.ax[i] - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
				Enemy.ax[i] -= (AttackSpeed);//攻撃を移動する
			}
		//}
		//else {
			//Enemy.Attck = false;//攻撃をなくす
		//}
	}
	//敵の攻撃が画面外に行ったら消す処理
	for (int i = 0; i < AttackAmount; i++)
	{
		if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
			Enemy.ax[i] = 0;
			//Enemy.Attck = false;//攻撃をなくす
		}
		if (Enemy.ax[i] >= WIDTH || Enemy.ax[i] + 40 <= 0 - msx)
		{
			Enemy.ax[i] = 0;
			//DeleteGraph(Enemy.Attackimage[0]);
			//Enemy.Attck = false;
		}
		if (Enemy.ax[AttackAmount - 1] == 0)
		{
			j = 0;
			count = 0;//敵の攻撃を初期化する
			Enemy.Attck = false;//敵の攻撃を辞めさせる
		}
	}
}