#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"
#include "PlayerAttack.h"
#include "BackgroundMove.h"

//player構造体
PLAYER player;

/*******************************
*プレイヤーの移動処理
********************************/
void PlayerMove() {
	//左移動
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0) {

		//左端に来たら止まる
		if (msx < 0) {
			//ブロックとの当たり判定
			if (CheckHitBlock(1,0) == 0) {
				msx += 2;		//マップチップのスクロール
				player.px -= 2;	//プレイヤーの座標
				scrool += spd;	//イラストのスクロール

				//マップチップの座標
				if (player.px % 40 == 38) {
					g_StageData[0][player.p_y][player.p_x - 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}
			}
		}
		player.direF = 1;
		//プレイヤーの画像（左向き）
		DrawExtendGraph(-5 - 65, player.py - 80, 191 - 65, player.py + 65, p[player.pcnt++ / 8 % 5 + 7], TRUE);
	}
	else {
		//右移動
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0) {

			//ブロックとの当たり判定
			if (CheckHitBlock(2, 0) == 0) {
				msx -= 2;		//マップチップのスクロール
				player.px += 2;	//プレイヤーの座標
				scrool -= spd;	//イラストのスクロール

				//マップチップの座標
				if (player.px % 40 == 0) {
					g_StageData[0][player.p_y][player.p_x + 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}
			}

			player.direF = 0;
			//プレイヤーの画像（右向き）
			DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
		}
		else {

			//立ち止まっているとき
			if (player.direF == 0) {	//右向き
				DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[0], TRUE);
			}
			if (player.direF == 1) {	//左向き
				DrawExtendGraph(-5 - 65, player.py - 80, 191 - 65, player.py + 65, p[6], TRUE);
			}
		}
	}


	//ジャンプフラグ（スペースキー）頭上にブロックがあったらジャンプできない
	if (g_KeyFlg & PAD_INPUT_1 && player.jflag == 0 && CheckHitBlock(3,0) == 0) {
		player.jflag = 1;	//ジャンプフラグ
		player.hozonY = player.py;	//ジャンプした瞬間の座標
		player.spy = player.py;		//640
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
			if (CheckHitBlock(3,0) == 1) {
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
			if (CheckHitBlock(4,0) == 1) {
				player.dflag = 0;
				player.jflag = 0;
			}
		}
	}

	//自由落下処理
	if (player.jflag == 0 && CheckHitBlock(5,0) == 1) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//落ちる瞬間の座標
		player.spy = player.py;
		player.sp_y = player.p_y;
	}
	DrawFormatString(50, 220, 0x000000, "px%d", player.px);
}

/***********************************
*プレイヤーとブロックの当たり判定
*引数
*ｊ
*１：左移動の当たり判定
*２：右移動の当たり判定
*３：上昇中の頭上のブロック
*４：下降中の下の足場
*５：横移動した先の足場
*６：攻撃の当たり判定	a：攻撃配列の添え字
*戻り値 1:ブロックに当たる
***********************************/
int CheckHitBlock(int j,int a) {

	//左移動
	if (j == 1) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1 && x * 40 + 40 == player.px	//x座標の当たり判定
					&& ((y * 40 <= player.py && y * 40 + 40 >= player.py)	//y座標の判定(下半身)
						|| (y * 40 < player.py - 40 && y * 40 + 40 > player.py - 40))) {	//上半身
					return 1;
				}
			}
		}
	}

	//右移動
	if (j == 2) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1 && x * 40 == player.px + 40	//x座標の当たり判定
					&& ((y * 40 <= player.py && y * 40 + 40 >= player.py)	//y座標の判定(下半身)
					|| (y * 40 < player.py - 40 && y * 40 + 40 > player.py - 40))) {	//上半身
					return 1;
				}
			}
		}
	}

	//上昇中(頭上の当たり判定)
	if (j == 3) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1
					&& (y * 40 <= player.py - 50 && y * 40 + 40 >= player.py - 50)//y座標
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x座標
						|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x座標
					return 1;
				}
			}
		}
	}

	//下降中(足場の当たり判定)
	if (j == 4) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1 
					&& (y * 40 <= player.py + 40 && y * 40 + 40 >= player.py + 40)//y座標
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x座標
					|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x座標

					//プレイヤーの位置
					player.py = y * 40 - 40;
					return 1;
				}
			}
		}
	}

	//自由落下
	if (j == 5) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 0
					&& (y * 40 == player.py + 40)//y座標
					&& (x * 40 == player.px)) {//x座標
					return 1;
				}
			}
		}
	}

	//攻撃
	if (j == 6) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1) {
					if (x * 40 < player.pa[a] + 80 + player.apx[a] && x * 40  + 40 > player.pa[a] + 40	+ player.apx[a]	//x座標の当たり判定
					&& y * 40 < player.ay[a] + 40 && y * 40 + 40 > player.ay[a]) {	//y座標の当たり判定
						return 1;
					}
				}
			}
		}
	}

	return 0;
}