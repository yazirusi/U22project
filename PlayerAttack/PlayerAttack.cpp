#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"

int ax;
int pa;
int apex;
/***************************************
*ÉvÉåÉCÉÑÅ[ÇÃçUåÇ
***************************************/
void PlayerAttack() {

	static int af;
	ax = p_x * 40;

	if (g_KeyFlg & PAD_INPUT_2) {
		af = 1;
	}
	if (af == 1 && g_StageData[0][17][(ax + pa + px) / 40 + 1] != 1) {
		//if (af == 1 && (ax + pa + px) / 40 + 1 != 10) {
		DrawBox(40 + pa + 40+apex, p_y * 40, 40 + 80 + pa+apex, p_y * 40 + 40, 0x22aaaa, TRUE);
		pa += 2;
	}
	else {
		pa = 0;
		af = 0;
	}
	if (pa == 120) {
		af = 0;
		pa = 0;
		apex = 0;
	}
	if ((ax + pa + 40) / 40 == 4) {
		printf("a");
	}
}