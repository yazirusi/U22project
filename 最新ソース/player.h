#pragma once
#include "DxLib.h"

//変数の宣言
extern int p_x, p_y, sp_y;  //プレイヤーの座標
extern int px, py, spy;	//プレイヤー描画の座標
extern int pcnt;	//イラストのカウント
/*int g_KeyFlg;  //入力キー情報
int	g_OldKey;  // 前回の入力キー
int	g_NowKey;	// 今回の入力キー*/

//ジャンプ変数
extern int jlong;    //押した長さでジャンプ力を変える
extern int jlength;    //一回SHIFTを離してから入力を受け付ける
extern int jflag;	//ジャンプフラグ
extern int hozonY;    //ジャンプした瞬間の座標
extern int jy;        //ジャンプした瞬間の座標
extern int tempY;
extern int dflag;	//下降フラグ

//関数の宣言
void PlayerMove();	//プレイヤー移動
int CheckHitBlock();	//ブロックとの当たり判定