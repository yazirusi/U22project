#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {
	
	//�v���C���[�����͈͂ɓ����Ă����瓮�����~�߂�
	if (Enemy.x - Enemy.Move - Enemy.MoveD - Enemy.Perception < px + 40/*&&Enemy.x + Enemy.Perception > px*/
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - Enemy.MoveD - 40;//�U���̍��W
		Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
	}
	if (Enemy.Attck == true) {
		DrawBox(Enemy.ax, Enemy.y, Enemy.ax + 40, Enemy.y + 40, 0xffffff, TRUE);//�U����`�悷��
		Enemy.ax -= (1);//�U�����ړ�����
	}
}