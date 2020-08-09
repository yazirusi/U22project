#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"
#include"images.h"
#include"math.h"
#include"BackgroundMove.h"

int Attackheight[MAXAttack]; //= 25;//攻撃ｙ座標の移動量(GameInitで25代入)
const int AttackSpeed = 5;//攻撃ｘ座標の移動量
const double RotAttackSpd = 2;	//自キャラに向かってくる攻撃の速度
//const int AttackAmount = 3;//
const int Gravity = 1;//重力
double EnemyAttackX[MAXAttack];//攻撃のｘ座標
double EnemyAttackY[MAXAttack];//攻撃のｙ座標
double EnemyAttackRot[MAXAttack];	//敵の攻撃が進む角度
bool AttackFlg[MAXAttack];	//攻撃表示フラグ
bool AttackDir[MAXAttack];	//攻撃の向き 0：左　１:右
int AttackType[MAXAttack];	//敵の攻撃の種類
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
		DrawFormatString(150, 290, 0x000000, "%d", player.px);
		DrawFormatString(150, 320, 0x000000, "%d", scrool);

		Enemy[i].speed = 1;

		//敵の射程範囲内にいたら(左)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			Enemy[i].speed = 0;//敵の動きを止める
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//敵のｘ座標を入れる
					EnemyAttackY[a] = Enemy[i].y;//敵のｙ座標を入れる
					AttackDir[a] = Enemy[i].direction;	//敵の攻撃の向き
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//敵の種類ごとの攻撃間隔
					AttackType[a] = Enemy[i].type;	//敵の種類ごとの攻撃パターン
					double taX = (double)player.px - EnemyAttackX[a];	//自キャラまでの距離(X)
					double taY = (double)player.py - EnemyAttackY[a];	//自キャラまでの距離(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//自キャラと敵の攻撃の角度
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
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//敵の種類ごとの攻撃間隔
					AttackType[a] = Enemy[i].type;	//敵の種類ごとの攻撃パターン
					double taX = (double)player.px - EnemyAttackX[a];	//自キャラまでの距離(X)
					double taY = (double)player.py - EnemyAttackY[a];	//自キャラまでの距離(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//自キャラと敵の攻撃の角度
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
	}
	for (int i = 0; i < MAXAttack; i++) {
		if (AttackFlg[i] == true) {//フラグがtrueなら入る
			//攻撃パターンごとの動き
			EnemyAttackType(i);

			if (AttackType[i] != 1) {	//1は壁貫通する攻撃
				//攻撃の地面や壁の当たり判定
				if (Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1) {
					AttackFlg[i] = false;//フラグをoffにする
					Attackheight[i] = 25;//攻撃の移動量を初期化する
					AttackType[i] = 0;	//攻撃パターンの初期化
				}
			}

			//攻撃が画面外に行ったら初期化
			if (-sx > EnemyAttackX[i] + 20 || -sx + WIDTH < EnemyAttackX[i]
				|| EnemyAttackY[i] + 20 < 0 || EnemyAttackY[i] + 20 > HEIGHT - 90) {
				AttackFlg[i] = false;//フラグをoffにする
				Attackheight[i] = 25;//攻撃の移動量を初期化する
				AttackType[i] = 0;	//攻撃パターンの初期化
			}

			//攻撃のプレイヤーとの当たり判定
			if ((Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1)
				&& player.hit == false) {
				//防御していたら
				if (player.protect == true) {
					//Perfect
					if (player.protecJudge == 1) {
						/*for (i = 0; i < MAXEnemy; i++) {
							Enemy[i].drawf = 0;	//敵が反撃をもらう
						}*/
					}
					player.protect = false;//防御終了
					AttackFlg[i] = false;//フラグをoffにする
					AttackType[i] = 0;	//攻撃パターンの初期化
				}
				else {
					AttackFlg[i] = false;//フラグをoffにする
					Attackheight[i] = 25;//攻撃の移動量を初期化する
					AttackType[i] = 0;	//攻撃パターンの初期化
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
int EnemyAttackType(int i) {
	if (AttackType[i] == 0) {	//放物線の攻撃
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画
		EnemyAttackY[i] -= Attackheight[i];//攻撃を上に動かす
		if (AttackDir[i] == false) {
			EnemyAttackX[i] -= AttackSpeed;//攻撃を左に動かせる
		}
		else {
			EnemyAttackX[i] += AttackSpeed;//攻撃を左に動かせる
		}

		Attackheight[i] -= Gravity;//重力を入れる
	}

	if (AttackType[i] == 1) {	//プレイヤーに向かってくる攻撃
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画

		//移動量計算
		EnemyAttackX[i] += cos(EnemyAttackRot[i]) * RotAttackSpd;
		EnemyAttackY[i] += sin(EnemyAttackRot[i]) * RotAttackSpd;
	}

	return 0;
}