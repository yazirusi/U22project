#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"
#include "sounds.h"
#include "main.h"
#include "map.h"

//notes関数の変数
int nx[100]; //ノーツの座標
int nf[100];//ノーツごとの押したときのフラグ
int nbf[100];//ノーツごとの出現フラグ
int mcnt[100];//メトロノーム
int mcntf[100];//メトロノーム用フラグ
int bcnt;	//ブレンドのカウント
int hf = 0;	//パーフェクト判定
int conbo;	//コンボ数

//BPM
const double rockbgm = 182.03;
const double fps = 1.0 / 60.0;	//１フレーム当たりの秒数

//8分音符が来るまでの時間(ms)
double nps = (60.0 / rockbgm) * 2;

//notesjudge関数の変数
int dc;	//表示する時間のカウント

/********************
*ノーツ
********************/
void notes() {
	int widthn = 80;//(WIDTH - 400)/(maxn*2); //ノーツとノーツの間隔(WIDTH/maxn)
	int maxn = ((680 / 2) / widthn) + 1;	//表示するノーツ数の数

	static int bgmflg;		//bgmを流すフラグ
	static int notesInitflg;	//初期化のフラグ
	static int nxf;		//ループのフラグ
	static int min;		//ノーツの座標の最小値
	static int nxbf;
	static int sbf;
	static int beatcnt;	//77小節

	static double f = 0.0;

	//ノーツの初期化
	if (notesInitflg == 0) {
		for (int i = 0; i < 100; i++) {
			nx[i] = 300;
			mcnt[i] = 300;
		}
		notesInitflg = 1;
	}

	//1フレームをmsに変換
	f += fps;

	//1小節あたりのmsと現在のフレーム(ms)を比較
	if (nps < f) {
		nxbf = 1;
		f = f - nps;
		beatcnt++;
	}

	if (beatcnt == 68) {
		beatcnt = 0;
		f = 0;
	}

	if (CheckSoundMem(rockBGM) == 0 && bgmflg == 1) {
		bgmflg = 0;
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
	DrawFormatString(30, 520, 0xFFFFFF, "%d", mcnt[0]);*/

	//コンボ数の表示
	if (conbo != 0) {
		SetFontSize(32);
		DrawFormatString(800, 750, 0xffffff, "%dコンボ", conbo);
		SetFontSize(16);
	}

	//ノーツの表示
	for (int i = 0; i < maxn; i++) {

		if (nbf[i] == 0 && nxbf == 1) {//ビートフラグが１の時
			nbf[i] = 1;
			mcntf[i] = 1;
			nxbf = 0;//１個フラグを建てたら通らない
		}

		if (nbf[i] == 1) {	//出現フラグが１ならノーツが動く
			nx[i] += 2;
		}

		
		if (mcntf[i] == 1) {
			mcnt[i] += 2;
		}

		//反応しなかったとき
		if (mcnt[i] == 640) {
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
				bgmflg = 1;
				mcnt[i] = 300;
				mcntf[i] = 0;
			}
		}

		//真ん中に来るまで
		if (nx[i] != 640) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i] - 300);	//透明度

			//ノーツの表示
			DrawLine(nx[i], 760, nx[i], 850, 0x99FFFF, 8);
			DrawLine(1280 - nx[i], 760, 1280 - nx[i], 850, 0x99FFFF, 8);

			//Zキーを押したら
			if (g_NowKey & PAD_INPUT_6 && nx[i] >= 600) {
				bcnt = 0;
				nf[maxn] = 0;
				hf = 0;
				dc = 0;
				//パーフェクト判定(+4F)
				if (nx[i] >= 632) {
					PlaySoundMem(prse, DX_PLAYTYPE_BACK, TRUE);
					//攻撃フラグ(最大５個同時描画)
					for (int ai = 0; ai < 5; ai++) {
						if (player.af[ai] == 0) {
							player.af[ai] = 1;
							player.ay[ai] = player.py;
							player.apx[ai] = player.px;
							player.adireF[ai] = player.direF;
							player.ajudge[ai] = 0;
							break;
						}
					}

					hf = 1;
					conbo++;
				}

				//グレート(10F)
				if (nx[i] >= 620 && nx[i] < 632) {
					PlaySoundMem(grse, DX_PLAYTYPE_BACK, TRUE);
					//攻撃フラグ(最大５個同時描画)
					for (int ai = 0; ai < 5; ai++) {
						if (player.af[ai] == 0) {
							player.af[ai] = 1;
							player.ay[ai] = player.py;
							player.apx[ai] = player.px;
							player.adireF[ai] = player.direF;
							player.ajudge[ai] = 1;
							break;
						}
					}

					hf = 2;
					conbo++;
				}

				//ミス
				if (nx[i] < 620) {
					conbo = 0;
				}

				nf[i] = 1;	//フラグ
				nf[maxn] = 1;	//判定用のフラグ
				nx[maxn] = nx[i];	//判定用の変数
				nbf[i] = 0;
				nx[i] = 300;

				//デバッグ用
				//攻撃フラグ(最大５個同時描画)
				/*for (int ai = 0; ai < 5; ai++) {
					if (player.af[ai] == 0) {
						player.af[ai] = 1;
						player.ay[ai] = player.py;
						player.apx[ai] = player.px;
						player.adireF[ai] = player.direF;
						break;
					}
				}*/
				nxf = 1;
			}
		}
		else {	//真ん中来たら
			if (nf[i] == 0) {
				conbo = 0;
			}
			//BGM
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
				bgmflg = 1;
			}
			PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			nx[i] = 300;	//初期位置に戻す
			nf[i] = 0;
			nbf[i] = 0;
			nxf = 1;
		}
		//押したノーツの消え方
		if (nf[i] == 1 || nf[maxn] == 1 && bcnt != 255) {
			bcnt++;	//透明度用カウント
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (bcnt));
			DrawLine(nx[maxn], 760, nx[maxn], 850, 0x00FF00, 8);
			DrawLine(1280 - nx[maxn], 760, 1280 - nx[maxn], 850, 0x00FF00, 8);
		}
		else {
			bcnt = 0;
			nf[maxn] = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//透明度の初期化
}
/********************
*ノーツの判定表示
********************/
void notesjudge() {

	//パーフェクト
	if (hf == 1 && (dc++) < 40) {
		DrawGraph(540, 730, P[(dc) / 4 % 4], TRUE);
	}
	//グレート
	if (hf == 2 && hf != 0 && (dc++) < 40) {
		DrawGraph(540, 730, G[(dc) / 4 % 2], TRUE);
	}
	if (dc >= 40) {
		dc = 0;
		hf = 0;
	}
}
/********************
*ノーツの座標の最小値
********************/
int nxmin(int max) {
	int min = 600;
	for (int i = 0; i < max; ++i) {
		if (min > nx[i] && nx[i] != 300) {
			min = nx[i];
		}
	}

	return min;
}