#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"
#include "PlayerAttack.h"

//player�\����
PLAYER player;

/*******************************
*�v���C���[�̈ړ�����
********************************/
void PlayerMove() {

	//���ړ�
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (g_StageData[0][player.p_y][player.p_x - 1] != 1 && g_StageData[0][player.p_y - 1][player.p_x - 1] != 1) {
			if (player.px > 0) {
				player.px -= 2;
				Enemy.Moveflg = 1;

				//�U���`����W�̔�����
				for (int ai = 0; ai < 5; ai++) {
					if (player.af[ai] == 1) {
						player.apx[0] += 2;
					}
				}
			}
			else {
				player.px = 40;
				g_StageData[0][player.p_y][player.p_x] = 0;
				g_StageData[0][player.p_y][player.p_x - 1] = 2;
				player.p_x -= 1;
				mx--;
			}
		}
	}

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		//�����蔻�菈��
		if (CheckHitBlock() != 1) {
			if (g_StageData[0][player.p_y][player.p_x] != 1 && player.px < 40) {
				player.px += 2;
				Enemy.Moveflg = 2;
			}
			else {
				//�ړ���ɕǂ����邩
				if (g_StageData[0][player.p_y][player.p_x + 1] != 1 && g_StageData[0][player.p_y - 1][player.p_x + 1] != 1) {
					player.px = 0;
					g_StageData[0][player.p_y][player.p_x + 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x += 1;
					mx++;
				}
			}
		}

		//�v���C���[�̉摜�i�E�����j
		DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
	}
	else {
		//�E�����ŗ����~�܂��Ă�Ƃ�
		DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[0], TRUE);
	}


	//�W�����v�t���O�i�X�y�[�X�L�[�j����Ƀu���b�N����������W�����v�ł��Ȃ�
	if (g_KeyFlg & PAD_INPUT_10 && player.jflag == 0 && ((player.px == 40 && g_StageData[0][player.p_y - 2][player.p_x] != 1) 
		|| (player.px < 40 && g_StageData[0][player.p_y - 2][player.p_x - 1] != 1))) {
		player.jflag = 1;	//�W�����v�t���O
		player.hozonY = player.py;	//�W�����v�����u�Ԃ̍��W
		player.spy = player.py;		//680
		player.sp_y = player.p_y;		//17
		player.py = player.py - 20;	//�W�����v�̉����x
	}
	//�W�����v�����i�������j
	if (player.jflag == 1) {

		//�W�����v�̍��W�̓���
		player.tempY = player.py;
		player.py += (player.py - player.hozonY) + 1;
		player.hozonY = player.tempY;

		player.p_y = player.py / 40;

		//�㏸���Ă�Ƃ�
		if (player.py - player.hozonY < 0 && player.p_y != player.sp_y) {
			//����Ƀu���b�N���������ꍇ
			if (g_StageData[0][player.p_y - 1][player.p_x] == 1 || player.px < 40 
				&& g_StageData[0][player.p_y - 1][player.p_x - 1] == 1) {
				player.hozonY = player.py;	//������u�Ԃ̍��W
				player.spy = player.py;
				player.sp_y = player.p_y;
			}

			//�W�����v���Ȃ���ړ�������̃u���b�N
			if (g_StageData[0][player.p_y + 1][player.p_x] != 1)
				g_StageData[0][player.p_y + 1][player.p_x] = 0;

			g_StageData[0][player.p_y][player.p_x] = 2;
		}

		//���~���Ă�Ƃ�
		if (player.py - player.hozonY > 0 && player.p_y != player.sp_y - 6 || player.dflag == 1) {
			player.dflag = 1;
			if (g_StageData[0][player.p_y - 1][player.p_x] != 1)
				g_StageData[0][player.p_y - 1][player.p_x] = 0;

			if (g_StageData[0][player.p_y][player.p_x] != 1)
				g_StageData[0][player.p_y][player.p_x] = 2;

			//�^���Ƀu���b�N����������W�����v�����I��
			if (g_StageData[0][player.p_y + 1][player.p_x] == 1 || player.px < 40 
				&& g_StageData[0][player.p_y + 1][player.p_x - 1] == 1) {
				if (player.py + 40 >= (player.p_y + 1) * 40) {
					player.py = -40 + (player.p_y + 1) * 40;
					player.dflag = 0;
					player.jflag = 0;
				}
			}
		}
	}

	//���R��������
	if (player.jflag == 0 && (g_StageData[0][player.p_y + 1][player.p_x] != 1 &&
		player.px < 40 && g_StageData[0][player.p_y + 1][player.p_x - 1] != 1)) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//������u�Ԃ̍��W
		player.spy = player.py;
		player.sp_y = player.p_y;
		//player.py = player.py - 20;	//�W�����v�̉����x
	}
}

/***********************************
*�v���C���[�ƃu���b�N�̓����蔻��
*�߂�l 1:�u���b�N�ɓ�����
***********************************/
int CheckHitBlock() {
	//���~���Ă�Ƃ�
	if (player.dflag == 1 && g_StageData[0][player.p_y + 1][player.p_x + 1] == 1 && player.px + 40 == 80) {
		return 1;
	}

	if (g_StageData[0][player.p_y][player.p_x + 1] == 1 && player.px + 40 == 80) {
		return 1;
	}
	return 0;
}