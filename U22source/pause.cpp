#include "DxLib.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "BossStage.h"
#include "pause.h"
#include "sounds.h"

void Pause(void) {
	SetFontSize(32);
	DrawString(610, 350, "PAUSE", 0xFF33FF);

	if (g_KeyFlg & PAD_INPUT_8) {
		if (soundsf == true) {
			PlaySoundMem(rockBGM, DX_PLAYTYPE_BACK, FALSE);
		}
		g_GameState = 2;
	}
}