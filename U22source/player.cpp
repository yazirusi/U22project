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
#include "GameInit.h"
#include "main.h"

//player構造体
PLAYER player;

/*******************************
*プレイヤーの移動処理
********************************/
void PlayerMove() {

	//プレイヤーのステータス描画
	SetFontSize(24);
	DrawFormatString(10, 770, 0xffffff, "HP");
	SetFontSize(16);
	//DrawFormatString(30, 200, 0xffffff, "px%d", player.px);
	//DrawFormatString(30, 230, 0xffffff, "py%d", player.py);
	//DrawFormatString(30, 260, 0xffffff, "jflag%d", player.jflag);

	//sx-3540 x1056 1136 y 600 680	80 80

	//HPゲージの描画
	DrawGraph(50, 750, hpg, TRUE);
	//攻撃ゲージの描画
	DrawGraph(50, 790, ag, TRUE);

	//ゲージの割合
	static float hpgauge, colgauge;

	hpgauge = (float)glen * ((float)player.hp / (float)100);

	if (player.hp <= 0) {
		hpgauge = 0.0;
	}

	if (player.col > 100) {
		player.col = 100;
	}

	colgauge = (float)glen * ((float)player.col / (float)100);

	//HPゲージの減少
	DrawBox(65 + (int)hpgauge, 769, 283, 799, 0x000000, TRUE);

	//攻撃ゲージの減少
	DrawBox(65 + (int)colgauge, 810, 283, 839, 0x000000, TRUE);

	//プレイヤー画像の描画位置
	if (player.px >= 640 && player.px <= (1280 * sx_c) + 640 && g_stage == 0) {
		player.ix = 595;
		player.iy = player.py - 80;
	}
	else if ( player.px >= (1280 * sx_c) + 640 ) {
		player.ix = player.px - ((1280 * sx_c) + 640) + 595;
		player.iy = player.py - 80;
	}
	else {
		player.ix = player.px - 45;
		player.iy = player.py - 80;
	}

	//プレイヤーの当たり判定描画
	if (debug == true) {
		DrawBox(player.px + sx, player.py - 40, player.px + 40 + sx, player.py + 40, 0xFF0000, FALSE);
	}

	//hp０以下で死亡
	if (player.hp <= 0) {
		//死ぬイラスト
		if (player.direF == 0) {	//右向き
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pd[player.pcnt++ / 16 % 4], TRUE);
		}
		if (player.direF == 1) {	//左向き
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pd[player.pcnt++ / 16 % 4 + 4], TRUE);
		}
		if (player.pcnt == 32) {
			PlaySoundMem(deathse, DX_PLAYTYPE_BACK, TRUE);
		}
		if (player.pcnt == 64) {
			StopSoundMem(rockBGM);
			player.hit = false;
			player.hitcnt = 0;
			g_GameState = 3;   //ゲームオーバー画面へ
		}
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
	if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0
		|| CheckHitKey(KEY_INPUT_LEFT) == 1) && player.at[0] <= 0) {
		player.left = true;
		//左端に来るまで
		if (msx < 0) {
			//ブロックとの当たり判定
			if (CheckHitBlock(1, 0) == 0) {
				msx += player.speed;		//マップチップのスクロール
				player.px -= player.speed;	//プレイヤーの座標
				if (sx < 0 && player.px < (1280 * sx_c) + 640 ) {
					spd += player.speed - 1;
					scrool += player.speed;	//イラストのスクロール
					sx += player.speed;
				}
			}
		}
		player.direF = 1;
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5 && player.jflag == 0 && player.at[0] <= 0) {
			//プレイヤーの画像（左向き）
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, p[player.pcnt++ / 8 % 5 + 7], TRUE);
		}
	}
	else {
		player.left = false;
	}
	//右移動
	if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0
		|| CheckHitKey(KEY_INPUT_RIGHT) == 1) && player.at[0] <= 0) {
		player.right = true;
		//ブロックとの当たり判定＆ラスボス戦なら障壁がある
		if (CheckHitBlock(2, 0) == 0) {
			if (player.px > 638 && g_stage == 1) {
			}
			else {
				msx -= player.speed;		//マップチップのスクロール
				player.px += player.speed;	//プレイヤーの座標
				if (player.px > 640 && (sx > (-1280 * sx_c)) && g_stage == 0) {
					spd -= player.speed - 1;
					scrool -= player.speed;	//イラストのスクロール
					sx -= player.speed;
				}
			}
		}

		player.direF = 0;
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5 && player.jflag == 0 && player.at[0] <= 0) {
			//プレイヤーの画像（右向き）
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, p[player.pcnt++ / 8 % 5 + 1], TRUE);
		}
	}
	else {
		player.right = false;
	}

	if (player.right == false && player.left == false && player.at[0] <= 0 && player.jflag == 0) {
		//攻撃を食らったら点滅させる
		if ((player.hitcnt % 10) < 5) {
			//立ち止まっているとき
			if (player.direF == 0) {	//右向き
				DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, p[0], TRUE);
			}
			if (player.direF == 1) {	//左向き
				DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, p[6], TRUE);
			}
		}
	}
	if (player.at[0] > 0) {
		//攻撃イラスト
		if ((player.hitcnt % 10) < 5 && player.direF == 0) {	//右向き
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 135, pa[player.pcnt++ / 8 % 2], TRUE);
		}
		if ((player.hitcnt % 10) < 5 && player.direF == 1) {	//左向き
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 135, pa[player.pcnt++ / 8 % 2 + 2], TRUE);
		}

		//攻撃イラストの最後のシャウトしている状態を続かせる
		if (player.pcnt > 8) {
			player.pcnt = 8;
		}
	}

	//自由落下処理
	if (player.jflag == 0 && CheckHitBlock(4, 0) == 0) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//落ちる瞬間の座標
		player.spy = player.py;
		player.sp_y = player.p_y;
	}

	//ジャンプフラグ（スペースキー）頭上にブロックがあったらジャンプできない
	if (g_KeyFlg & PAD_INPUT_1 && CheckHitBlock(3, 0) == 0 && player.jflag == 0 && player.at[0] <= 0) {
		PlaySoundMem(jpse, DX_PLAYTYPE_BACK, TRUE);
		player.jflag = 1;	//ジャンプフラグ
		player.hozonY = player.py;	//ジャンプした瞬間の座標
		player.spy = player.py;		//640
		player.sp_y = player.p_y;	//17
		player.py = player.py - 17;	//ジャンプの加速度
		player.pcnt = 0;
	}

	//ジャンプ処理（放物線）
	if (player.jflag == 1) {
		//ジャンプの座標の動き
		player.tempY = player.py;
		player.py += (player.py - player.hozonY) + 1;
		player.hozonY = player.tempY;
		//player.p_y = player.py / 40;

		//上昇してるとき
		if (player.py - player.hozonY <= 0 /*&& player.p_y != player.sp_y*/) {
			//頭上にブロックがあった場合
			if (CheckHitBlock(3,0) == 1) {
				player.hozonY = player.py;	//落ちる瞬間の座標
				player.spy = player.py;
				player.sp_y = player.p_y;
			}

			//ジャンプイラスト
			if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//右向き
				DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[0], TRUE);
			}
			if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//左向き
				DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[3], TRUE);
			}

			/*//ジャンプしながら移動した先のブロック
			if (g_StageData[0][player.p_y + 1][player.p_x] != 1)
				g_StageData[0][player.p_y + 1][player.p_x] = 0;

			g_StageData[0][player.p_y][player.p_x] = 2;*/
		}

		//下降してるとき
		if (player.py - player.hozonY > 0 /*&& player.p_y != player.sp_y - 6*/ || player.dflag == 1) {
			player.dflag = 1;
			/*if (g_StageData[0][player.p_y - 1][player.p_x] != 1)
				g_StageData[0][player.p_y - 1][player.p_x] = 0;
			
			if (g_StageData[0][player.p_y][player.p_x] != 1)
				g_StageData[0][player.p_y][player.p_x] = 2;*/

			//真下にブロックがあったらジャンプ処理終了
			if (CheckHitBlock(4,0) == 1) {
				player.dflag = 0;
				player.jflag = 0;
			}

			//ジャンプイラスト
			if (player.py - player.hozonY < 9) {
				if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//右向き
					DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[1], TRUE);
				}
				if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//左向き
					DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[4], TRUE);
				}
			}
			else {
				if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//右向き
					DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[2], TRUE);
				}
				if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//左向き
					DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[5], TRUE);
				}
			}
		}
	}
	//攻撃(R1を押したら)
	if (g_KeyFlg & PAD_INPUT_6 && player.at[0] <= 0 && AttackExtend == 0 && player.aHitflg == false) {
		//攻撃フラグ(最大５個同時描画)
		for (int ai = 0; ai < 5; ai++) {
			if (player.af[ai] == 0) {
				player.af[ai] = 1;
				player.ay[ai] = player.py - 40;
				player.apx[ai] = player.px;
				player.adireF[ai] = player.direF;
				player.ajudge[ai] = 0;
				player.at[ai] = 20;
				imgflg = true;
				break;
			}
		}
		PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
		player.pcnt = 5;
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
		if (g_StageData[g_stage][player.py / 40][(player.px - 1) / 40] == 1) {
			return 1;
		}
		if (g_StageData[g_stage][(player.py - 40) / 40][(player.px - 1) / 40] == 1) {
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
		if (g_StageData[g_stage][player.py / 40][(player.px + 40) / 40] == 1) {
			return 1;
		}
		if (g_StageData[g_stage][(player.py - 40) / 40][(player.px + 40) / 40] == 1) {
			return 1;
		}
	}

	//上昇中(頭上の当たり判定)
	if (j == 3) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//ブロックとの当たり判定
				if (g_StageData[g_stage][y][x] == 1
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
				if (g_StageData[g_stage][y][x] == 1
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
				if (g_StageData[g_stage][y][x] == 0
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
				if (g_StageData[g_stage][y][x] == 1) {
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
				if (g_StageData[g_stage][y][x] == 1) {
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

/***********************************
*プレイヤーの初期化
***********************************/
void PlayerInit() {
	//マップチップに合わせて座標を設定する
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[g_stage][y][x] == 2) {
				player.px = (x * 40);
				player.py = (y * 40);
			}
		}
	}
	player.hp = 100;
	player.pcnt = 0;	//イラストのカウント
	player.jflag = 0;	//ジャンプフラグ
	player.hozonY = 0; //ジャンプした瞬間の座標
	player.tempY = 0;	//ジャンプ時に使う入れ替え処理の変数
	player.dflag = 0;	//下降フラグ
	player.direF = 0;	//向きフラグ 0:右向き　1:左向き
	player.right = false;	//右移動のフラグ false:動かない　true:動く
	player.left = false;	//左移動のフラグ false:動かない　true:動く
	player.jump = false;  //ジャンプフラグ false:動かない　true:動く
	player.hit = false;	//敵の攻撃を食らったフラグ(食らって点滅している間無敵)
	player.hitcnt = 0;	//点滅させるカウント
	player.col = 0;
	/*protect = false;	//防御フラグ
	protecJudge = 0;	//防御用にノーツの判定を保存する*/
}