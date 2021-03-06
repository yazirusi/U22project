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
#include"sounds.h"

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
int AttackBoss[3];	//ラスボス特有の攻撃用配列
int k;
ENEMY Enemy[MAXEnemy];
//Airman airman;

/***************
*Airmanの攻撃
***************/
void Airman::AirmanAttack() {
	//エアーマンの左側の感知範囲
	if (x - Perception < player.px + 40 && x>player.px) {
		direction = false;
		for (int i = 0; i < MAXAttack; i++) {
			if (AttackFlg[i] == false) {
				if (airman[Air[1].ReloadCount].Jump == 20 && AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				if (airman[Air[1].ReloadCount].Jump == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				break;
			}
		}
	}

	//エアーマンの右側の感知範囲
	if (x + Perception > player.px && x < player.px && x != 0) {
		direction = true;
		for (int i = 0; i < MAXAttack; i++) {
			if (AttackFlg[i] == false) {
				if (airman[Air[1].ReloadCount].Jump == 20 && AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				if (airman[Air[1].ReloadCount].Jump == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				break;
			}
		}
	}

}
/*************
*
**************/
int AIR::AirMove(int X, int Y) {
	for (int i = 0; i < MAXAttack; i++) {
		if (AttackFlg[i] == true && AttackType[i] == 2) {
			/*if (airman[Air[1].ReloadCount].Jump == 20) {
				EnemyAttackX[i] = X;
				EnemyAttackY[i] = Y;
			}
			if (airman[Air[1].ReloadCount].Jump == 0 ) {
				Upx = X;
				Upy = Y;
				DispFlg[1] = true;
			}*/
			DrawGraph(EnemyAttackX[i] + sx, EnemyAttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画
			if (AttackDir[i] == false) {
				if (Enemy[0].type == 2) {//ラスボスだったら
					EnemyAttackX[i] -= 5;
				}
				EnemyAttackX[i] -= 3;
			}
			else {
				if (Enemy[0].type == 2) {//ラスボスだったら
					EnemyAttackX[i] += 5;
				}
				EnemyAttackX[i] += 3;
			}
			if (Hitcheck(EnemyAttackX[i], EnemyAttackY[i], 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i] + 20, EnemyAttackY[i], 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i], EnemyAttackY[i] + 20, 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i] + 20, EnemyAttackY[i] + 20, 0, false) == 1 ||
				0 - sx >= EnemyAttackX[i] || EnemyAttackX[i] >= 1280 - sx) {
				AttackFlg[i] = false;
				AttackType[i] = 0;
				EnemyAttackX[i] = 0;
				EnemyAttackY[i] = 0;
			}
		}
		//if (/*EnemyAttackX[i] != 0 && EnemyAttackY[i] != 0 && */DispFlg[0] == true) {
		/*DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//敵の攻撃の描画
		Upx -= 3;
		if (Hitcheck(Upx, Upy, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
			Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
			0 - sx >= Upx || Upx >= 1280 - sx) {
			DispFlg[1] = false;//フラグをoffにする
			Upx = 0;
			Upy = 0;
		}*/
	}

	//if (AttackFlg[Air[1].ReloadCount] == true)
	//{
	//	if (airman[Air[1].ReloadCount].Jump == 20 && DispFlg[0] == false
	//		/*&& Downx != 0 && Downy != 0*/) {
	//		Downx = X;
	//		Downy = Y;
	//		DispFlg[0] = true;
	//	}
	//	if (airman[Air[1].ReloadCount].Jump == 0 && DispFlg[1] == false
	//		/*&& Upx != 0 && Upy != 0*/) {
	//		Upx = X;
	//		Upy = Y;
	//		DispFlg[1] = true;
	//	}
	//}

	//if (/*Downx != 0 && Downy != 0 && */DispFlg[0] == true) {
	//	DrawGraph(Downx + sx, Downy, EnemyAttackImg, TRUE);//敵の攻撃の描画
	//	Downx -= 3;
	//	if (Hitcheck(Downx, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx, Downy + 20, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy + 20, 0, false) == 1 ||
	//		0 - sx >= Downx || Downx >= 1280 - sx && DispFlg[0] == true) {
	//		DispFlg[0] = false;//フラグをoffにする
	//		Downx = 0;
	//		Downy = 0;
	//	}
	//}
	//if (/*Upx != 0 && Upy != 0 &&*/ DispFlg[1] == true) {
	//	DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//敵の攻撃の描画
	//	Upx -= 3;
	//	if (Hitcheck(Upx, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
	//		0 - sx >= Upx || Upx >= 1280 - sx && DispFlg[1] == true) {
	//		DispFlg[1] = false;//フラグをoffにする
	//		Upx = 0;
	//		Upy = 0;
	//	}
	//}

	return 0;
}
/***************************************
*エネミーの攻撃
***************************************/
void EnemyAttck(void) {

	for (int i = 0; i < MAXEnemy; i++) {
		airman[i].AirmanAttack();

		//Enemy.MoveFlg;
		//敵が死ぬか、表示フラグが非表示なら
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//ここから下の処理をしない
		}
		if (CheckSoundMem(rockBGM) == 0) {//曲が流れていなかったら処理をしない
			continue;
		}

		//敵の攻撃間隔
		if (Enemy[i].AttackInterval > 0) {
			Enemy[i].AttackInterval--;
		}

		//Enemy[i].speed = 1;
		if (Enemy[i].type == 0) {
			Enemy[i].MoveFlg = true;
		}

		//ラスボスの攻撃(ランダムで雑魚敵の攻撃をする)
		if (Enemy[i].type == 2) {
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//敵のｘ座標を入れる
					EnemyAttackY[a] = Enemy[i].y;//敵のｙ座標を入れる
					AttackDir[a] = Enemy[i].direction;	//敵の攻撃の向き
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//敵の種類ごとの攻撃間隔
					AttackType[a] = GetRand(2);	//敵の種類ごとの攻撃パターン
					if (AttackType[a] == 0) {	//放物線の攻撃なら３つ同時に飛ばす
						for (int j = 1; j < 3; j++) {
							AttackFlg[a + j] = true;
							EnemyAttackX[a + j] = Enemy[i].x;//敵のｘ座標を入れる
							EnemyAttackY[a + j] = Enemy[i].y;//敵のｙ座標を入れる
							AttackDir[a + j] = Enemy[i].direction;	//敵の攻撃の向き
							AttackType[a + j] = 0;
							AttackBoss[j - 1] = a + j;
						}
					}
					if (AttackType[a] == 2) {
						if (GetRand(1) == 0) {
							EnemyAttackY[a] -= 80;//エアーマンの攻撃の下の攻撃
						}
						else {
							EnemyAttackY[a] += 80;//エアーマンの攻撃の上の攻撃
						}
					}
					double taX = (double)player.px - EnemyAttackX[a];	//自キャラまでの距離(X)
					double taY = (double)player.py - EnemyAttackY[a];	//自キャラまでの距離(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//自キャラと敵の攻撃の角度
					break;
				}
			}
		}

		if (g_stage == 1) {
			continue;	//ラスボス戦なら下の処理をしない
		}

		//敵の射程範囲内にいたら(左)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			//Enemy[i].speed = 0;//敵の動きを止める
			Enemy[i].MoveFlg = false;//敵の動きを止める
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
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
			//Enemy[i].speed = 0;//敵の動きを止める
			Enemy[i].MoveFlg = false;//敵の動きを止める
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
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
				PlaySoundMem(attackse2, DX_PLAYTYPE_BACK, TRUE);
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

	Air[Air[1].ReloadCount].AirMove(0, 0);

}
int EnemyAttackType(int i) {
	if (AttackType[i] == 0) {	//放物線の攻撃
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画
		if (Enemy[0].type == 2) {//ラスボスだったら

			EnemyAttackY[i] -= Attackheight[i];//攻撃を上に動かす
			if (AttackDir[i] == false) {
				if (AttackBoss[0] == i) {
					EnemyAttackX[i] -= AttackSpeed + 5;//攻撃を左に動かせる
				}
				if (AttackBoss[1] == i) {
					EnemyAttackX[i] -= AttackSpeed + 10;//攻撃を左に動かせる
				}
				if (AttackBoss[0] != i && AttackBoss[1] != i) {
					EnemyAttackX[i] -= AttackSpeed;//攻撃を左に動かせる
				}
			}
			/*else {
				EnemyAttackX[i] += AttackSpeed;//攻撃を左に動かせる
			}*/

			Attackheight[i] -= Gravity;//重力を入れる
		}
		else {
			EnemyAttackY[i] -= Attackheight[i];//攻撃を上に動かす
			if (AttackDir[i] == false) {
				EnemyAttackX[i] -= AttackSpeed;//攻撃を左に動かせる
			}
			else {
				EnemyAttackX[i] += AttackSpeed;//攻撃を左に動かせる
			}

			Attackheight[i] -= Gravity;//重力を入れる
		}
	}

	if (AttackType[i] == 1) {	//プレイヤーに向かってくる攻撃
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//敵の攻撃の描画

		if (Enemy[0].type == 2) {//ラスボスだったら
			//移動量計算
			EnemyAttackX[i] += cos(EnemyAttackRot[i]) * (RotAttackSpd + 3.0);
			EnemyAttackY[i] += sin(EnemyAttackRot[i]) * (RotAttackSpd + 3.0);
		}
		else {
			//移動量計算
			EnemyAttackX[i] += cos(EnemyAttackRot[i]) * RotAttackSpd;
			EnemyAttackY[i] += sin(EnemyAttackRot[i]) * RotAttackSpd;
		}
	}

	return 0;
}