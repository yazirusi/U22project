#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {
	
	//�v���C���[�����͈͂ɓ����Ă����瓮�����~�߂�
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		 ) {
		if (Enemy.Attck == false&&Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 && Enemy.drawf == 1) {
			Enemy.ax = Enemy.x - Enemy.Move - 40;//�U���̍��W
			Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
			Enemy.MoveFlg = true;//�G�l�~�[�̓������~�߂�
		}
	}
	else 
	{
		Enemy.MoveFlg = false;//�G�l�~�[�𓮂���
	}
	
	//�v���C���[���G�̍U���͈͓��ɓ�������U��
	if (Enemy.Attck == true) {
		//�G�̍U�����ǂɓ����������������
		if (Hitcheck(Enemy.ax, Enemy.y, Enemy.direction) != 1) {
			DrawGraph(Enemy.ax - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
			Enemy.ax -= (4);//�U�����ړ�����
		}
		else {
			Enemy.Attck = false;
		}
	}
	//�G�̍U������ʊO�ɍs�������������
	if (Enemy.ax >= WIDTH || Enemy.ax + 40 <= 0 - msx)
	{
		//DeleteGraph(Enemy.Attackimage[0]);
		Enemy.Attck = false;
	}
}