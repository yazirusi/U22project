#include"DxLib.h"
#include"EnemyMove.h"
#include"map.h"

ENEMY Enemy;

/***************************************
*�G�l�~�[�̓���
***************************************/
void EnemyMove(void) {
	DrawFormatString(50, 100, 0xffffff, "%d", Enemy.ax);//�G�̍U���̂����W
	DrawFormatString(50, 130, 0xffffff, "%d", Enemy.x);//�G�̂����W

	//�v���C���[���������t���O���L�[�������Ă邩
	if (Enemy.Moveflg == 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		Enemy.Move -= 2;//�G�L�����̈ړ��ɉ��Z����X�N���[����
		if (Enemy.Attck == true) {
			Enemy.MoveD -= 2;
		}
		Enemy.Moveflg = 0;//�t���O��������
	}
	//�v���C���[���������t���O���L�[�������Ă邩
	else if (Enemy.Moveflg == 2 && CheckHitKey(KEY_INPUT_LEFT) != 1)
	{
		Enemy.Move += 2;//�G�L�����̈ړ��ɉ��Z����X�N���[����
		if (Enemy.Attck == true) {
			Enemy.MoveD += 2;
		}
		Enemy.Moveflg = 0;
	}

	if (Enemy.MoveFlg == false) {
		//�G�̍��W�ƃ}�b�v�`�b�v�̓����蔻��𒲂ׂ�
		if (Enemy.direction == false) {//���Ɉړ����Ă鎞�̏���
			if (Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
				Enemy.x -= (Enemy.speed);//�����Ȃ�ړ����Ă���
			}
			else
			{
				Enemy.direction = true;//�E�ɂ��邽�߂̃t���O
			}
		}

		if (Enemy.direction == TRUE) {//�E�Ɉړ����Ă鎞�̏���
			if (Hitcheck(Enemy.x + Enemy.size, Enemy.y, Enemy.direction) != 1) {//�����蔻��̊֐��ɓG�̍��W�ƃX�N���[���ʂ𑗂�
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
int Hitcheck(int hx, int hy, int direction/*, int Move*/)
{
	int x = 0;//������
	int y = 0;//������

	y = hy / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�
	x = (hx /*+ Move*/) / 40;//�G�̂����W���}�b�v�`�b�v�ɓ��Ă͂߂�

	return g_StageData[0][y][x];//�}�b�v�`�b�v��ł̍��W��Ԃ�

	return 0;
}