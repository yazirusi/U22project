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
#include "GameInit.h"

//player�\����
PLAYER player;

/*******************************
*�v���C���[�̈ړ�����
********************************/
void PlayerMove() {

	//�v���C���[�̃X�e�[�^�X�`��
	SetFontSize(24);
	DrawFormatString(10, 770, 0xffffff, "HP");
	SetFontSize(16);
	//DrawFormatString(30, 200, 0xffffff, "px%d", player.px);
	//DrawFormatString(30, 230, 0xffffff, "py%d", player.py);
	//DrawFormatString(30, 260, 0xffffff, "jflag%d", player.jflag);

	//sx-3540 x1056 1136 y 600 680	80 80

	//HP�Q�[�W�̕`��
	DrawGraph(50, 750, hpg, TRUE);
	//�U���Q�[�W�̕`��
	DrawGraph(50, 790, ag, TRUE);

	//�Q�[�W�̊���
	static float hpgauge, colgauge;

	hpgauge = (float)glen * ((float)player.hp / (float)100);

	if (player.hp <= 0) {
		hpgauge = 0.0;
	}

	if (player.col > 100) {
		player.col = 100;
	}

	colgauge = (float)glen * ((float)player.col / (float)100);

	//HP�Q�[�W�̌���
	DrawBox(65 + (int)hpgauge, 769, 283, 799, 0x000000, TRUE);

	//�U���Q�[�W�̌���
	DrawBox(65 + (int)colgauge, 810, 283, 839, 0x000000, TRUE);

	//�v���C���[�摜�̕`��ʒu
	if (player.px >= 640 && player.px <= (1280 * sx_c) + 640 && g_stage == 0) {
		player.ix = 595;
		player.iy = player.py - 80;
	}
	else if ( player.px >= (1280 * sx_c) + 640 ) {
		player.ix = player.px - ((1280 * sx_c) + 640) + 595;
		player.iy = player.py - 80;
	}
	else {
		player.ix = player.px - 45;
		player.iy = player.py - 80;
	}

	//�v���C���[�̓����蔻��`��
	DrawBox(player.px + sx, player.py - 40, player.px + 40 + sx, player.py + 40, 0xFF0000, FALSE);

	//hp�O�ȉ��Ŏ��S
	if (player.hp <= 0) {
		//���ʃC���X�g
		if (player.direF == 0) {	//�E����
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pd[player.pcnt++ / 16 % 4], TRUE);
		}
		if (player.direF == 1) {	//������
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pd[player.pcnt++ / 16 % 4 + 4], TRUE);
		}
		if (player.pcnt == 64) {
			StopSoundMem(rockBGM);

			g_GameState = 3;   //�Q�[���I�[�o�[��ʂ�
		}
		return;
	}

	//�G�̍U����H�������_�ŗp�J�E���g�����Z����
	if (player.hit == true) {
		player.hitcnt++;
	}
	//���G���Ԃ��؂ꂽ��
	if (player.hitcnt == player.invit) {
		player.hit = false;
		player.hitcnt = 0;
	}
	//���ړ�
	if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0
		|| CheckHitKey(KEY_INPUT_LEFT) == 1) && player.at[0] <= 0) {
		player.left = true;
		//���[�ɗ���܂�
		if (msx < 0) {
			//�u���b�N�Ƃ̓����蔻��
			if (CheckHitBlock(1, 0) == 0) {
				msx += player.speed;		//�}�b�v�`�b�v�̃X�N���[��
				player.px -= player.speed;	//�v���C���[�̍��W
				if (sx < 0 && player.px < (1280 * sx_c) + 640 ) {
					spd += player.speed - 1;
					scrool += player.speed;	//�C���X�g�̃X�N���[��
					sx += player.speed;
				}
			}
		}
		player.direF = 1;
		//�U����H�������_�ł�����
		if ((player.hitcnt % 10) < 5 && player.jflag == 0 && player.at[0] <= 0) {
			//�v���C���[�̉摜�i�������j
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, p[player.pcnt++ / 8 % 5 + 7], TRUE);
		}
	}
	else {
		player.left = false;
	}
	//�E�ړ�
	if (((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0
		|| CheckHitKey(KEY_INPUT_RIGHT) == 1) && player.at[0] <= 0) {
		player.right = true;
		//�u���b�N�Ƃ̓����蔻�聕���X�{�X��Ȃ��ǂ�����
		if (CheckHitBlock(2, 0) == 0) {
			if (player.px > 638 && g_stage == 1) {
			}
			else {
				msx -= player.speed;		//�}�b�v�`�b�v�̃X�N���[��
				player.px += player.speed;	//�v���C���[�̍��W
				if (player.px > 640 && (sx > (-1280 * sx_c)) && g_stage == 0) {
					spd -= player.speed - 1;
					scrool -= player.speed;	//�C���X�g�̃X�N���[��
					sx -= player.speed;
				}
			}
		}

		player.direF = 0;
		//�U����H�������_�ł�����
		if ((player.hitcnt % 10) < 5 && player.jflag == 0 && player.at[0] <= 0) {
			//�v���C���[�̉摜�i�E�����j
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, p[player.pcnt++ / 8 % 5 + 1], TRUE);
		}
	}
	else {
		player.right = false;
	}

	if (player.right == false && player.left == false && player.at[0] <= 0 && player.jflag == 0) {
		//�U����H�������_�ł�����
		if ((player.hitcnt % 10) < 5) {
			//�����~�܂��Ă���Ƃ�
			if (player.direF == 0) {	//�E����
				DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, p[0], TRUE);
			}
			if (player.direF == 1) {	//������
				DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, p[6], TRUE);
			}
		}
	}
	if (player.at[0] > 0) {
		//�U���C���X�g
		if ((player.hitcnt % 10) < 5 && player.direF == 0) {	//�E����
			DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 135, pa[player.pcnt++ / 8 % 2], TRUE);
		}
		if ((player.hitcnt % 10) < 5 && player.direF == 1) {	//������
			DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 135, pa[player.pcnt++ / 8 % 2 + 2], TRUE);
		}

		//�U���C���X�g�̍Ō�̃V���E�g���Ă����Ԃ𑱂�����
		if (player.pcnt > 8) {
			player.pcnt = 8;
		}
	}

	//���R��������
	if (player.jflag == 0 && CheckHitBlock(4, 0) == 0) {
		player.jflag = 1;
		player.dflag = 1;
		player.hozonY = player.py;	//������u�Ԃ̍��W
		player.spy = player.py;
		player.sp_y = player.p_y;
	}

	//�W�����v�t���O�i�X�y�[�X�L�[�j����Ƀu���b�N����������W�����v�ł��Ȃ�
	if (g_KeyFlg & PAD_INPUT_1 && CheckHitBlock(3, 0) == 0 && player.jflag == 0 && player.at[0] <= 0) {
		PlaySoundMem(jpse, DX_PLAYTYPE_BACK, TRUE);
		player.jflag = 1;	//�W�����v�t���O
		player.hozonY = player.py;	//�W�����v�����u�Ԃ̍��W
		player.spy = player.py;		//640
		player.sp_y = player.p_y;	//17
		player.py = player.py - 17;	//�W�����v�̉����x
		player.pcnt = 0;
	}

	//�W�����v�����i�������j
	if (player.jflag == 1) {
		//�W�����v�̍��W�̓���
		player.tempY = player.py;
		player.py += (player.py - player.hozonY) + 1;
		player.hozonY = player.tempY;
		player.p_y = player.py / 40;

		//�㏸���Ă�Ƃ�
		if (player.py - player.hozonY <= 0 && player.p_y != player.sp_y) {
			//����Ƀu���b�N���������ꍇ
			if (CheckHitBlock(3,0) == 1) {
				player.hozonY = player.py;	//������u�Ԃ̍��W
				player.spy = player.py;
				player.sp_y = player.p_y;
			}

			//�W�����v�C���X�g
			if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//�E����
				DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[0], TRUE);
			}
			if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//������
				DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[3], TRUE);
			}

			/*//�W�����v���Ȃ���ړ�������̃u���b�N
			if (g_StageData[0][player.p_y + 1][player.p_x] != 1)
				g_StageData[0][player.p_y + 1][player.p_x] = 0;

			g_StageData[0][player.p_y][player.p_x] = 2;*/
		}

		//���~���Ă�Ƃ�
		if (player.py - player.hozonY > 0 && player.p_y != player.sp_y - 6 || player.dflag == 1) {
			player.dflag = 1;
			/*if (g_StageData[0][player.p_y - 1][player.p_x] != 1)
				g_StageData[0][player.p_y - 1][player.p_x] = 0;
			
			if (g_StageData[0][player.p_y][player.p_x] != 1)
				g_StageData[0][player.p_y][player.p_x] = 2;*/

			//�^���Ƀu���b�N����������W�����v�����I��
			if (CheckHitBlock(4,0) == 1) {
				player.dflag = 0;
				player.jflag = 0;
			}

			//�W�����v�C���X�g
			if (player.py - player.hozonY < 9) {
				if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//�E����
					DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[1], TRUE);
				}
				if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//������
					DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[4], TRUE);
				}
			}
			else {
				if ((player.hitcnt % 10) < 5 && player.direF == 0 && player.at[0] <= 0) {	//�E����
					DrawExtendGraph(player.ix, player.iy, player.ix + 196, player.iy + 145, pj[2], TRUE);
				}
				if ((player.hitcnt % 10) < 5 && player.direF == 1 && player.at[0] <= 0) {	//������
					DrawExtendGraph(player.ix - 65, player.iy, player.ix + 196 - 65, player.iy + 145, pj[5], TRUE);
				}
			}
		}
	}
	//�U��(R1����������)
	if (g_KeyFlg & PAD_INPUT_6 && player.at[0] <= 0 && AttackExtend == 0) {
		//�U���t���O(�ő�T�����`��)
		for (int ai = 0; ai < 5; ai++) {
			if (player.af[ai] == 0) {
				player.af[ai] = 1;
				player.ay[ai] = player.py - 40;
				player.apx[ai] = player.px;
				player.adireF[ai] = player.direF;
				player.ajudge[ai] = 0;
				player.at[ai] = 20;
				imgflg = true;
				break;
			}
		}
		player.pcnt = 5;
	}
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
		/*for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 && x * 40 + 40 == player.px	//x���W�̓����蔻��
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y���W�̔���(�����g)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//�㔼�g
					return 1;
				}
			}
		}*/
		if (g_StageData[g_stage][player.py / 40][(player.px - 1) / 40] == 1) {
			return 1;
		}
		if (g_StageData[g_stage][(player.py - 40) / 40][(player.px - 1) / 40] == 1) {
			return 1;
		}
	}

	//�E�ړ�
	if (j == 2) {
		/*for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[0][y][x] == 1 && x * 40 == player.px + 40	//x���W�̓����蔻��
					&& ((y * 40 < player.py + 40 && y * 40 + 40 > player.py)	//y���W�̔���(�����g)
					|| (y * 40 < player.py && y * 40 + 40 > player.py - 40))) {	//�㔼�g

					return 1;
				}
			}
		}*/
		if (g_StageData[g_stage][player.py / 40][(player.px + 40) / 40] == 1) {
			return 1;
		}
		if (g_StageData[g_stage][(player.py - 40) / 40][(player.px + 40) / 40] == 1) {
			return 1;
		}
	}

	//�㏸��(����̓����蔻��)
	if (j == 3) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[g_stage][y][x] == 1
					&& (y * 40 <= player.py - 50 && y * 40 + 40 >= player.py - 50)//y���W
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x���W
						|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x���W
					return 1;
				}
			}
		}
		/*if (g_StageData[0][player.py / 40][player.px / 40] == 1) {
			return 1;
		}*/
	}

	//���~��(����̓����蔻��)
	if (j == 4) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[g_stage][y][x] == 1
					&& (y * 40 <= player.py + 40 && y * 40 + 40 >= player.py + 40)//y���W
					&& ((x * 40 <= player.px && x * 40 + 40 > player.px)//x���W
					|| (x * 40 < player.px + 40 && x * 40 + 40 >= player.px + 40))) {//x���W

					//�v���C���[�̈ʒu
					player.py = y * 40 - 40;
					return 1;
				}
			}
		}
		/*if ((g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40 - 1] == 1
		  || g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40] == 1)) {
			//�v���C���[�̈ʒu
			player.py = player.py - (player.py % 40);
			return 1;
		}*/
	}

	//���R����
	if (j == 5) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[g_stage][y][x] == 0
					&& (y * 40 == player.py + 40)//y���W
					&& (x * 40 < player.px + 40 && x * 40 + 40 < player.px ) ){//x���W
					return 1;
				}
			}
		}
		/*if (g_StageData[0][player.py / 40 + 1][(player.px + 40) / 40 - 1] != 1) {
			return 1;
		}*/
	}

	//�U��(�E����)
	if (j == 6) {
		for (int y = 0; y < MAPHEIGHT; y++) {
			for (int x = 0; x < MAPWIDTH; x++) {
				//�u���b�N�Ƃ̓����蔻��
				if (g_StageData[g_stage][y][x] == 1) {
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
				if (g_StageData[g_stage][y][x] == 1) {
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

/***********************************
*�v���C���[�̏�����
***********************************/
void PlayerInit() {
	//�}�b�v�`�b�v�ɍ��킹�č��W��ݒ肷��
	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[g_stage][y][x] == 2) {
				player.px = (x * 40);
				player.py = (y * 40);
			}
		}
	}
	player.hp = 100;
	player.pcnt = 0;	//�C���X�g�̃J�E���g
	player.jflag = 0;	//�W�����v�t���O
	player.hozonY = 0; //�W�����v�����u�Ԃ̍��W
	player.tempY = 0;	//�W�����v���Ɏg������ւ������̕ϐ�
	player.dflag = 0;	//���~�t���O
	player.direF = 0;	//�����t���O 0:�E�����@1:������
	player.right = false;	//�E�ړ��̃t���O false:�����Ȃ��@true:����
	player.left = false;	//���ړ��̃t���O false:�����Ȃ��@true:����
	player.jump = false;  //�W�����v�t���O false:�����Ȃ��@true:����
	player.hit = false;	//�G�̍U����H������t���O(�H����ē_�ł��Ă���Ԗ��G)
	player.hitcnt = 0;	//�_�ł�����J�E���g
	player.col = 0;
	/*protect = false;	//�h��t���O
	protecJudge = 0;	//�h��p�Ƀm�[�c�̔����ۑ�����*/
}