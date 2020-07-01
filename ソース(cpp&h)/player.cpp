#include "DxLib.h"
#include "player.h"
#include "map.h"
#include "images.h"
#include "key.h"

//�ϐ��̒�`
int p_x, p_y, sp_y;  //�v���C���[�̍��W
int px, py, spy;	//�v���C���[�`��̍��W
int pcnt;	//�C���X�g�̃J�E���g

//�W�����v�ϐ�
int jlong;    //�����������ŃW�����v�͂�ς���
int jlength;    //���SHIFT�𗣂��Ă�����͂��󂯕t����
int jflag;	//�W�����v�t���O
int hozonY;    //�W�����v�����u�Ԃ̍��W
int jy;        //�W�����v�����u�Ԃ̍��W
int tempY;
int dflag;	//���~�t���O

/*******************************
*�v���C���[�̈ړ�����
********************************/
void PlayerMove() {

	//���ړ�
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (g_StageData[0][p_y][p_x - 1] != 1 && g_StageData[0][p_y - 1][p_x - 1] != 1) {
			if (px > 0) {
				px -= 2;
			}
			else {
				px = 40;
				g_StageData[0][p_y][p_x] = 0;
				g_StageData[0][p_y][p_x - 1] = 2;
				p_x -= 1;
				mx--;
			}
		}
	}

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		//�����蔻�菈��
		if (CheckHitBlock() != 1) {
			if (g_StageData[0][p_y][p_x] != 1 && px < 40) {
				px += 2;
			}
			else {
				//�ړ���ɕǂ����邩
				if (g_StageData[0][p_y][p_x + 1] != 1 && g_StageData[0][p_y - 1][p_x + 1] != 1) {
					px = 0;
					g_StageData[0][p_y][p_x + 1] = 2;
					g_StageData[0][p_y][p_x] = 0;
					p_x += 1;
					mx++;
				}
			}
		}

		//�v���C���[�̉摜�i�E�����j
		DrawExtendGraph(-5, py - 80, 191, py + 65, p[pcnt++ / 8 % 5 + 1], TRUE);
	}
	else {
		//�E�����ŗ����~�܂��Ă�Ƃ�
		DrawExtendGraph(-5, py - 80, 191, py + 65, p[0], TRUE);
	}


	//�W�����v�t���O�i�X�y�[�X�L�[�j����Ƀu���b�N����������W�����v�ł��Ȃ�
	if (g_KeyFlg & PAD_INPUT_10 && jflag == 0 && ((px == 40 && g_StageData[0][p_y - 2][p_x] != 1) || (px < 40 && g_StageData[0][p_y - 2][p_x - 1] != 1))) {
		jflag = 1;	//�W�����v�t���O
		hozonY = py;	//�W�����v�����u�Ԃ̍��W
		spy = py;		//680
		sp_y = p_y;		//17
		py = py - 20;	//�W�����v�̉����x
	}
	//�W�����v�����i�������j
	if (jflag == 1) {

		//�W�����v�̍��W�̓���
		tempY = py;
		py += (py - hozonY) + 1;
		hozonY = tempY;

		p_y = py / 40;

		//�㏸���Ă�Ƃ�
		if (py - hozonY < 0 && p_y != sp_y) {
			//����Ƀu���b�N���������ꍇ
			if (g_StageData[0][p_y - 1][p_x] == 1 || px < 40 && g_StageData[0][p_y - 1][p_x - 1] == 1) {
				hozonY = py;	//������u�Ԃ̍��W
				spy = py;
				sp_y = p_y;
			}

			//�W�����v���Ȃ���ړ�������̃u���b�N
			if (g_StageData[0][p_y + 1][p_x] != 1)
				g_StageData[0][p_y + 1][p_x] = 0;

			g_StageData[0][p_y][p_x] = 2;
		}

		//���~���Ă�Ƃ�
		if (py - hozonY > 0 && p_y != sp_y - 6 || dflag == 1) {
			dflag = 1;
			if (g_StageData[0][p_y - 1][p_x] != 1)
				g_StageData[0][p_y - 1][p_x] = 0;

			if (g_StageData[0][p_y][p_x] != 1)
				g_StageData[0][p_y][p_x] = 2;

			//�^���Ƀu���b�N����������W�����v�����I��
			if (g_StageData[0][p_y + 1][p_x] == 1 || px < 40 && g_StageData[0][p_y + 1][p_x - 1] == 1) {
				if (py + 40 >= (p_y + 1) * 40) {
					py = -40 + (p_y + 1) * 40;
					dflag = 0;
					jflag = 0;
				}
			}
		}
	}

	//���R��������
	if (jflag == 0 && (g_StageData[0][p_y + 1][p_x] != 1 && px < 40 && g_StageData[0][p_y + 1][p_x - 1] != 1)) {
		jflag = 1;
		dflag = 1;
		hozonY = py;	//������u�Ԃ̍��W
		spy = py;
		sp_y = p_y;
		//py = py - 20;	//�W�����v�̉����x
	}
}

/***********************************
*�v���C���[�ƃu���b�N�̓����蔻��
*�߂�l 1:�u���b�N�ɓ�����
***********************************/
int CheckHitBlock() {
	//���~���Ă�Ƃ�
	if (dflag == 1 && g_StageData[0][p_y + 1][p_x + 1] == 1 && px + 40 == 80) {
		return 1;
	}

	if (g_StageData[0][p_y][p_x + 1] == 1 && px + 40 == 80) {
		return 1;
	}
	return 0;
}