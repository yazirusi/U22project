#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"
#include "EnemyMove.h"

int AttackExtend = 0;	//�Q�[�W�̗ʂōU���͈͂��L�т��

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
	static int Ysize = 60;
	static int a_x[5] = { 0,0,0,0,0 };

	//�U���̕`��
	for (int i = 0; i < 5; i++) {

		player.ay[i] = player.py - 20;
		player.apx[i] = player.px;
		DrawFormatString(0, 450, 0x000000, "AX:%d", AttackExtend);
		DrawFormatString(0, 400, 0x000000, "pa:%d", player.pa[i]);
		DrawFormatString(0, 425, 0x000000, "apx:%d", player.apx[i]);
		DrawFormatString(0, 300, 0x000000, "0:%d", player.pa[i] + 680 + player.apx[i] - player.px + 10);
		DrawFormatString(0, 325, 0x000000, "1:%d", player.pa[i] + 600 + player.apx[i] - player.px - 30);
		DrawFormatString(0, 350, 0x000000, "0:%d", player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10);
		DrawFormatString(0, 375, 0x000000, "1:%d", player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30);
		if (player.af[i] == 1) {
			player.ay[i] = player.py - 20;
			player.apx[i] = player.px;

			DrawFormatString(0, 300, 0x000000, "0:%d", player.pa[i] + 680 + player.apx[i] - player.px + 10);
			DrawFormatString(0, 325, 0x000000, "1:%d", player.pa[i] + 600 + player.apx[i] - player.px - 30);
			DrawFormatString(0, 350, 0x000000, "0:%d", player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10);
			DrawFormatString(0, 375, 0x000000, "1:%d", player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30);
			if (abs(AttackExtend) < player.col * 2) {
				if (player.adireF[0] == 0) {
					AttackExtend += 2;
				}
				else {
					AttackExtend -= 2;
				}
			}
			else {
				AttackExtend = 0;
			}

			if (player.px >= 640 && sx != -6400 ) {

				if (player.adireF[i] == 0) {//�E����
					a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px + 10;	//�U����x���W
				}
				if (player.adireF[i] == 1) {//������
					a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px - 30;	//�U����x���W
				}
			}
			else if (sx == -6400) {

				if (player.adireF[i] == 0) {//�E����
					a_x[i] = player.px + 40 + sx + 10;	//�U����x���W
				}
				if (player.adireF[i] == 1) {//������
					a_x[i] = player.px - 40 + sx - 30;	//�U����x���W
				}
			}
			else {
				if (player.adireF[i] == 0) {//�E����
					a_x[i] = player.pa[i] + (player.px + 40) + player.apx[i] - player.px + 10;	//�U����x���W
				}
				if (player.adireF[i] == 1) {//������
					a_x[i] = player.pa[i] + (player.px - 40) + player.apx[i] - player.px - 30;	//�U����x���W
				}
			}

			//�E�����̍U���̕`��
			if (player.af[i] == 1 && player.adireF[i] == 0) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize + AttackExtend, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.at[i]--;
			}
			//�������̕`��
			if (player.af[i] == 1 && player.adireF[i] == 1) {
				DrawBox(a_x[i] + AttackExtend, player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.at[i]--;
			}

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
				//0:��\���@1:�\��
				if (Enemy[j].drawf == false) {
					continue;	//��\���Ȃ炱�����牺�̏��������Ȃ�
				}
				int ax1, ax2;
				if (player.adireF[0] == 0) {
					//�E�̓����蔻��p���W
					ax1 = a_x[i];
					ax2 = a_x[i] + Xsize + AttackExtend;
				}
				else {
					//��
					ax1 = a_x[i] + AttackExtend;
					ax2 = a_x[i] + Xsize;
				}
				if (ax2 > (Enemy[j].x + sx) && (Enemy[j].x + Enemy[j].size + sx) > ax1
					&& player.ay[i] < Enemy[j].y + Enemy[j].size && player.ay[i] + Ysize > Enemy[j].y && player.aHitflg == false) {
					/*player.pa[i] = 0;
					player.af[i] = 0;
					player.ay[i] = 0;
					player.apx[i] = 0;
					player.at[i] = 0;*/

					//�q�b�g�t���O
					player.aHitflg = true;

					//��b�U���͂ɏ�悹����{��
					//float bai = (float)maxpmag * ((float)player.col / (float)100);
					int bai = 100 + (maxpmag * player.col);

					Enemy[j].HP -= (player.pow * bai) / 100;
					Enemy[j].HPdrawf = true;
					player.col = 0;	//�~�ϒl�̏�����
					AttackExtend = 0;	//������

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//�G�̍��W�̏�����
					}
				}
			}
			//�U���̓����蔻�莞��(20F)�ɂȂ����������
			if (player.at[i] < 0 && AttackExtend == 0) {
				player.af[i] = 0;
				player.pa[i] = 0;
				player.ay[i] = 0;
				player.apx[i] = 0;
				player.col = 0;	//�~�ϒl�̏�����
				AttackExtend = 0;	//������
				player.aHitflg = false;
			}
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
	}
}