#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"

int pa:
/***************************************
*ÉvÉåÉCÉÑÅ[ÇÃçUåÇ
***************************************/
void PlayerAttack(void) {

	static int af;
	static int ax = p_x * 40;

	if (g_KeyFlg & PAD_INPUT_2 == 1) {
		af = 1;
		DrawBox(ax + pa, p_y * 40, ax + 40 + pa, p_y * 40 + 40, 0x22aaaa, TRUE);
	}
	if (af == 1) {
		pa += 2;
	}
	if (pa == 80) {
		af = 0;
		pa = 0;
	}
}