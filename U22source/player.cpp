#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"
#include "PlayerAttack.h"
#include "BackgroundMove.h"
#include "sounds.h"

//player構造体
PLAYER player;

/*******************************
*プレイヤーの移動処理
********************************/
void PlayerMove() {

	//プレイヤーのステータス描画
	SetFontSize(24);
	DrawFormatString(10, 770, 0xffffff, "モチベーション：%d", player.hp);
	SetFontSize(16);
	//DrawFormatString(30, 200, 0xffffff, "px%d", player.px);
	//DrawFormatString(30, 230, 0xffffff, "py%d", player.py);
	//DrawFormatString(30, 260, 0xffffff, "jflag%d", player.jflag);

	//hp０以下で死亡
	if (player.hp <= 0) {
		return;
	}
	//敵の攻撃を食らったら点滅用カウントを加算する
	if (player.hit == true) {
		player.hitcnt++;
	}
	//無敵時間が切れたら
	if (player.hitcnt == player.invit) {
		player.hit = false;
		player.hitcnt = 0;
	}
	//左移動
	/*if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0
		|| CheckHitKey(KEY_INPUT_LEFT) == 1) {*/
	if(player.left == true){
		//左端に来るまで
		if (msx < 0) {
			//ブロックとの当たり判定
			if (CheckHitBlock(1, 0) == 0) {
				msx += player.speed;		//マップチップのスクロール
				player.px -= player.speed;	//プレイヤーの座標
				if (player.px >= 640) {
					spd += player.speed + 1;
					scrool += player.speed;	//イラストのスクロール
					sx += player.speed;
				}
				/*//マップチップの座標
				if (player.px % 40 == 38) {
					g_StageData[0][player.p_y][player.p_x - 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}*/
			}
		}
		else {
			player.left = false;
		}
		player.direF = 1;
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5) {
			if (player.px >= 640) {
				//プレイヤーの画像（左向き）
				DrawExtendGraph(640 - 45 - 65, player.py - 80, 640 + 151 - 65, player.py + 65, p[player.pcnt++ / 8 % 5 + 7], TRUE);
			}
			else {
				//プレイヤーの画像（左向き）
				DrawExtendGraph(player.px - 45 - 65, player.py - 80, player.px + 151 - 65, player.py + 65, p[player.pcnt++ / 8 % 5 + 7], TRUE);
			}
		}
	}
	//右移動
	/*if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0
		|| CheckHitKey(KEY_INPUT_RIGHT) == 1) {*/

	if (player.right == true) {
		//ブロックとの当たり判定
		if (CheckHitBlock(2, 0) == 0) {
			msx -= player.speed;		//マップチップのスクロール
			player.px += player.speed;	//プレイヤーの座標

			if (player.px >= 640) {
				spd -= player.speed + 1;
				scrool -= player.speed;	//イラストのスクロール
				sx -= player.speed;
			}

			/*//マップチップの座標
			if (player.px % 40 == 0) {
				g_StageData[0][player.p_y][player.p_x + 1] = 2;
				g_StageData[0][player.p_y][player.p_x] = 0;
				player.p_x = player.px / 40;
			}*/
		}
		else {
			printf("a");
		}

		player.direF = 0;
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5) {
			if (player.px >= 640) {
				//プレイヤーの画像（右向き）
				DrawExtendGraph(640 - 45, player.py - 80, 640 + 151, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
			}
			else {
				//プレイヤーの画像（右向き）
				DrawExtendGraph(player.px - 45, player.py - 80, player.px + 151, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
			}
		}
	}

	if (player.right == false && player.left == false) {
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5) {
			if (player.px >= 640) {
				//立ち止まっているとき
				if (player.direF == 0) {	//右向き
					DrawExtendGraph(640 - 45, player.py - 80, 640 + 151, player.py + 65, p[0], TRUE);
				}
				if (player.direF == 1) {	//左向き
					DrawExtendGraph(640 - 45 - 65, player.py - 80, 640 + 151 - 65, player.py + 65, p[6], TRUE);
				}
			}
			else {			//立ち止まっているとき
				if (player.direF == 0) {	//右向き
					DrawExtendGraph(player.px - 45, player.py - 80, player.px + 151, player.py + 65, p[0], TRUE);
				}
				if (player.direF == 1) {	//左向き
					DrawExtendGraph(player.px - 45 - 65, player.py - 80, player.px + 151 - 65, player.py + 65, p[6], TRUE);
				}
			}
		}
	}

	//自由落下処理
	if (player.jflag == 0 && CheckHitBlock(5, 0) == 1) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//落ちる瞬間の座標
		player.spy = player.py;
		player.sp_y = player.p_y;
	}

	//ジャンプフラグ（スペースキー）頭上にブロックがあったらジャンプできない
	if (player.jump == true) {
		PlaySoundMem(jpse, DX_PLAYTYPE_BACK, TRUE);
		player.jflag = 1;	//ジャンプフラグ
		player.hozonY = player.py;	//ジャンプした瞬間の座標
		player.spy = player.py;		//640
		player.sp_y = player.p_y;	//17
		player.py = player.py - 20;	//ジャンプの加速度
		player.jump = false;
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
*６：右向きの攻撃の当たり判定	a：攻撃配列の添え字
*７：左向きの攻撃判定			a:攻撃配列の添え字
*戻り値 1:ブロックに当たる
***********************************/
int CheckHitBlock(int j,int a) {

	//左移動
	if (j == 1) {
		/*for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1 && x * 40 + 40 == player.px	//x座標の当たり判定
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y座標の判定(下半身)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//上半身
					return 1;
				}
			}
		}*/
		if (g_StageData[0][player.py / 40][(player.px - 1) / 40] == 1) {
			return 1;
		}
		if (g_StageData[0][(player.py - 40) / 40][(player.px - 1) / 40] == 1) {
			return 1;
		}
	}

	//右移動
	if (j == 2) {
		/*for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1 && x * 40 == player.px + 40	//x座標の当たり判定
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y座標の判定(下半身)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//上半身

					return 1;
				}
			}
		}*/
		if (g_StageData[0][player.py / 40][(player.px + 40) / 40] == 1) {
			return 1;
		}
		if (g_StageData[0][(player.py - 40) / 40][(player.px + 40) / 40] == 1) {
			return 1;
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
		/*if (g_StageData[0][player.py / 40][player.px / 40] == 1) {
			return 1;
		}*/
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
		/*if ((g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40 - 1] == 1
		  || g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40] == 1)) {
			//プレイヤーの位置
			player.py = player.py - (player.py % 40);
			return 1;
		}*/
	}

	//自由落下
	if (j == 5) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 0
					&& (y * 40 == player.py + 40)//y座標
					&& (x * 40 < player.px + 40 && x * 40 + 40 < player.px ) ){//x座標
					return 1;
				}
			}
		}
		/*if (g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40 - 1] != 1) {
			return 1;
		}*/
	}

	//攻撃(右向き)
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

	//攻撃(左向き)
	if (j == 7) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[0][y][x] == 1) {
					if (x * 40 < player.pa[a] + 0 + player.apx[a] && x * 40 + 40 > player.pa[a] - 40 + player.apx[a]	//x座標の当たり判定
						&& y * 40 < player.ay[a] + 40 && y * 40 + 40 > player.ay[a]) {	//y座標の当たり判定
						return 1;
					}
				}
			}
		}
	}

	return 0;
}