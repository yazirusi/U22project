#include "DxLib.h"
#include "images.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "GameTitle.h"
void DrawGameTitle(void) {
	DrawGraph(0, 0, Titleimg, TRUE);
	if (g_KeyFlg & PAD_INPUT_2) {
		g_GameState = 1;	// �Q�[�����C��������

	}
	
	SetFontSize(45);
		DrawString(250, 550, "B �{ �^ �� �� �� �� �� �� �� �� ��", 0x0000ff);

		
}