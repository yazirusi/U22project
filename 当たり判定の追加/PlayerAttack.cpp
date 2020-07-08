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

	player.ax = player.p_x * 40;	//マップチップに合わせた攻撃の座標

	//攻撃フラグ
	/*if (g_KeyFlg & PAD_INPUT_2) {
		player.af = 1;
		player.ay = player.py;
	}*/
	//攻撃の描画
	for (int i = 0; i < 5; i++) {
		if (player.af[i] == 1 && g_StageData[0][(player.ay[i] / 40) || (player.ay[i] / 40 + 1)][(player.ax + player.pa[i] + player.px + player.apx[i]) / 40 + 1] != 1) {
			DrawBox(40 + player.pa[i] + 40 + player.apx[i], player.ay[i],
				40 + 80 + player.pa[i] + player.apx[i], player.ay[i] + 40, 0xCC33FF, TRUE);
			player.pa[i] += 2;
		}
		//ブロックにぶつかった場合初期化
		else {
			player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
		//敵に当たった場合
		if ((player.pa[i] + 120) > (Enemy.x - Enemy.Move) && (Enemy.x - Enemy.Move + Enemy.size) > (player.pa[i] + 80)) {
			player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
		//射程距離(マップチップ３個分)になったら初期化
		if (player.pa[i] == 120) {
			player.af[i] = 0;
			player.pa[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
	}

	/*DrawFormatString(50, 190, 0xffffff, "%d", (player.pa[0] + 80));//敵のｘ座標
	DrawFormatString(50, 160, 0xffffff, "%d", Enemy.x - Enemy.Move);//敵のｘ座標
	DrawFormatString(50, 220, 0xffffff, "%d", player.apx[0]);//敵のｘ座標*/
}