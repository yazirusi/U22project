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

	//player.ax = player.p_x * 40;	//�}�b�v�`�b�v�ɍ��킹���U���̍��W
	static int Xsize = 40;
	static int Ysize = 40;

	//�U���̕`��
	for (int i = 0; i < 5; i++) {

		int a_x[5];
		a_x[i] = player.pa[i] + 80 + player.apx[i] - player.px;	//�U����x���W

		//�u���b�N�Ƃ̓����蔻��
		if (player.af[i] == 1 && CheckHitBlock(6,i) == 0) {
			DrawBox(a_x[i], player.ay[i],a_x[i] + Xsize, player.ay[i] + Ysize, 0xCC33FF, TRUE);
			player.pa[i] += 2;
		}
		//�u���b�N�ɂԂ������ꍇ������
		else {
			player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
		}
		//�G�ɓ��������ꍇ
		if (( a_x[i] + Xsize ) > (Enemy.x - Enemy.Move + msx) 
		&&(Enemy.x - Enemy.Move + Enemy.size + msx) > a_x[i]) {
			player.pa[i] = 0;
			player.af[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
		//�˒�����(�}�b�v�`�b�v�R��)�ɂȂ����珉����
		if (player.pa[i] == 120) {
			player.af[i] = 0;
			player.pa[i] = 0;
			player.ay[i] = 0;
			player.apx[i] = 0;
		}
		/*DrawFormatString(50, 190, 0xffffff, "a_x%d", a_x[0]);//�G�̂����W
		DrawFormatString(50, 260, 0xffffff, "/%d", a_x[0] / 40);//�G�̂����W
		DrawFormatString(50, 290, 0xffffff, "%d", player.pa[0] + 40 + player.px);//�G�̂����W*/
	}
}