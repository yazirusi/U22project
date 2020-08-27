#include "DxLib.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "BossStage.h"
#include "pause.h"

void Pause(void) {
	if (g_KeyFlg & PAD_INPUT_8) {
		g_GameState = 2;
	}
}