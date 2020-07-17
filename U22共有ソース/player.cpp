#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"
#include "PlayerAttack.h"
#include "BackgroundMove.h"
#include "sounds.h"

//player�\����
PLAYER player;

/*******************************
*�v���C���[�̈ړ�����
********************************/
void PlayerMove() {
	//���ړ�
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0
		|| CheckHitKey(KEY_INPUT_LEFT) == 1) {

		//���[�ɗ�����~�܂�
		if (msx < 0) {
			//�u���b�N�Ƃ̓����蔻��
			if (CheckHitBlock(1,0) == 0) {
				msx += 2;		//�}�b�v�`�b�v�̃X�N���[��
				player.px -= 2;	//�v���C���[�̍��W
				scrool += spd;	//�C���X�g�̃X�N���[��

				//�}�b�v�`�b�v�̍��W
				if (player.px % 40 == 38) {
					g_StageData[0][player.p_y][player.p_x - 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}
			}
		}
		player.direF = 1;
		//�v���C���[�̉摜�i�������j
		DrawExtendGraph(-5 - 65, player.py - 80, 191 - 65, player.py + 65, p[player.pcnt++ / 8 % 5 + 7], TRUE);
	}
	else {
		//�E�ړ�
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0 
			|| CheckHitKey(KEY_INPUT_RIGHT) == 1) {

			//�u���b�N�Ƃ̓����蔻��
			if (CheckHitBlock(2, 0) == 0) {
				msx -= 2;		//�}�b�v�`�b�v�̃X�N���[��
				player.px += 2;	//�v���C���[�̍��W
				scrool -= spd;	//�C���X�g�̃X�N���[��

				//�}�b�v�`�b�v�̍��W
				if (player.px % 40 == 0) {
					g_StageData[0][player.p_y][player.p_x + 1] = 2;
					g_StageData[0][player.p_y][player.p_x] = 0;
					player.p_x = player.px / 40;
				}
			}

			player.direF = 0;
			//�v���C���[�̉摜�i�E�����j
			DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[player.pcnt++ / 8 % 5 + 1], TRUE);
		}
		else {

			//�����~�܂��Ă���Ƃ�
			if (player.direF == 0) {	//�E����
				DrawExtendGraph(-5, player.py - 80, 191, player.py + 65, p[0], TRUE);
			}
			if (player.direF == 1) {	//������
				DrawExtendGraph(-5 - 65, player.py - 80, 191 - 65, player.py + 65, p[6], TRUE);
			}
		}
	}

	//�W�����v�t���O�i�X�y�[�X�L�[�j����Ƀu���b�N����������W�����v�ł��Ȃ�
	if (g_KeyFlg & PAD_INPUT_1 && player.jflag == 0 && CheckHitBlock(3,0) == 0) {
		PlaySoundMem(jpse, DX_PLAYTYPE_BACK, TRUE);
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
			if (CheckHitBlock(3,0) == 1) {
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
			if (CheckHitBlock(4,0) == 1) {
				player.dflag = 0;
				player.jflag = 0;
			}
		}
	}

	//���R��������
	if (player.jflag == 0 && CheckHitBlock(5,0) == 1) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//������u�Ԃ̍��W
		player.spy = player.py;
		player.sp_y = player.p_y;
	}

	//�v���C���[�̃X�e�[�^�X�`��
	SetFontSize(24);
	DrawFormatString(10, 770, 0xffffff, "���`�x�[�V�����F%d", player.hp);
	SetFontSize(16);

	DrawFormatString(50, 220, 0x000000, "px%d", player.px);//�f�o�b�O
	DrawFormatString(50, 250, 0x000000, "py%d", player.py);//�f�o�b�O
}

/***********************************
*�v���C���[�ƃu���b�N�̓����蔻��
*����
*��
*�P�F���ړ��̓����蔻��
*�Q�F�E�ړ��̓����蔻��
*�R�F�㏸���̓���̃u���b�N
*�S�F���~���̉��̑���
*�T�F���ړ�������̑���
*�U�F�E�����̍U���̓����蔻��	a�F�U���z��̓Y����
*�V�F�������̍U������			a:�U���z��̓Y����
*�߂�l 1:�u���b�N�ɓ�����
***********************************/
int CheckHitBlock(int j,int a) {

	//���ړ�
	if (j == 1) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 && x * 40 + 40 == player.px	//x���W�̓����蔻��
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y���W�̔���(�����g)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//�㔼�g
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
				if (g_StageData[0][y][x] == 1 && x * 40 == player.px + 40	//x���W�̓����蔻��
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y���W�̔���(�����g)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//�㔼�g
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
					&& (y * 40 <= player.py - 50 && y * 40 + 40 >= player.py - 50)//y���W
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x���W
						|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x���W
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
					&& (y * 40 <= player.py + 40 && y * 40 + 40 >= player.py + 40)//y���W
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x���W
					|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x���W

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
					&& (y * 40 == player.py + 40)//y���W
					&& (x * 40 == player.px)) {//x���W
					return 1;
				}
			}
		}
	}

	//�U��(�E����)
	if (j == 6) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1) {
					if (x * 40 < player.pa[a] + 80 + player.apx[a] && x * 40  + 40 > player.pa[a] + 40	+ player.apx[a]	//x���W�̓����蔻��
					&& y * 40 < player.ay[a] + 40 && y * 40 + 40 > player.ay[a]) {	//y���W�̓����蔻��
						return 1;
					}
				}
			}
		}
	}

	//�U��(������)
	if (j == 7) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1) {
					if (x * 40 < player.pa[a] + 0 + player.apx[a] && x * 40 + 40 > player.pa[a] - 40 + player.apx[a]	//x���W�̓����蔻��
						&& y * 40 < player.ay[a] + 40 && y * 40 + 40 > player.ay[a]) {	//y���W�̓����蔻��
						return 1;
					}
				}
			}
		}
	}

	return 0;
}