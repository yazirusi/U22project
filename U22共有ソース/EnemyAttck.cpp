#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {

	//�v���C���[�����͈͂ɓ����Ă����瓮�����~�߂�
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//�U���̍��W
		Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
	}
	//�v���C���[���G�̍U���͈͓��ɓ�������U��
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD, Enemy.y, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
		Enemy.ax -= (2);//�U�����ړ�����
	}
}