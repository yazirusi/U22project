#pragma once
#include "DxLib.h"

//プレイヤーの構造体
struct PLAYER
{
	//player関数で使う変数
	int p_x = 0, p_y = 0, sp_y = 0;  //マップチップ上のプレイヤーの座標
	int px = 0, py = 0, spy = 0;	//プレイヤー描画の座標
	int pcnt = 0;	//イラストのカウント
	int jlong = 0;    //押した長さでジャンプ力を変える
	int jlength = 0;    //一回SHIFTを離してから入力を受け付ける
	int jflag = 0;	//ジャンプフラグ
	int hozonY = 0;    //ジャンプした瞬間の座標
	int tempY = 0;	//ジャンプ時に使う入れ替え処理の変数
	int dflag = 0;	//下降フラグ
	int direF = 0;	//向きフラグ 0:右向き　1:左向き

	//プレイヤーのステータス
	int hp = 100;	//HP

	//playerattack用変数(最大５個同時描画)
	int af[5] = { 0,0,0,0,0 };	//攻撃フラグ	0:なし 1:攻撃
	int ax = 0;
	int pa[5] = { 0,0,0,0,0 };
	int ay[5] = { 0,0,0,0,0 };
	int apx[5] = { 0,0,0,0,0 };
	int adireF[5] = { 0,0,0,0,0 };	//0：右向き　1：左向き
	int ajudge[5] = { 0,0,0,0,0 };	//0：パーフェクト	1:グレート
	int acolor[5] = { 0xFF0000,0xFFFF00 };	//添え字　0:赤(perfect)　1:黄色(great)

}; extern PLAYER player;

//関数の宣言
void PlayerMove();	//プレイヤー移動
int CheckHitBlock(int j,int a);	//ブロックとの当たり判定