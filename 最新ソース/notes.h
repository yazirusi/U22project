#pragma once
#include "DxLib.h"

//notes関数の変数
//notesの構造体
struct NOTES
{
	int nx[100]; //ノーツの座標
	int nf[100];//ノーツごとの押したときのフラグ
	int nbf[100];//ノーツごとの出現フラグ 0:表示しない 1:プレイヤーの行動ノーツ 2:敵とプレイヤーの行動ノーツ
	int mcnt[100];//メトロノーム
	int mcntf[100];//メトロノーム用フラグ
	int bcnt = 0;	//ブレンドのカウント
	int hf = 0;	//パーフェクト判定
	int conbo = 0;	//コンボ数
	int encnt = 0;
	const int maxn = 20;	//表示するノーツ数の数
	int nxf = 0;		//ループのフラグ
	int bgmflg = 0;		//bgmを流すフラグ
	int notesInitflg = 0;	//初期化のフラグ
	int min = 0;		//ノーツの座標の最小値
	int nxbf = 0;
	int sbf = 0;
	int beatcnt = 0;	//77小節
	double f = 0.0;
	int dc = 0;	//表示する時間のカウント
}; extern NOTES note;
/*extern int nx[100]; //ノーツの座標
extern int nf[100];//ノーツごとのフラグ
extern int nbf[100];//ノーツごとの出現フラグ
extern int mcnt[100];//メトロノーム
extern int mcntf[100];//メトロノーム用フラグ
extern int bcnt;	//ブレンドのカウント
extern int hf;	//パーフェクト判定
extern int conbo;*/

void notes();	//ノーツ描画関数
void notesjudge();	//ノーツ判定描画
int nxmin(int max);	//表示されているノーツの中の最小値を調べる
int judgeinit(int i);	//判定した後ノーツを初期化する関数
int notesinit(int i);	//ノーツ関数で使う変数の初期化