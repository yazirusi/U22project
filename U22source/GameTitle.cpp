#include "DxLib.h"
#include "images.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "GameTitle.h"
#include "sounds.h"
void DrawGameTitle(void) {
	DrawGraph(0, 0, Titleimg, TRUE);
	if (g_KeyFlg & PAD_INPUT_2) {
		PlaySoundMem(dese, DX_PLAYTYPE_BACK, TRUE);
		g_GameState = 1;	// ゲームメイン処理へ
		StopSoundMem(Titlebgm);

	}

	if (g_KeyFlg & PAD_INPUT_4) {
		//StopSoundMem(rockBGM);
		g_GameState = 7;
	}
	SetFontSize(45);
		DrawString(250, 550, "B ボ タ ン を 押 し て く だ さ い", 0x0000ff);
	SetFontSize(45);
		DrawString(405, 620, "Y ボタンで、操作説明", 0x0000ff);
}