#include "DxLib.h"
#include "images.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "player.h"
#include "GameOver.h"


void DrawGameOver(void) {
	DrawGraph(0, 0, GameOverimg, TRUE);
	if (g_KeyFlg & PAD_INPUT_1) {
		g_GameState = 0;	// ゲームメイン処理へ

	}

	SetFontSize(40);
	DrawString(400, 400, "\"タイトル画面へ\"\nAボタンを押してください", 0xffffff);
}