#include "DxLib.h"
#include "images.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "player.h"
#include "GameOver.h"
#include "sounds.h"


void DrawGameOver(void) {
	DrawGraph(0, 0, GameOverimg, TRUE);
	if (g_KeyFlg & PAD_INPUT_1) {
		StopSoundMem(GObgm);
		PlaySoundMem(dese, DX_PLAYTYPE_BACK, TRUE);
		g_GameState = 0;	// ゲームメイン処理へ
		PlaySoundMem(Titlebgm, DX_PLAYTYPE_BACK, TRUE);
	}

	SetFontSize(40);
	DrawString(400, 400, "\"タイトル画面へ\"\nAボタンを押してください", 0xffffff);
}