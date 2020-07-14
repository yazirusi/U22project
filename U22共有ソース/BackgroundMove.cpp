#include "DxLib.h"
#include "images.h"
#include "BackgroundMove.h"
#include "player.h"
//#include "map.h"

int spd = 2;         //スクロールスピード
int scrool = 0;  //表示位置

/***********************
*背景のスクロール
***********************/
void BackScrool(){

	//背景をスクロール表示
	SetDrawArea(0, 0, 1280, 850);
	DrawGraph(scrool % 1280 + 1280,0, Backimg,TRUE);
	DrawGraph(scrool % 1280,0, Backimg, TRUE);
	SetDrawArea(0, 0, 1280, 850);

}