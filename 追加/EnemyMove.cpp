#include"DxLib.h"
#include"EnemyMove.h"
#include"map.h"

ENEMY Enemy;

/***************************************
*�G�l�~�[�̓���
***************************************/
void EnemyMove(void) {
	//Enemy.x = (Enemy.Mapx * 40) + Enemy.direction * Enemy.speed;
	//Enemy.y = Enemy.MapY * 40;
	//Enemy.x = Enemy.x + (Enemy.speed * Enemy.direction);
	if (Enemy.Attck == false) {
		//�G�̍��W�ƃ}�b�v�`�b�v�̓����蔻��𒲂ׂ�
		if (Enemy.direction == false) {//���Ɉړ����Ă鎞�̏���
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction, Enemy.MoveD) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
			//if (g_StageData[0][Enemy.y/40][Enemy.x+Enemy.speed - Enemy.Move]) {
				Enemy.x -= (Enemy.speed);//�����Ȃ�ړ����Ă���
			}
			else
			{
				Enemy.direction = true;//�E�ɂ��邽�߂̃t���O
			}
		}

		if (Enemy.direction == TRUE) {//�E�Ɉړ����Ă鎞�̏���
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction, Enemy.MoveD) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
				Enemy.x += (Enemy.speed);//�����Ȃ�ړ����Ă���
			}
			else
			{
				Enemy.direction = false;//���ɂ��邽�߂̃t���O
			}
		}
	}
}
/**************************************
*�����蔻��
*hx:�G�L�����̂����W
*hy:�G�L�����̂����W
*Move�F��ʂ̃X�N���[����
***************************************/
int Hitcheck(int hx, int hy, int direction, int Move)
{
	int x = 0;//������
	int y = 0;//������

	y = hy / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�
	x = (hx + Move) / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�

	return g_StageData[0][y][x];//�}�b�v�`�b�v��ł̍��W��Ԃ�

	return 0;
}