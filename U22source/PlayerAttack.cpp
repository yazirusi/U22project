#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"
#include "EnemyMove.h"
#include "images.h"
#include "GameInit.h"
#include "sounds.h"
#include "notes.h"
#include "Ending.h"

int AttackExtend = 0;	//�Q�[�W�̗ʂōU���͈͂��L�т��
int imgflg;
int a_x[5] = { 0,0,0,0,0 };
int a_y[5] = { 0,0,0,0,0 };
bool ExtendFlg = false;
int hozon_a_x = 0;
int hozon_a_y = 0;
int hozon_diref = 0;
bool a_xf = false;
int efcnt = 0;

/***************************************
*�v���C���[�̍U��
***************************************/
void PlayerAttack() {

	//hp�O�ȉ��Ŏ��S
	if (player.hp <= 0) {
		return;
	}

	//player.ax = player.p_x * 40;	//�}�b�v�`�b�v�ɍ��킹���U���̍��W
	static int Xsize = 60;
	static int Ysize = 33;

	//�U���̕`��
	//for (int i = 0; i < 5; i++) {
	static int i = 0;
		if (player.af[i] == 1) {
			//player.ay[i] = player.py - 20;
			player.apx[i] = player.px;

			if (abs(AttackExtend) < player.col * 2) {
				ExtendFlg = true;
				if (player.adireF[0] == 0) {
					AttackExtend += 4;
				}
				else {
					AttackExtend -= 4;
				}
			}
			else {
				if (ExtendFlg == true) {
					//����
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];
					AttackExtend = 0;
				}
			}
			//�U���̍��W�v�Z
			if (a_xf == false && (g_stage == 1 || g_stage == 0)) {
				if (player.adireF[i] == 0) {//�E����
					a_x[i] = player.px + 40 + 10;	//�U����x���W
				}
				if (player.adireF[i] == 1) {//������
					a_x[i] = player.px - 40 - 30;	//�U����x���W
				}
				if (AttackExtend != 0) {
					a_xf = true;
				}
			}

			//if (player.px >= 640 && sx != -6400 ) {

			//	if (player.adireF[i] == 0) {//�E����
			//		a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px + 10;	//�U����x���W
			//	}
			//	if (player.adireF[i] == 1) {//������
			//		a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px - 30;	//�U����x���W
			//	}
			//}
			//else if (sx == -6400) {

			//	if (player.adireF[i] == 0) {//�E����
			//		a_x[i] = player.px + 40 + sx + 10;	//�U����x���W
			//	}
			//	if (player.adireF[i] == 1) {//������
			//		a_x[i] = player.px - 40 + sx - 30;	//�U����x���W
			//	}
			//}
			//else {
			//	if (player.adireF[i] == 0) {//�E����
			//		a_x[i] = player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10;	//�U����x���W
			//	}
			//	if (player.adireF[i] == 1) {//������
			//		a_x[i] = player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30;	//�U����x���W
			//	}
			//}

			////�u���b�N�Ƃ̓����蔻��(�E����)
			//if (player.af[i] == 1 && CheckHitBlock(6,i) == 0 && player.adireF[i] == 0) {
			//	DrawBox(a_x[i], player.ay[i],a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			//	//player.pa[i] += 4;
			//	player.at[i]--;
			//}
			////�u���b�N�ɂԂ������ꍇ������
			//else {
			//	//�u���b�N�Ƃ̓����蔻��(������)
			//	if (player.af[i] == 1 && CheckHitBlock(7, i) == 0 && player.adireF[i] == 1) {
			//		DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			//		//player.pa[i] -= 4;
			//		player.at[i]--;
			//	}
			//	//�u���b�N�ɂԂ������ꍇ������
			//	else {
			//		/*player.pa[i] = 0;
			//		player.af[i] = 0;
			//		player.ay[i] = 0;*/
			//		player.at[i]--;
			//	}
			//}


			//�G�ɓ��������ꍇ
			for (int j = 0; j < MAXEnemy; j++) {
				int ax1, ax2;
				if (player.adireF[0] == 0) {
					//�E�̓����蔻��p���W
					ax1 = a_x[i] + sx;
					ax2 = a_x[i] + sx + Xsize + AttackExtend;
				}
				else {
					//��
					ax1 = a_x[i] + sx + AttackExtend;
					ax2 = a_x[i] + sx + Xsize;
				}

				//�G�A�[�}���̔���
				if (ax2 > (airman[j].x + sx) && (airman[j].x + airman[j].size + sx) > ax1
					&& player.ay[i] < airman[j].y + airman[j].size && player.ay[i] + Ysize > airman[j].y - airman[j].size && player.aHitflg == false) {

					//�q�b�g�t���O
					PlaySoundMem(attackse2, DX_PLAYTYPE_BACK, TRUE);
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//��b�U���͂ɏ�悹����{��
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					airman[j].HP -= (player.pow * bai) / 100;
					airman[j].HPdrawf = true;
					player.col = 0;	//�~�ϒl�̏�����
					AttackExtend = 0;	//������
					player.ay[i] = 0;

					if (airman[j].HP <= 0) {
						airman[j].HPdrawf = false;
						airman[j].drawf = 0;
						airman[j].x = 0;
						airman[j].y = 0;//�G�̍��W�̏�����
						EnemyFascinationCount++;
					}

					player.hp += note.conbo;
					if (player.hp > 100) {
						player.hp = 100;
					}
				}

				//0:��\���@1:�\��
				if (Enemy[j].drawf == false) {
					continue;	//��\���Ȃ炱�����牺�̏��������Ȃ�
				}
				if (ax2 > (Enemy[j].x + sx) && (Enemy[j].x + Enemy[j].size + sx) > ax1
					&& player.ay[i] < Enemy[j].y + Enemy[j].size && player.ay[i] + Ysize > Enemy[j].y - Enemy[j].size && player.aHitflg == false) {
					//�q�b�g�t���O
					PlaySoundMem(attackse2, DX_PLAYTYPE_BACK, TRUE);
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//��b�U���͂ɏ�悹����{��
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//�~�ϒl�̏�����
					AttackExtend = 0;	//������
					player.ay[i] = 0;

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//�G�̍��W�̏�����
						EnemyFascinationCount++;
					}
					player.hp += note.conbo;
					if (player.hp > 100) {
						player.hp = 100;
					}
				}

				if (ax2 > (Enemy[j].x + sx - 30) && player.ay[i] > Enemy[j].y - Ysize
					&&  player.aHitflg == false && Enemy[j].type == 2) {//���X�{�X�̓����蔻��
					//�q�b�g�t���O
					PlaySoundMem(attackse2, DX_PLAYTYPE_BACK, TRUE);
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];

					//��b�U���͂ɏ�悹����{��
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//�~�ϒl�̏�����
					AttackExtend = 0;	//������
					player.ay[i] = 0;

					if (Enemy[j].HP <= 0) {
						PlaySoundMem(clearbgm, DX_PLAYTYPE_BACK, TRUE);
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//�G�̍��W�̏�����
						g_GameState = 6;	//���X�{�X��|������G���f�B���O
						g_stage = 0;
						StopSoundMem(rockBGM);
					}
				}
			}
			//�U���̓����蔻�莞��(20F)�ɂȂ����������
			if (player.at[i] <= 0) {
				if (ExtendFlg == false) {
					//����
					player.aHitflg = true;
					hozon_a_x = a_x[i] + AttackExtend;
					hozon_a_y = player.ay[i];
					hozon_diref = player.adireF[i];
					player.af[i] = 0;
					player.col = 0;	//�~�ϒl�̏�����
					//AttackExtend = 0;	//������
				}
				player.at[i] = 0;
				imgflg = false;
			}
			if (player.at[i] <= 0 || (AttackExtend == 0 && ExtendFlg == true)) {
				player.pa[i] = 0;
				if (AttackExtend == 0 && ExtendFlg == true) {
					player.af[i] = 0;
					player.ay[i] = 0;
					player.col = 0;	//�~�ϒl�̏�����
					ExtendFlg = false;
				}
				player.apx[i] = 0;
				//player.col = 0;	//�~�ϒl�̏�����
				//player.aHitflg = false;
				//ExtendFlg = false;
			}

			//�E�����̍U���̕`��
			if (player.af[i] == 1 && player.adireF[i] == 0 && player.aHitflg == false) {
				DrawBox(a_x[i] + sx + AttackExtend, player.ay[i], a_x[i] + sx + Xsize + AttackExtend, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], FALSE);
				DrawGraph(a_x[i] + sx + AttackExtend, player.ay[i], ef[0], TRUE);
			}
			//�������̕`��
			if (player.af[i] == 1 && player.adireF[i] == 1 && player.aHitflg == false) {
				DrawBox(a_x[i] + sx + AttackExtend, player.ay[i], a_x[i] + sx + Xsize + AttackExtend, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], FALSE);
				DrawTurnGraph(a_x[i] + sx + AttackExtend, player.ay[i], ef[0], TRUE);
			}
		}

		if (player.aHitflg == true) {
			//�E�����̍U���̕`��
			if (hozon_diref == 0) {
				DrawGraph(hozon_a_x + sx, hozon_a_y, ef[efcnt++ / 8 % 3 + 1], TRUE);
			}
			else {	//������
				DrawTurnGraph(hozon_a_x + sx, hozon_a_y, ef[efcnt++ / 8 % 3 + 1], TRUE);
			}
			if (efcnt == 24) {
				player.aHitflg = false;
				efcnt = 0;
			}
			a_xf = false;
			
		}

		if (imgflg == true) {
			player.at[i]--;
		}


		////�˒�����(�}�b�v�`�b�v�R��)�ɂȂ����珉����(�E����)
		//if (player.pa[i] == 120 && player.adireF[i] == 0) {
		//	player.af[i] = 0;
		//	player.pa[i] = 0;
		//	player.ay[i] = 0;
		//	player.apx[i] = 0;
		//}

		////�˒�����(�}�b�v�`�b�v�R��)�ɂȂ����珉����(������)
		//if (player.pa[i] == -120 && player.adireF[i] == 1) {
		//	player.af[i] = 0;
		//	player.pa[i] = 0;
		//	player.ay[i] = 0;
		//	player.apx[i] = 0;
		//}

		/*DrawFormatString(50, 190, 0xffffff, "a_x%d", a_x[0]);//�G�̂����W
		DrawFormatString(50, 260, 0xffffff, "/%d", a_x[0] / 40);//�G�̂����W
		DrawFormatString(50, 290, 0xffffff, "%d", player.pa[0] + 40 + player.px);//�G�̂����W*/
	//}
}

/***************************************
*�v���C���[�̍U���̏�����
***************************************/
void PlayerAttackInit() {
	a_x[0] = 0;
	a_y[0] = 0;
	ExtendFlg = false;
	hozon_a_x = 0;
	hozon_a_y = 0;
	hozon_diref = 0;
	a_xf = false;
	efcnt = 0;
	AttackExtend = 0;	//�Q�[�W�̗ʂōU���͈͂��L�т��
	imgflg = false;
	player.af[0] = 0;
	player.at[0] = 0;
}