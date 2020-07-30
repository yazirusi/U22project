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
	static int Xsize = 40;
	static int Ysize = 40;
	static int a_x[5] = { 0,0,0,0,0 };

	//�U���̕`��
	for (int i = 0; i < 5; i++) {
		if (player.px >= 640) {

			if (player.adireF[i] == 0) {//�E����
				a_x[i] = player.pa[i] + 680 + player.apx[i] - player.px;	//�U����x���W
			}
			if (player.adireF[i] == 1) {//������
				a_x[i] = player.pa[i] + 600 + player.apx[i] - player.px;	//�U����x���W
			}
		}else{
			if (player.adireF[i] == 0) {//�E����
				a_x[i] = player.pa[i] + (player.px + 40) + player.apx[i] - player.px;	//�U����x���W
			}
			if (player.adireF[i] == 1) {//������
				a_x[i] = player.pa[i] + (player.px - 40) + player.apx[i] - player.px;	//�U����x���W
			}
		}

		//�u���b�N�Ƃ̓����蔻��(�E����)
		if (player.af[i] == 1 && CheckHitBlock(6,i) == 0 && player.adireF[i] == 0) {
			DrawBox(a_x[i], player.ay[i],a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
			//player.pa[i] += 4;
			player.at[i]--;
		}
		//�u���b�N�ɂԂ������ꍇ������
		else {
			//�u���b�N�Ƃ̓����蔻��(������)
			if (player.af[i] == 1 && CheckHitBlock(7, i) == 0 && player.adireF[i] == 1) {
				DrawBox(a_x[i], player.ay[i], a_x[i] + Xsize, player.ay[i] + Ysize, player.acolor[player.ajudge[i]], TRUE);
				//player.pa[i] -= 4;
				player.at[i]--;
			}
			//�u���b�N�ɂԂ������ꍇ������
			else {
				/*player.pa[i] = 0;
				player.af[i] = 0;
				player.ay[i] = 0;*/
				player.at[i]--;
			}
		}


		//�G�ɓ��������ꍇ
		if (( a_x[i] + Xsize ) > (Enemy.x - Enemy.Move + sx) && (Enemy.x - Enemy.Move + Enemy.size + sx) > a_x[i]
		&& player.ay[i] < Enemy.y + Enemy.size && player.ay[i] + Ysize > Enemy.y) {
			/*player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
			player.at[i] = 0;*/
			Enemy.x = 0;
			Enemy.y = 0;//�G�̍��W�̏�����
			Enemy.drawf = 0;
		}
		//�U���̓����蔻�莞��(20F)�ɂȂ����������
		if (player.at[i] == 0) {
			player.af[i] = 0;
			player.pa[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
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