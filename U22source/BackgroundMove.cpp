#include "DxLib.h"
#include "images.h"
#include "BackgroundMove.h"
#include "player.h"
#include "map.h"
#include "main.h"
//#include "map.h"

int spd = 2;         //スクロールスピード
int scrool = 0;  //表示位置

/***********************xxxxxxxxxxxxx
*背景のスクロール
***********************/
void BackScrool() {
	DrawGraph(0, 0, Backimg3, TRUE);

	//背景をスクロール表示
	SetDrawArea(0, 0, 1280, 850);
	DrawGraph(spd % 1280 + 1280, 0, Backimg2, TRUE);
	DrawGraph(spd % 1280, 0, Backimg2, TRUE);
	DrawGraph(scrool % 1280 + 1280, 0, Backimg, TRUE);
	DrawGraph(scrool % 1280, 0, Backimg, TRUE);
	//プレイヤーがスタートからどこまで離れたか
	if (player.px > (1280 * (sx_c - 1))) {
		DrawGraph(scrool % (1280 * sx_c) + (1280 * sx_c), 0, Backimg4, TRUE);
		DrawGraph(scrool % (1280 * sx_c), 0, Backimg4, TRUE);
	}

	//ボス戦のドア部分を黒くする
	if (sx < (-1280 * sx_c) + 300) {
		int x = WIDTH + sx + (1280 * sx_c) - 300;
		DrawBox(x, 620, x + 80, 720, 0x000000, TRUE);
	}


	SetDrawArea(0, 0, 1280, 850);

}
/***********************
*スクロールの初期化
***********************/
void ScroolInit() {
	spd = 2;
	scrool = 0;
	msx = 0;
	sx = 0;
}