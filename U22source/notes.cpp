#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"
#include "sounds.h"
#include "main.h"
#include "map.h"
#include "EnemyMove.h"

//notes構造体
NOTES note;

//BPM
const double rockbgm = 182.03;

/*double fps = 1.0 / 60.0;	//１フレーム当たりの秒数

//1小節が来るまでの時間(ms)
double nps = (60.0 / rockbgm) * 2;*/

/********************
*ノーツ
********************/
void notes() {

	double fps = ave / 1000;	//１フレーム当たりの秒数

	//1小節が来るまでの時間(ms)
	double nps = (60.0 / rockbgm) * 2;
	//1フレームをmsに変換
	note.f += fps;

	//1小節あたりのmsと現在のフレーム(ms)を比較
	if (nps < note.f) {
		note.nxbf = 1;
		note.f = note.f - nps;
		note.beatcnt++;
	}

	if (note.beatcnt == 68) {
		note.beatcnt = 0;
		note.f = 0;
	}

	if (CheckSoundMem(rockBGM) == 0 && note.bgmflg == 1) {
		note.bgmflg = 0;
	}

	//DrawFormatString(30, 430, 0xFFFFFF, "%d", CheckSoundMem(rockBGM));

	//下の枠
	DrawLine(0, 760, 300, 760, 0xFFFFFF, 4);
	DrawLine(300, 758, 300, 850, 0xFFFFFF, 4);
	DrawLine(980, 760, 1280, 760, 0xFFFFFF, 4);
	DrawLine(980, 758, 980, 850, 0xFFFFFF, 4);

	/*DrawFormatString(30, 400, 0xFFFFFF, "%lf", fps);
	DrawFormatString(30, 460, 0xFFFFFF, "%d", beatcnt);
	DrawFormatString(30, 490, 0xFFFFFF, "%d", nx[0]);
	DrawFormatString(30, 520, 0xFFFFFF, "%d", mcnt[0]);
	DrawFormatString(30, 550, 0xFFFFFF, "%d", mcnt[1]);
	DrawFormatString(30, 580, 0xFFFFFF, "%d", mcnt[2]);
	DrawFormatString(30, 580, 0xFFFFFF, "%d", player.protect);*/

	//コンボ数の表示
	if (note.conbo != 0) {
		SetFontSize(32);
		DrawFormatString(800, 750, 0xffffff, "%dコンボ", note.conbo);
		SetFontSize(16);
	}

	//ノーツの表示
	for (int i = 0; i < note.maxn; i++) {

		if (note.nbf[i] == 0 && note.nxbf == 1) {//ビートフラグが１の時
			note.nbf[i] = 1;
			note.mcntf[i] = 1;
			/*if(note.encnt % 3 == 0){
				note.nbf[i] = 2;
			}*/
			note.encnt++;
			note.nxbf = 0;//１個フラグを建てたら通らない
		}

		if (note.nbf[i] != 0) {
			note.nx[i] += 2;
		}

		
		if (note.mcntf[i] == 1) {
			note.mcnt[i] += 2;
		}

		//BGMを流す
		if (note.mcnt[i] == 640) {
			if (note.bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, TRUE);
				note.bgmflg = 1;
				note.mcnt[i] = 300;
				note.mcntf[i] = 0;
			}
			note.mcnt[i] = 300;
			note.mcntf[i] = 0;
		}

		//真ん中に来るまで
		if (note.nx[i] != 660) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, note.nx[i] - 300);	//透明度

			if (note.nx[i] == 640) {
				PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			}

			//ノーツの表示
			if (note.nbf[i] == 1) {
				DrawLine(note.nx[i], 760, note.nx[i], 850, 0x99FFFF, 8);
				DrawLine(1280 - note.nx[i], 760, 1280 - note.nx[i], 850, 0x99FFFF, 8);
			}

			//判定
			if (g_NowKey & PAD_INPUT_5 && note.nx[i] >= 620) {
				//Enemy.MoveFlg = false;
				//パーフェクト判定(+4F)
				if (abs(note.nx[i] - 640) <= 2 * note.spd) {
					PlaySoundMem(prse, DX_PLAYTYPE_BACK, TRUE);
					note.hf = 1;
					note.conbo++;
					player.col += 10;
				}

				//グレート(10F)
				if (abs(note.nx[i] - 640) <= 5 * note.spd && abs(note.nx[i] - 640) > 2 * note.spd) {
					PlaySoundMem(grse, DX_PLAYTYPE_BACK, TRUE);
					note.hf = 2;
					note.conbo++;
					player.col += 4;
				}

				//ミス
				if (abs(note.nx[i] - 640) > 5 * note.spd) {
					note.conbo = 0;
					if (player.col > 1) {
						player.col -= 4;
					}
				}

				/*//敵の行動ノーツだったら
				if (note.nbf[i] == 2) {
					if (Enemy.Attck == false) {
						Enemy.MoveFlg = true;
					}
					else {
						Enemy.AttckFlg = true;
					}
				}*/
				judgeinit(i);//ノーツの初期化
			}
			
		}
		else {	//判定しなかったら
			note.conbo = 0;
			player.right = false;
			player.left = false;
			//Enemy.MoveFlg = false;
			/*//敵の行動ノーツだったら
			if (note.nbf[i] == 2) {
				if (Enemy.Attck == false) {
					Enemy.MoveFlg = true;
				}
				else {
					Enemy.AttckFlg = true;
				}
			}*/
			if (player.col > 1) {
				player.col -= 4;
			}
			//player.protect = false;//防御終了
			note.nx[i] = 300;	//初期位置に戻す
			note.nf[i] = 0;
			note.nbf[i] = 0;
			note.nxf = 1;
		}
		//押したノーツの消え方
		if (note.nf[note.maxn] == 1 && note.bcnt != 256) {
			if (i == 0) {
				note.bcnt += 4;	//透明度用カウント
			}
		}
		else {
			note.bcnt = 0;
			note.nf[note.maxn] = 0;
		}
	}
	if (note.nf[note.maxn] == 1 && note.bcnt != 256) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (note.bcnt));
		DrawLine(note.nx[note.maxn], 760, note.nx[note.maxn], 850, 0x00FF00, 8);
		DrawLine(1280 - note.nx[note.maxn], 760, 1280 - note.nx[note.maxn], 850, 0x00FF00, 8);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透明度の初期化
}
/********************
*ノーツの判定表示
********************/
void notesjudge() {

	//パーフェクト
	if (note.hf == 1 && (note.dc++) < 40) {
		DrawGraph(540, 730, P[(note.dc) / 4 % 4], TRUE);
	}
	//グレート
	if (note.hf == 2 && note.hf != 0 && (note.dc++) < 40) {
		DrawGraph(540, 730, G[(note.dc) / 4 % 2], TRUE);
	}
	if (note.dc >= 40) {
		note.dc = 0;
		note.hf = 0;
	}
}
/**************************
*判定した時のノーツの初期化
**************************/
int judgeinit(int i) {
	note.bcnt = 0;
	note.nf[note.maxn] = 0;
	note.dc = 0;
	note.nf[i] = 1;	//フラグ
	note.nf[note.maxn] = 1;	//判定用のフラグ
	note.nx[note.maxn] = note.nx[i];	//判定用の変数
	note.nbf[i] = 0;
	note.nx[i] = 300;
	note.nxf = 1;
	return 0;
}
/**************************
*ノーツ関数の初期化
**************************/
int notesinit(int i) {
	note.nx[i] = 300;
	note.nf[i] = 0;
	note.nbf[i] = 0;
	note.mcnt[i] = 300;
	note.mcntf[i] = 0;
	note.bcnt = 0;
	note.hf = 0;
	note.conbo = 0;
	note.encnt = 0;
	note.nxf = 0;
	note.bgmflg = 0;
	note.notesInitflg = 0;
	note.min = 0;
	note.nxbf = 0;
	note.sbf = 0;
	note.beatcnt = 0;
	note.f = 0.0;
	note.dc = 0;
	return 0;
}
/********************
*ノーツの座標の最小値
********************/
int nxmin(int max) {
	int min = 600;
	for (int i = 0; i < max; ++i) {
		if (min > note.nx[i] && note.nx[i] != 300) {
			min = note.nx[i];
		}
	}

	return min;
}