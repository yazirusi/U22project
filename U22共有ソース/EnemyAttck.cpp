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
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//�U���̍��W
		Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
	}
	
	//�v���C���[���G�̍U���͈͓��ɓ�������U��
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
		Enemy.ax -= (4);//�U�����ړ�����
	}
	if (Enemy.ax >= WIDTH || Enemy.ax + 40 <= 0 - msx)
	{
		//DeleteGraph(Enemy.Attackimage[0]);
		Enemy.Attck = false;
	}
}