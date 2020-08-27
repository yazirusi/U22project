#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"
#include "EnemyMove.h"
#include "images.h"
#include "GameInit.h"
#include "sounds.h"
#include "notes.h"
#include "Ending.h"

int AttackExtend = 0;	//ゲージの量で攻撃範囲が伸びる量
int imgflg;

/***************************************
*プレイヤーの攻撃
***************************************/
void PlayerAttack() {

	//hp０以下で死亡
	if (player.hp <= 0) {
		return;
	}

	//player.ax = player.p_x * 40;	//マップチップに合わせた攻撃の座標
	static int Xsize = 60;
	static int Ysize = 33;
	static int a_x[5] = { 0,0,0,0,0 };
	static int a_y[5] = { 0,0,0,0,0 };
	static bool ExtendFlg = false;
	static int hozon_a_x = 0;
	static int hozon_a_y = 0;
	static int hozon_diref = 0;
	static bool a_xf = false;
	static int efcnt;

	//攻撃の描画
	//for (int i = 0; i < 5; i++) {
	static int i = 0;
		if (player.af[i] == 1) {
			//player.ay[i] = player.py - 20;
			player.apx[i] = player.px;

			if (abs(AttackExtend) < player.col * 2) {
				ExtendFlg = true;
				if (player.adireF[0] == 0) {
					AttackExtend += 4;
				}
				else {
					AttackExtend -= 4;
				}
			}
			else {
				if (ExtendFlg == true) {
					//消滅
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];
					AttackExtend = 0;
				}
			}
			//攻撃の座標計算
			if (a_xf == false && (g_stage == 1 || g_stage == 0)) {
				if (player.adireF[i] == 0) {//右向き
					a_x[i] = player.px + 40 + 10;	//攻撃のx座標
				}
				if (player.adireF[i] == 1) {//左向き
					a_x[i] = player.px - 40 - 30;	//攻撃のx座標
				}
				if (AttackExtend != 0) {
					a_xf = true;
				}
			}

			//if (player.px >= 640 && sx != -6400 ) {

			//	if (player.adireF[i] == 0) {//右向き
			//		a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px + 10;	//攻撃のx座標
			//	}
			//	if (player.adireF[i] == 1) {//左向き
			//		a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px - 30;	//攻撃のx座標
			//	}
			//}
			//else if (sx == -6400) {

			//	if (player.adireF[i] == 0) {//右向き
			//		a_x[i] = player.px + 40 + sx + 10;	//攻撃のx座標
			//	}
			//	if (player.adireF[i] == 1) {//左向き
			//		a_x[i] = player.px - 40 + sx - 30;	//攻撃のx座標
			//	}
			//}
			//else {
			//	if (player.adireF[i] == 0) {//右向き
			//		a_x[i] = player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10;	//攻撃のx座標
			//	}
			//	if (player.adireF[i] == 1) {//左向き
			//		a_x[i] = player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30;	//攻撃のx座標
			//	}
			//}

			////ブロックとの当たり判定(右向き)
			//if (player.af[i] == 1 && CheckHitBlock(6,i) == 0 && player.adireF[i] == 0) {
			//	DrawBox(a_x[i], player.ay[i],a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			//	//player.pa[i] += 4;
			//	player.at[i]--;
			//}
			////ブロックにぶつかった場合初期化
			//else {
			//	//ブロックとの当たり判定(左向き)
			//	if (player.af[i] == 1 && CheckHitBlock(7, i) == 0 && player.adireF[i] == 1) {
			//		DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			//		//player.pa[i] -= 4;
			//		player.at[i]--;
			//	}
			//	//ブロックにぶつかった場合初期化
			//	else {
			//		/*player.pa[i] = 0;
			//		player.af[i] = 0;
			//		player.ay[i] = 0;*/
			//		player.at[i]--;
			//	}
			//}


			//敵に当たった場合
			for (int j = 0; j < MAXEnemy; j++) {
				int ax1, ax2;
				if (player.adireF[0] == 0) {
					//右の当たり判定用座標
					ax1 = a_x[i] + sx;
					ax2 = a_x[i] + sx + Xsize + AttackExtend;
				}
				else {
					//左
					ax1 = a_x[i] + sx + AttackExtend;
					ax2 = a_x[i] + sx + Xsize;
				}

				//エアーマンの判定
				if (ax2 > (airman[j].x + sx) && (airman[j].x + airman[j].size + sx) > ax1
					&& player.ay[i] < airman[j].y + airman[j].size && player.ay[i] + Ysize > airman[j].y - airman[j].size && player.aHitflg == false) {

					//ヒットフラグ
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//基礎攻撃力に上乗せする倍率
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					airman[j].HP -= (player.pow * bai) / 100;
					airman[j].HPdrawf = true;
					player.col = 0;	//蓄積値の初期化
					AttackExtend = 0;	//初期化
					player.ay[i] = 0;

					if (airman[j].HP <= 0) {
						airman[j].HPdrawf = false;
						airman[j].drawf = 0;
						airman[j].x = 0;
						airman[j].y = 0;//敵の座標の初期化
						EnemyFascinationCount++;
					}

					player.hp += note.conbo;
					if (player.hp > 100) {
						player.hp = 100;
					}
				}

				//0:非表示　1:表示
				if (Enemy[j].drawf == false) {
					continue;	//非表示ならここから下の処理をしない
				}
				if (ax2 > (Enemy[j].x + sx) && (Enemy[j].x + Enemy[j].size + sx) > ax1
					&& player.ay[i] < Enemy[j].y + Enemy[j].size && player.ay[i] + Ysize > Enemy[j].y - Enemy[j].size && player.aHitflg == false) {
					//ヒットフラグ
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//基礎攻撃力に上乗せする倍率
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//蓄積値の初期化
					AttackExtend = 0;	//初期化
					player.ay[i] = 0;

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//敵の座標の初期化
						EnemyFascinationCount++;
					}
					player.hp += note.conbo;
					if (player.hp > 100) {
						player.hp = 100;
					}
				}

				if (ax2 > (Enemy[j].x + sx) && player.ay[i] > Enemy[j].y - Ysize
					&&  player.aHitflg == false && Enemy[j].type == 2) {//ラスボスの当たり判定
					//ヒットフラグ
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//基礎攻撃力に上乗せする倍率
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//蓄積値の初期化
					AttackExtend = 0;	//初期化
					player.ay[i] = 0;

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//敵の座標の初期化
						g_GameState = 6;	//ラスボスを倒したらエンディング
						g_stage = 0;
						StopSoundMem(rockBGM);
					}
				}
			}
			//攻撃の当たり判定時間(20F)になったら消える
			if (player.at[i] <= 0) {
				if (ExtendFlg == false) {
					//消滅
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];
					player.af[i] = 0;
					player.col = 0;	//蓄積値の初期化
					//AttackExtend = 0;	//初期化
				}
				player.at[i] = 0;
				imgflg = false;
			}
			if (player.at[i] <= 0 || (AttackExtend == 0 && ExtendFlg == true)) {
				player.pa[i] = 0;
				if (AttackExtend == 0 && ExtendFlg == true) {
					player.af[i] = 0;
					player.ay[i] = 0;
					player.col = 0;	//蓄積値の初期化
					ExtendFlg = false;
				}
				player.apx[i] = 0;
				//player.col = 0;	//蓄積値の初期化
				//player.aHitflg = false;
				//ExtendFlg = false;
			}

			//右向きの攻撃の描画
			if (player.af[i] == 1 && player.adireF[i] == 0 && player.aHitflg == false) {
				DrawBox(a_x[i] + sx + AttackExtend, player.ay[i], a_x[i] + sx + Xsize + AttackExtend, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], FALSE);
				DrawGraph(a_x[i] + sx + AttackExtend, player.ay[i], ef[0], TRUE);
			}
			//左向きの描画
			if (player.af[i] == 1 && player.adireF[i] == 1 && player.aHitflg == false) {
				DrawBox(a_x[i] + sx + AttackExtend, player.ay[i], a_x[i] + sx + Xsize + AttackExtend, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], FALSE);
				DrawTurnGraph(a_x[i] + sx + AttackExtend, player.ay[i], ef[0], TRUE);
			}
		}

		if (player.aHitflg == true) {
			//右向きの攻撃の描画
			if (hozon_diref == 0) {
				DrawGraph(hozon_a_x + sx, hozon_a_y, ef[efcnt++ / 8 % 3 + 1], TRUE);
			}
			else {	//左向き
				DrawTurnGraph(hozon_a_x + sx, hozon_a_y, ef[efcnt++ / 8 % 3 + 1], TRUE);
			}
			if (efcnt == 24) {
				player.aHitflg = false;
				efcnt = 0;
			}
			a_xf = false;
			
		}

		if (imgflg == true) {
			player.at[i]--;
		}


		////射程距離(マップチップ３個分)になったら初期化(右向き)
		//if (player.pa[i] == 120 && player.adireF[i] == 0) {
		//	player.af[i] = 0;
		//	player.pa[i] = 0;
		//	player.ay[i] = 0;
		//	player.apx[i] = 0;
		//}

		////射程距離(マップチップ３個分)になったら初期化(左向き)
		//if (player.pa[i] == -120 && player.adireF[i] == 1) {
		//	player.af[i] = 0;
		//	player.pa[i] = 0;
		//	player.ay[i] = 0;
		//	player.apx[i] = 0;
		//}

		/*DrawFormatString(50, 190, 0xffffff, "a_x%d", a_x[0]);//敵のｘ座標
		DrawFormatString(50, 260, 0xffffff, "/%d", a_x[0] / 40);//敵のｘ座標
		DrawFormatString(50, 290, 0xffffff, "%d", player.pa[0] + 40 + player.px);//敵のｘ座標*/
	//}
}