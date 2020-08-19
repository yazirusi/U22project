#include "DxLib.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "BossStage.h"
#include "pause.h"

void Pause(void) {
	//SetDrawScreen(DX_SCREEN_BACK);
	///*プレイヤーの操作説明*/
	//printf("+----------[操作説明]----------+\n");
	//printf("・アナログスティックを右に倒すと右側に移動する\n");
	//printf("・アナログスティックを左に倒すと左側に移動する\n");
	SetFontSize(40);
	DrawString(0, 0, "             +----------[操作説明]----------+\n・アナログスティックを右に倒すと右側に移動する\n・アナログスティックを左に倒すと左側に移動する\n・R1で攻撃\n・L1で火力ゲージを貯める\n・Aボタンでジャンプ\n・扉の開いてる場所でXボタンをしてボスステージへ",  GetColor(255, 255, 255));
	/*SetFontSize(20);
	DrawString(0, 10, "・アナログスティックを右に倒すと右側に移動する", GetColor(255, 255, 255));*/

	//ScreenFlip();
	if (g_KeyFlg & PAD_INPUT_4) {
		g_GameState = 2;
	}
	//else if (g_KeyFlg & PAD_INPUT_3) {
	//	g_GameState = 4;
	//}
}