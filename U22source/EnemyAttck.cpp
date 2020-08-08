#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"
#include"images.h"

int Attackheight[MAXAttack]; //= 25;//攻撃ｙ座標の移動量(GameInitで25代入)
const int AttackSpeed = 5;//攻撃ｘ座標の移動量
//const int AttackAmount = 3;//
const int Gravity = 1;//重力
int EnemyAttackX[MAXAttack];//攻撃のｘ座標
int EnemyAttackY[MAXAttack];//攻撃のｙ座標
bool AttackFlg[MAXAttack];	//攻撃表示フラグ
bool AttackDir[MAXAttack];	//攻撃の向き 0：左　１:右
int k;
ENEMY Enemy[MAXEnemy];
//Airman airman;

/***************
*Airmanの攻撃
***************/
void Airman::AirmanAttack() {

	//DrawFormatString(50, 130, 0xffffff, "%d", sx);//敵のｘ座標
	//DrawFormatString(50, 160, 0xffffff, "%d", k);//敵のｘ座標

	for (int i = 0; i < Air_MAX; i++) {
		if (Air.DispFlg[i] == true) {//フラグがtrueなら入る
			DrawGraph(Airman::AttackX[i] - Airman::MoveD + sx, Airman::AttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画
			Airman::AttackX[i] -= AttackSpeed;//敵の攻撃を移動

			//攻撃の地面や壁の当たり判定
			if (Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Airman::MoveD - sx, Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Airman::MoveD - sx, Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
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

	airman.AirmanAttack();

	for (int i = 0; i < MAXEnemy; i++) {
		//Enemy.MoveFlg;

		DrawFormatString(150, 200, 0x000000, "%d", Enemy[0].x);
		DrawFormatString(150, 230, 0x000000, "%d", AttackFlg[0]);
		DrawFormatString(150, 260, 0x000000, "%d", AttackFlg[1]);

		Enemy[i].speed = 1;

		//攻撃が発動するか確認するためのもの(左)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x > player.px
			&& Enemy[i].direction == false) {
			Enemy[i].speed = 0;//敵の動きを止める
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//敵のｘ座標を入れる
					EnemyAttackY[a] = Enemy[i].y;//敵のｙ座標を入れる
					AttackDir[a] = Enemy[i].direction;	//敵の攻撃の向き
					Enemy[i].AttackInterval = 90;	//敵の攻撃間隔
					break;
				}
			}
		}
		//右
		if (Enemy[i].x + Enemy[i].Perception > player.px
			&& Enemy[i].x < player.px
			&& Enemy[i].direction == true) {
			Enemy[i].speed = 0;//敵の動きを止める
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//敵のｘ座標を入れる
					EnemyAttackY[a] = Enemy[i].y;//敵のｙ座標を入れる
					AttackDir[a] = Enemy[i].direction;	//敵の攻撃の向き
					Enemy[i].AttackInterval = 90;	//敵の攻撃間隔
					break;
				}
			}
		}

		//敵の攻撃間隔
		if (Enemy[i].AttackInterval > 0) {
			Enemy[i].AttackInterval--;
		}
		/*//一個も攻撃フラグが無かったら動く
		for (int i = 0; i < MAXAttack; i++) {
			if (Enemy.Attack[i] == true) {
				break;
			}
			if (i == MAXAttack - 1) {
				Enemy.speed = 1;
			}
		}*/

		for (int a = 0; a < MAXAttack && i == 29; a++) {
			if (AttackFlg[a] == true) {//フラグがtrueなら入る
				DrawGraph(EnemyAttackX[a] + sx, EnemyAttackY[a], EnemyAttackImg, TRUE);//敵の攻撃の描画
				EnemyAttackY[a] -= Attackheight[a];//攻撃を上に動かす
				if (AttackDir[a] == false) {
					EnemyAttackX[a] -= AttackSpeed;//攻撃を左に動かせる
				}
				else {
					EnemyAttackX[a] += AttackSpeed;//攻撃を左に動かせる
				}

				Attackheight[a] -= Gravity;//重力を入れる

				//攻撃の地面や壁の当たり判定
				if (Hitcheck(EnemyAttackX[a], EnemyAttackY[a], AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a], AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a], EnemyAttackY[a] + 20, AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a] + 20, AttackDir[a], false) == 1) {
					AttackFlg[a] = false;//フラグをoffにする
					Attackheight[a] = 25;//攻撃の移動量を初期化する
				}

				//攻撃のプレイヤーとの当たり判定
				if ((Hitcheck(EnemyAttackX[a], EnemyAttackY[a], AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a], AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a], EnemyAttackY[a] + 20, AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a] + 20, AttackDir[a], true) == 1)
					&& player.hit == false) {
					//防御していたら
					if (player.protect == true) {
						//Perfect
						if (player.protecJudge == 1) {
							Enemy[i].drawf = 0;	//敵が反撃をもらう
						}
						player.protect = false;//防御終了
						AttackFlg[a] = false;//フラグをoffにする
					}
					else {
						AttackFlg[a] = false;//フラグをoffにする
						Attackheight[a] = 25;//攻撃の移動量を初期化する
						player.hp -= 20;//プレイヤーのhpが減る
						player.hit = true;//攻撃を食らったフラグ
						if (player.hp <= 0) {
							player.pcnt = 0;	//一回だけ初期化
						}
					}
				}
			}
		}
	}

	/*Enemy.Attack = false;
	//攻撃が発動するか確認するためのもの(左)
	if (Enemy.x - Enemy.Perception < player.px + 40
		&& Enemy.x > player.px
		&& Enemy.direction == false) {
		Enemy.Attack = true;
	}
	//右
	if (Enemy.x + Enemy.Perception > player.px
		&& Enemy.x < player.px
		&& Enemy.direction == true) {
		Enemy.Attack = true;
	}

	if (Enemy.Attack == true) {//フラグがtrueなら入る
		Enemy.speed = 0;//敵の動きを止める
		DrawGraph(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.Attackimage[0], TRUE);//敵の攻撃の描画
		EnemyAttackY -= Attackheight;//攻撃を上に動かす
		if (Enemy.direction == false) {
			EnemyAttackX -= AttackSpeed;//攻撃を左に動かせる
		}
		else {
			EnemyAttackX += AttackSpeed;//攻撃を左に動かせる
		}

		Attackheight -= Gravity;//重力を入れる
	}

	//攻撃の地面や壁の当たり判定
	if (Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1) {
		Enemy.Attack = false;//フラグをoffにする
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
			Enemy.Attack = false;//フラグをoffにする
		}
		else {
			Enemy.Attack = false;//フラグをoffにする
			Attackheight = 25;//攻撃の移動量を初期化する
			player.hp -= 20;//プレイヤーのhpが減る
			player.hit = true;//攻撃を食らったフラグ
			if (player.hp <= 0) {
				player.pcnt = 0;	//一回だけ初期化
			}
		}
	}
	*/

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