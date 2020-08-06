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
		g_GameState = 0;	// �Q�[�����C��������

	}

	SetFontSize(40);
	DrawString(400, 400, "\"�^�C�g����ʂ�\"\nA�{�^���������Ă�������", 0xffffff);
}