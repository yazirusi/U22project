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

	//player.ax = player.p_x * 40;	//マップチップに合わせた攻撃の座標
	static int Xsize = 40;
	static int Ysize = 40;
	static int a_x[5] = { 0,0,0,0,0 };

	//攻撃の描画
	for (int i = 0; i < 5; i++) {

		if (player.adireF[i] == 0){//右向き
			a_x[i] = player.pa[i] + 80 + player.apx[i] - player.px;	//攻撃のx座標
		}
		if (player.adireF[i] == 1) {//左向き
			a_x[i] = player.pa[i] + 0 + player.apx[i] - player.px;	//攻撃のx座標
		}

		//ブロックとの当たり判定(右向き)
		if (player.af[i] == 1 && CheckHitBlock(6,i) == 0 && player.adireF[i] == 0) {
			DrawBox(a_x[i], player.ay[i],a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			player.pa[i] += 4;
		}
		//ブロックにぶつかった場合初期化
		else {
			//ブロックとの当たり判定(左向き)
			if (player.af[i] == 1 && CheckHitBlock(7, i) == 0 && player.adireF[i] == 1) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.pa[i] -= 4;
			}
			//ブロックにぶつかった場合初期化
			else {
				player.pa[i] = 0;
				player.af[i] = 0;
				player.ay[i] = 0;
			}
		}


		//敵に当たった場合
		if (( a_x[i] + Xsize ) > (Enemy.x - Enemy.Move + msx) && (Enemy.x - Enemy.Move + Enemy.size + msx) > a_x[i]
		&& player.ay[i] < Enemy.y + Enemy.size && player.ay[i] + Ysize > Enemy.y) {
			player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
			Enemy.x = 0;
			Enemy.y = 0;//敵の座標の初期化
			Enemy.drawf = 0;
		}
		//射程距離(マップチップ３個分)になったら初期化(右向き)
		if (player.pa[i] == 120 && player.adireF[i] == 0) {
			player.af[i] = 0;
			player.pa[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}

		//射程距離(マップチップ３個分)になったら初期化(左向き)
		if (player.pa[i] == -120 && player.adireF[i] == 1) {
			player.af[i] = 0;
			player.pa[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
		/*DrawFormatString(50, 190, 0xffffff, "a_x%d", a_x[0]);//敵のｘ座標
		DrawFormatString(50, 260, 0xffffff, "/%d", a_x[0] / 40);//敵のｘ座標
		DrawFormatString(50, 290, 0xffffff, "%d", player.pa[0] + 40 + player.px);//敵のｘ座標*/
	}
}