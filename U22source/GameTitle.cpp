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
		g_GameState = 1;	// �Q�[�����C��������

	}

	if (g_KeyFlg & PAD_INPUT_4) {
		//StopSoundMem(rockBGM);
		g_GameState = 7;
	}
	SetFontSize(45);
		DrawString(250, 550, "B �{ �^ �� �� �� �� �� �� �� �� ��", 0x0000ff);
	SetFontSize(45);
		DrawString(405, 620, "Y �{�^���ŁA�������", 0x0000ff);
}