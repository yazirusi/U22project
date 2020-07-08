#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"
#include "PlayerAttack.h"

//player構造体
PLAYER player;

/*******************************
*プレイヤーの移動処理
********************************/
void PlayerMove() {

	//左移動
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (g_StageData[0][player.p_y][player.p_x - 1] != 1 && g_StageData[0][player.p_y - 1][player.p_x - 1] != 1) {
			if (player.px > 0) {
				player.px -= 2;
				Enemy.Moveflg = 1;

				//攻撃描画座標の微調整
				for (int ai = 0; ai < 5; ai++) {
					if (player.af[ai] == 1) {
						player.apx[ai] += 2;
					}
				}
			}
			else {
				player.px = 40;
				g_StageData[0][player.p_y][player.p_x] = 0;
				g_StageData[0][player.p_y][player.p_x - 1] = 2;
				player.p_x -= 1;
				mx--;
			}
		}
	}

	//右移動
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		//当たり判定処理
		if (CheckHitBlock() != 1) {
			if (g_StageData[0][player.p_y][player.p_x] != 1 && player.px < 40) {
				player.px += 2;
				Enemy.Moveflg = 2;
			}
			else {
				//移動先に壁があるか
				if (g_StageData[0][player.p_y][player.p_x + 1] != 1 && g_StageData[0][player.p_y - 1][player.p_x + 1] != 1) {
					player.px = 0;
					g_StageData[0][player.p_y][player.p_x + 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x += 1;
					mx++;
				}
			}
		}

		//プレイヤーの画像（右向き）
		DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
	}
	else {
		//右向きで立ち止まってるとき
		DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[0], TRUE);
	}


	//ジャンプフラグ（スペースキー）頭上にブロックがあったらジャンプできない
	if (g_KeyFlg & PAD_INPUT_10 && player.jflag == 0 && ((player.px == 40 && g_StageData[0][player.p_y - 2][player.p_x] != 1) 
		|| (player.px < 40 && g_StageData[0][player.p_y - 2][player.p_x - 1] != 1))) {
		player.jflag = 1;	//ジャンプフラグ
		player.hozonY = player.py;	//ジャンプした瞬間の座標
		player.spy = player.py;		//680
		player.sp_y = player.p_y;		//17
		player.py = player.py - 20;	//ジャンプの加速度
	}
	//ジャンプ処理（放物線）
	if (player.jflag == 1) {

		//ジャンプの座標の動き
		player.tempY = player.py;
		player.py += (player.py - player.hozonY) + 1;
		player.hozonY = player.tempY;

		player.p_y = player.py / 40;

		//上昇してるとき
		if (player.py - player.hozonY < 0 && player.p_y != player.sp_y) {
			//頭上にブロックがあった場合
			if (g_StageData[0][player.p_y - 1][player.p_x] == 1 || player.px < 40 
				&& g_StageData[0][player.p_y - 1][player.p_x - 1] == 1) {
				player.hozonY = player.py;	//落ちる瞬間の座標
				player.spy = player.py;
				player.sp_y = player.p_y;
			}

			//ジャンプしながら移動した先のブロック
			if (g_StageData[0][player.p_y + 1][player.p_x] != 1)
				g_StageData[0][player.p_y + 1][player.p_x] = 0;

			g_StageData[0][player.p_y][player.p_x] = 2;
		}

		//下降してるとき
		if (player.py - player.hozonY > 0 && player.p_y != player.sp_y - 6 || player.dflag == 1) {
			player.dflag = 1;
			if (g_StageData[0][player.p_y - 1][player.p_x] != 1)
				g_StageData[0][player.p_y - 1][player.p_x] = 0;

			if (g_StageData[0][player.p_y][player.p_x] != 1)
				g_StageData[0][player.p_y][player.p_x] = 2;

			//真下にブロックがあったらジャンプ処理終了
			if (g_StageData[0][player.p_y + 1][player.p_x] == 1 || player.px < 40 
				&& g_StageData[0][player.p_y + 1][player.p_x - 1] == 1) {
				if (player.py + 40 >= (player.p_y + 1) * 40) {
					player.py = -40 + (player.p_y + 1) * 40;
					player.dflag = 0;
					player.jflag = 0;
				}
			}
		}
	}

	//自由落下処理
	if (player.jflag == 0 && (g_StageData[0][player.p_y + 1][player.p_x] != 1 &&
		player.px < 40 && g_StageData[0][player.p_y + 1][player.p_x - 1] != 1)) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//落ちる瞬間の座標
		player.spy = player.py;
		player.sp_y = player.p_y;
		//player.py = player.py - 20;	//ジャンプの加速度
	}
}

/***********************************
*プレイヤーとブロックの当たり判定
*戻り値 1:ブロックに当たる
***********************************/
int CheckHitBlock() {
	//下降してるとき
	if (player.dflag == 1 && g_StageData[0][player.p_y + 1][player.p_x + 1] == 1 && player.px + 40 == 80) {
		return 1;
	}

	if (g_StageData[0][player.p_y][player.p_x + 1] == 1 && player.px + 40 == 80) {
		return 1;
	}
	return 0;
}