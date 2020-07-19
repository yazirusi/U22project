#pragma once
#include "DxLib.h"

//notes関数の変数
extern int nx[100]; //ノーツの座標
extern int nf[100];//ノーツごとのフラグ
extern int nbf[100];//ノーツごとの出現フラグ
extern int mcnt[100];//メトロノーム
extern int mcntf[100];//メトロノーム用フラグ
extern int bcnt;	//ブレンドのカウント
extern int hf;	//パーフェクト判定
extern int conbo;

//notesjudge関数の変数
extern int dc;	//表示する時間のカウント

void notes();	//ノーツ描画関数
void notesjudge();	//ノーツ判定描画
int nxmin(int max);
