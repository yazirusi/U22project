#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"

int Attackheight = 25;//攻撃ｙ座標の移動量
const int AttackSpeed = 5;//攻撃ｘ座標の移動量
//const int AttackAmount = 3;//
const int Gravity = 1;//重力
int EnemyAttackX;//攻撃のｘ座標
int EnemyAttackY;//攻撃のｙ座標
int k;
ENEMY Enemy;
//Airman airman;

/***************
*Airmanの攻撃
***************/
void Airman::AirmanAttack() {

	//DrawFormatString(50, 130, 0xffffff, "%d", sx);//敵のｘ座標
	//DrawFormatString(50, 160, 0xffffff, "%d", k);//敵のｘ座標

	for (int i = 0; i < Air_MAX; i++) {
		if (Air.DispFlg[i] == true) {//フラグがtrueなら入る
			DrawGraph(Airman::AttackX[i] - Airman::MoveD + sx, Airman::AttackY[i], Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
			Airman::AttackX[i] -= AttackSpeed;//敵の攻撃を移動

			//攻撃の地面や壁の当たり判定
			if (Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i], Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Enemy.MoveD - sx, Airman::AttackY[i], Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] - Enemy.MoveD - sx, Airman::AttackY[i] + 20, Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Enemy.MoveD - sx, Airman::AttackY[i] + 20, Enemy.direction, false) == 1 ||
				0 > Airman::AttackX[i] || Airman::AttackX[i] > 1280 && Air.DispFlg[i] == true) {
				Airman::AttackX[i] = Airman::x;//攻撃座標を初期化する
				Airman::AttackY[i] = Airman::y;//攻撃の座標を初期化する
				Air.DispFlg[i] = false;//フラグをoffにする
			}
			k = sx;
		}
	}
}
/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {
	//敵の死亡判定	0:死亡　1:表示
	if (Enemy.drawf == 0) {
		return;
	}
	Enemy.Moveflg;
	airman.AirmanAttack();

	//コメント化していいかも（ごめん使わせてもらいます）
	if (Enemy.Attck == false) {//フラグがfalseの時プレイヤーの座標をいれる
		EnemyAttackX = Enemy.x;//敵のｘ座標を入れる
		EnemyAttackY = Enemy.y;//敵のｙ座標を入れる
		Enemy.speed = 1;//敵の移動量を初期化
	}

	//攻撃が発動するか確認するためのもの
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px) {
		Enemy.Attck = true;
	}
	else {
		Enemy.Attck = false;
	}

	if (Enemy.Attck == true) {//フラグがtrueなら入る
		Enemy.speed = 0;//敵の動きを止める
		DrawGraph(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
		EnemyAttackY -= Attackheight;//攻撃を上に動かす
		EnemyAttackX -= AttackSpeed;//攻撃を左に動かせる
		Attackheight -= Gravity;//重力を入れる
	}

	//攻撃の地面や壁の当たり判定
	if (Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1) {
		Enemy.Attck = false;//フラグをoffにする
		Attackheight = 25;//攻撃の移動量を初期化する
	}

	//攻撃のプレイヤーとの当たり判定
	if ((Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1) 
		&& player.hit == false) {
		//防御していたら
		if (player.protect == true) {
			//Perfect
			if (player.protecJudge == 1) {
				Enemy.drawf = 0;	//敵が反撃をもらう
			}
			player.protect = false;//防御終了
			Enemy.Attck = false;//フラグをoffにする
		}
		else {
			Enemy.Attck = false;//フラグをoffにする
			Attackheight = 25;//攻撃の移動量を初期化する
			player.hp -= 20;//プレイヤーのhpが減る
			player.hit = true;//攻撃を食らったフラグ
			if (player.hp <= 0) {
				player.pcnt = 0;	//一回だけ初期化
			}
		}
	}

	////プレイヤーが一定範囲に入ってきたら動きを止める
	//if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
	//	&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
	//	 ) {
	//	if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
	//		&& Enemy.drawf == 1) {
	//		for (int i = 0; i < AttackAmount; i++)
	//		{
	//			Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//攻撃の座標
	//		}
	//		Enemy.Attck = true;//攻撃を描画するためのフラグ
	//		Enemy.speed = 0;//敵の移動量を０にする
	//		//Enemy.MoveFlg = true;//エネミーの動きを止める
	//		//count++;
	//	}
	//}
	//else 
	//{
	//	Enemy.speed = 1;//敵の移動量を戻す
	//	//Enemy.MoveFlg = false;//エネミーを動かす
	//}
	//
	////プレイヤーが敵の攻撃範囲内に入ったら攻撃
	//if (Enemy.Attck == true) {
	//	//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//敵の攻撃が壁に当たったら消す処理
	//		if (count < 60 * AttackAmount) {
	//			count++;
	//			if (count % 60 == 0) {
	//				j++;
	//			}
	//		}
	//		for (int i = 0; i < j; i++)
	//		{
	//			DrawGraph(Enemy.ax[i] - Enemy.MoveD + sx, Enemy.y, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
	//			Enemy.ax[i] -= (AttackSpeed);//攻撃を移動する
	//		}
	//	//}
	//	//else {
	//		//Enemy.Attck = false;//攻撃をなくす
	//	//}
	//}
	////敵の攻撃が画面外に行ったら消す処理
	//for (int i = 0; i < AttackAmount; i++)
	//{
	//	if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
	//		Enemy.ax[i] = 0;
	//		//Enemy.Attck = false;//攻撃をなくす
	//	}
	//	if (Enemy.ax[i] >= WIDTH || Enemy.ax[i] + 40 <= 0 - sx)
	//	{
	//		Enemy.ax[i] = 0;
	//		//DeleteGraph(Enemy.Attackimage[0]);
	//		//Enemy.Attck = false;
	//	}
	//	if (Enemy.ax[AttackAmount - 1] == 0)
	//	{
	//		j = 0;
	//		count = 0;//敵の攻撃を初期化する
	//		Enemy.Attck = false;//敵の攻撃を辞めさせる
	//	}
	//}
}