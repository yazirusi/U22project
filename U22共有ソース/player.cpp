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

		//���[�ɗ�����~�܂�
		if (msx < 0) {
			//�u���b�N�Ƃ̓����蔻��
			if (CheckHitBlock(1) == 0) {
				msx += 2;
				player.px -= 2;

				//�U���`����W�̔�����
				for (int ai = 0; ai < 5; ai++) {
					if (player.af[ai] == 1) {
						player.apx[0] += 2;
					}
				}

				//�}�b�v�`�b�v�̍��W
				if (player.px % 40 == 38) {
					g_StageData[0][player.p_y][player.p_x - 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}
			}
		}
	}

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		
		//�u���b�N�Ƃ̓����蔻��
		if (CheckHitBlock(2) == 0) {
			msx -= 2;
			player.px += 2;

			//�}�b�v�`�b�v�̍��W
			if (player.px % 40 == 0) {
				g_StageData[0][player.p_y][player.p_x + 1] = 2;
				g_StageData[0][player.p_y][player.p_x] = 0;
				player.p_x = player.px / 40;
			}
		}

		//�v���C���[�̉摜�i�E�����j
		DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
	}
	else {
		//�E�����ŗ����~�܂��Ă�Ƃ�
		DrawExtendGraph(-5, player.py - 80 , 191, player.py + 65, p[0], TRUE);
	}


	//�W�����v�t���O�i�X�y�[�X�L�[�j����Ƀu���b�N����������W�����v�ł��Ȃ�
	if (g_KeyFlg & PAD_INPUT_10 && player.jflag == 0 && CheckHitBlock(3) == 0) {
		player.jflag = 1;	//�W�����v�t���O
		player.hozonY = player.py;	//�W�����v�����u�Ԃ̍��W
		player.spy = player.py;		//640
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
			if (CheckHitBlock(3) == 1) {
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
			if (CheckHitBlock(4) == 1) {
				player.dflag = 0;
				player.jflag = 0;
			}
		}
	}

	//���R��������
	if (player.jflag == 0 && CheckHitBlock(5) == 1) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//������u�Ԃ̍��W
		player.spy = player.py;
		player.sp_y = player.p_y;
	}
	DrawFormatString(50, 220, 0xffffff, "%d", player.jflag);
}

/***********************************
*�v���C���[�ƃu���b�N�̓����蔻��
*����
*�P�F���ړ��̓����蔻��
*�Q�F�E�ړ��̓����蔻��
*�R�F�㏸���̓���̃u���b�N
*�S�F���~���̉��̑���
*�T�F���ړ�������̑���
*�߂�l 1:�u���b�N�ɓ�����
***********************************/
int CheckHitBlock(int j) {

	//���ړ�
	if (j == 1) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 && x * 40 + 40 == player.px
					&& ((y * 40 <= player.py && y * 40 + 40 >= player.py)	//�����g
						|| (y * 40 < player.py - 40 && y * 40 + 40 > player.py - 40))) {	//�㔼�g
					return 1;
				}
			}
		}
	}

	//�E�ړ�
	if (j == 2) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 && x * 40 == player.px + 40
					&& ((y * 40 <= player.py && y * 40 + 40 >= player.py)	//�����g
					|| (y * 40 < player.py - 40 && y * 40 + 40 > player.py - 40))) {	//�㔼�g
					return 1;
				}
			}
		}
	}

	//�㏸��(����̓����蔻��)
	if (j == 3) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1
					&& (y * 40 <= player.py - 40 && y * 40 + 40 >= player.py - 40)
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)
						|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {
					return 1;
				}
			}
		}
	}

	//���~��(����̓����蔻��)
	if (j == 4) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 
					&& (y * 40 <= player.py + 40 && y * 40 + 40 >= player.py + 40)
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)
					|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {

					//�v���C���[�̈ʒu
					player.py = y * 40 - 40;
					return 1;
				}
			}
		}
	}

	//���R����
	if (j == 5) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 0
					&& (y * 40 == player.py + 40)
					&& (x * 40 == player.px)) {
					return 1;
				}
			}
		}
	}

	return 0;
}