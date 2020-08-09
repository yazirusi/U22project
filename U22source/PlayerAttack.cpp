#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"
#include "EnemyMove.h"

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
	static int Ysize = 60;
	static int a_x[5] = { 0,0,0,0,0 };

	//攻撃の描画
	for (int i = 0; i < 5; i++) {
		if (player.af[i] == 1) {
			player.ay[i] = player.py - 20;
			player.apx[i] = player.px;
			if (player.px >= 640) {

				if (player.adireF[i] == 0) {//右向き
					a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px + 10;	//攻撃のx座標
				}
				if (player.adireF[i] == 1) {//左向き
					a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px - 30;	//攻撃のx座標
				}
			}
			else {
				if (player.adireF[i] == 0) {//右向き
					a_x[i] = player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10;	//攻撃のx座標
				}
				if (player.adireF[i] == 1) {//左向き
					a_x[i] = player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30;	//攻撃のx座標
				}
			}

			//右向きの攻撃の描画
			if (player.af[i] == 1 && player.adireF[i] == 0) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.at[i]--;
			}
			//左向きの描画
			if (player.af[i] == 1 && player.adireF[i] == 1) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.at[i]--;
			}

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
				//0:非表示　1:表示
				if (Enemy[j].drawf == false) {
					continue;	//非表示ならここから下の処理をしない
				}
				if ((a_x[i] + Xsize) > (Enemy[j].x + sx) && (Enemy[j].x + Enemy[j].size + sx) > a_x[i]
					&& player.ay[i] < Enemy[j].y + Enemy[j].size && player.ay[i] + Ysize > Enemy[j].y && player.aHitflg == false) {
					/*player.pa[i] = 0;
					player.af[i] = 0;
					player.ay[i] = 0;
					player.apx[i] = 0;
					player.at[i] = 0;*/

					//ヒットフラグ
					player.aHitflg = true;

					//基礎攻撃力に上乗せする倍率
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//蓄積値の初期化

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//敵の座標の初期化
					}
				}
			}
			//攻撃の当たり判定時間(20F)になったら消える
			if (player.at[i] == 0) {
				player.af[i] = 0;
				player.pa[i] = 0;
				player.ay[i] = 0;
				player.apx[i] = 0;
				player.col = 0;	//蓄積値の初期化
				player.aHitflg = false;
			}
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
	}
}