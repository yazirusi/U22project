#include "DxLib.h"
#include "key.h"
#include "main.h"
#include "GameInit.h"
#include "BossStage.h"
#include "sousa.h"

void Sousa(void) {
	SetFontSize(40);
	DrawString(0, 0,
		"             +----------[�������]----------+\n�E�A�i���O�X�e�B�b�N���E�ɓ|���ƉE���Ɉړ�����\n�E�A�i���O�X�e�B�b�N�����ɓ|���ƍ����Ɉړ�����\n�ER1�ōU��\n�EL1�ŉἨQ�[�W�𒙂߂�\n�EA�{�^���ŃW�����v\n�E���̊J���Ă�ꏊ��X�{�^�������ă{�X�X�e�[�W��",
		GetColor(255, 255, 255));
	if (g_KeyFlg & PAD_INPUT_4) {
		g_GameState = 0;
	}
	//else if (g_KeyFlg & PAD_INPUT_3) {
	//	g_GameState = 4;
	//}
}