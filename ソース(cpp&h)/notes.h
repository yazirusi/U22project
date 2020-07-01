#pragma once
#include "DxLib.h"

//notes関数の変数
extern int nx[10]; //ノーツの座標
extern int nf[10];//ノーツごとのフラグ
extern int bcnt;	//ブレンドのカウント
extern int hf;	//パーフェクト判定

/*//BPMの構造体
extern struct BPM {
};
struct BPM bpm;
*/
//notesjudge関数の変数
extern int dc;	//表示する時間のカウント

void notes();	//ノーツ描画関数
void notesjudge();	//ノーツ判定描画