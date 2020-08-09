#include"DxLib.h"
#include"player.h"
#include"PlayerAttack.h"
#include "key.h"
#include "map.h"
#include "EnemyMove.h"

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
		if (player.af[i] == 1) {
			player.ay[i] = player.py - 20;
			player.apx[i] = player.px;
			if (player.px >= 640) {

				if (player.adireF[i] == 0) {//�E����
					a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px + 10;	//�U����x���W
				}
				if (player.adireF[i] == 1) {//������
					a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px - 30;	//�U����x���W
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
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				player.at[i]--;
			}
			//�������̕`��
			if (player.af[i] == 1 && player.adireF[i] == 1) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
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
				if ((a_x[i] + Xsize) > (Enemy[j].x + sx) && (Enemy[j].x + Enemy[j].size + sx) > a_x[i]
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

					if (Enemy[j].HP <= 0) {
						Enemy[j].HPdrawf = false;
						Enemy[j].drawf = 0;
						Enemy[j].x = 0;
						Enemy[j].y = 0;//�G�̍��W�̏�����
					}
				}
			}
			//�U���̓����蔻�莞��(20F)�ɂȂ����������
			if (player.at[i] == 0) {
				player.af[i] = 0;
				player.pa[i] = 0;
				player.ay[i] = 0;
				player.apx[i] = 0;
				player.col = 0;	//�~�ϒl�̏�����
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