#pragma once
#include "DxLib.h"

//プレイヤーの構造体
struct PLAYER
{
	//player関数で使う変数
	int p_x, p_y, sp_y;  //マップチップ上のプレイヤーの座標
	int px, py, spy;	//プレイヤー描画の座標
	int pcnt;	//イラストのカウント
	int jlong;    //押した長さでジャンプ力を変える
	int jlength;    //一回SHIFTを離してから入力を受け付ける
	int jflag;	//ジャンプフラグ
	int hozonY;    //ジャンプした瞬間の座標
	int tempY;	//ジャンプ時に使う入れ替え処理の変数
	int dflag;	//下降フラグ

	//playerattack用変数(最大５個同時描画)
	int af[5];	//攻撃フラグ	0:なし 1:攻撃
	int ax;
	int pa[5];
	int ay[5];
	int apx[5];
}; extern PLAYER player;

//関数の宣言
void PlayerMove();	//プレイヤー移動
int CheckHitBlock();	//ブロックとの当たり判定