#include "DxLib.h"
#include "images.h"
#include "BackgroundMove.h"
#include "player.h"
//#include "map.h"

//
int spd;         //スクロールスピード
int scrool = 0;  //表示位置

/***********************
*背景のスクロール
***********************/
void BackScrool(){
	//プレイヤーが進んでいるかどうかの判定
	//進んで入れば spdに2を代入　そうでなければ 0を代入
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		if (CheckHitBlock(2,0) == 0) {
			spd = 2;
			scrool -= spd ;
		}
	}
	else {
		spd = 0;
	}
	//プレイヤーが進んでいるかどうかの判定
	//進んで入れば spdに2を代入　そうでなければ 0を代入
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (CheckHitBlock(1,0) == 0) {
			spd = 2;
			scrool += spd ;
		}
	}
	else {
		spd = 0;
	}
	if (scrool > 0) {
		scrool = 0;
	}
	//背景をスクロール表示
	SetDrawArea(0, 0, 1280, 850);
	DrawGraph(scrool % 1280 + 1280,0, Backimg,TRUE);
	DrawGraph(scrool % 1280,0, Backimg, TRUE);
	SetDrawArea(0, 0, 1280, 850);


}