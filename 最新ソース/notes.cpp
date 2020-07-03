#include "DxLib.h"
#include "notes.h"
#include "player.h"
#include "images.h"
#include "key.h"
#include "sounds.h"
#include "main.h"

//notes関数の変数
int nx[100]; //ノーツの座標
int nf[100];//ノーツごとのフラグ
int bcnt;	//ブレンドのカウント
int hf = 0;	//パーフェクト判定

/*//BPMの構造体
extern struct BPM {
};
struct BPM bpm;
*/
//notesjudge関数の変数
int dc;	//表示する時間のカウント

/********************
*ノーツ
********************/
void notes() {
	//下の枠
	DrawLine(0, 800, 200, 800, 0xFFFFFF, 4);
	DrawLine(200, 798, 200, 850, 0xFFFFFF, 4);
	DrawLine(1080, 800, 1280, 800, 0xFFFFFF, 4);
	DrawLine(1080, 798, 1080, 850, 0xFFFFFF, 4);
	//PlaySoundMem(rockBGM, DX_PLAYTYPE_LOOP, FALSE);

	int widthn = 80;//(WIDTH - 400)/(maxn*2); //ノーツとノーツの間隔(WIDTH/maxn)
	int maxn = ((880 / 2) / widthn) + 1;	//表示するノーツ数の数

	/*int maxn = 11;	//表示するノーツ数の数
	int widthn = 40;//(WIDTH - 400)/(maxn*2); //ノーツとノーツの間隔(WIDTH/maxn)*/
	static int bgmflg;
	static int notesInitflg;
	static int nxf;
	static int min;

	//ノーツ位置の初期化
	if (notesInitflg == 0) {
		for (int i = 0; i < 100; i++) {
			nx[i] = 200;
		}
		notesInitflg = 1;
	}
	//nx[0] += 2;
	for (int i = 0; i < maxn; i++) {
		//if (nf[maxn + 1] == 1 || (nx[0] - 200) >= i * widthn)	//最初だけずらす、後ループ
		if (i != 0 && nx[0] - 200 >= i * widthn && nxf == 0) {
			nx[i] += 2;
		}
		else if (i == 0 && nxf == 0) {
			nx[i] += 2;
		}
		min = nxmin(maxn);	//最小値を探す
		if(nxf == 1 && nx[i] == 200 && min - nx[i] >= widthn){
			nx[i] += 2;
		}
		else if (nxf == 1 && nx[i] != 200) {
			nx[i] += 2;
		}

		if (nx[i] != 640) {	//真ん中に来たら
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i] - 200);	//透明度
			if (nf[i] == 0 && nx[i] != 200) {
				DrawLine(nx[i], 800, nx[i], 850, 0x99FFFF, 8);
				DrawLine(1280 - nx[i], 800, 1280 - nx[i], 850, 0x99FFFF, 8);
			}
			if (g_NowKey & PAD_INPUT_1 && nx[i] >= 610 && nf[maxn] == 0) {	//Zキーを押したら
				if (nx[i] >= 625)
					hf = 1; //パーフェクト判定
				if (nx[i] >= 605 && nx[i] < 625)
					hf = 2;
				nf[i] = 1;	//フラグ
				nf[maxn] = 1;	//判定用のフラグ
				nx[maxn] = nx[i];	//判定用の変数
			}
		}
		else {
			//最初のノーツが来たときに曲を流す
			if (bgmflg == 0) {
				PlaySoundMem(rockBGM, DX_PLAYTYPE_LOOP, FALSE);
				bgmflg = 1;
				nxf = 1;
			}
			PlaySoundMem(bpm, DX_PLAYTYPE_BACK, TRUE);
			nf[maxn + 1] = 1;	//ループフラグ
			nx[i] = 200;	//初期位置に戻す
			nf[i] = 0;
		}
		if (nf[i] == 1 || nf[maxn] == 1 && bcnt != 255) {
			bcnt++;	//透明度用カウント
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (bcnt));
			DrawLine(nx[maxn], 800, nx[maxn], 850, 0x00FF00, 8);
			DrawLine(1280 - nx[maxn], 800, 1280 - nx[maxn], 850, 0x00FF00, 8);
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

	if (hf == 1 && (dc++) < 40) {
		DrawGraph(540, 730, P[(dc) / 4 % 4], TRUE);
	}
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
		if (min > nx[i] && nx[i] != 200) {
			min = nx[i];
		}
	}

	return min;
}