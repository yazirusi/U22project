#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

const int AttackSpeed = 3;
const int AttackAmount = 3;
int count = 0;
int j = 0;

/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {
	SetFontSize(30);
	DrawFormatString(100, 300, 0xffffff, "%d", count);
	DrawFormatString(100, 330, 0xffffff, "%d", j);
	DrawFormatString(100, 360, 0xffffff, "%d", Enemy.Attck);
	//�v���C���[�����͈͂ɓ����Ă����瓮�����~�߂�
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		 ) {
		if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
			&& Enemy.drawf == 1) {
			for (int i = 0; i < AttackAmount; i++)
			{
				Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//�U���̍��W
			}
			Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
			Enemy.speed = 0;//�G�̈ړ��ʂ��O�ɂ���
			//Enemy.MoveFlg = true;//�G�l�~�[�̓������~�߂�
			//count++;
		}
	}
	else 
	{
		Enemy.speed = 1;//�G�̈ړ��ʂ�߂�
		//Enemy.MoveFlg = false;//�G�l�~�[�𓮂���
	}
	
	//�v���C���[���G�̍U���͈͓��ɓ�������U��
	if (Enemy.Attck == true) {
		//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//�G�̍U�����ǂɓ����������������
			if (count < 60 * AttackAmount) {
				count++;
				if (count % 60 == 0) {
					j++;
				}
			}
			for (int i = 0; i < j; i++)
			{
				DrawGraph(Enemy.ax[i] - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
				Enemy.ax[i] -= (AttackSpeed);//�U�����ړ�����
			}
		//}
		//else {
			//Enemy.Attck = false;//�U�����Ȃ���
		//}
	}
	//�G�̍U������ʊO�ɍs�������������
	for (int i = 0; i < AttackAmount; i++)
	{
		if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
			Enemy.ax[i] = 0;
			//Enemy.Attck = false;//�U�����Ȃ���
		}
		if (Enemy.ax[i] >= WIDTH || Enemy.ax[i] + 40 <= 0 - msx)
		{
			Enemy.ax[i] = 0;
			//DeleteGraph(Enemy.Attackimage[0]);
			//Enemy.Attck = false;
		}
		if (Enemy.ax[AttackAmount - 1] == 0)
		{
			j = 0;
			count = 0;//�G�̍U��������������
			Enemy.Attck = false;//�G�̍U�������߂�����
		}
	}
}