#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

int Attackheight = 25;//�U�������W�̈ړ���
const int AttackSpeed = 5;//�U�������W�̈ړ���
//const int AttackAmount = 3;//
const int Gravity = 1;//�d��
int EnemyAttackX;//�U���̂����W
int EnemyAttackY;//�U���̂����W

/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {
	SetFontSize(30);
	/*DrawFormatString(100, 100, 0xffffff, "%d", EnemyAttackX);
	DrawFormatString(100, 130, 0xffffff, "%d", EnemyAttackY);
	DrawFormatString(100, 160, 0xffffff, "%d", Enemy.Attck);*/
	//�G�̎��S����	0:���S�@1:�\��
	if (Enemy.drawf == 0) {
		return;
	}

	//�U�����������邩�m�F���邽�߂̂���
	/*if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px) {
		Enemy.Attck = true;
	}*/

	if (Enemy.Attck == false) {//�t���O��false�̎��v���C���[�̍��W�������
		EnemyAttackX = Enemy.x;//�G�̂����W������
		EnemyAttackY = Enemy.y;//�G�̂����W������
		Enemy.speed = 1;//�G�̈ړ��ʂ�������
	}

	if (Enemy.Attck == true) {//�t���O��true�Ȃ����
		Enemy.speed = 0;//�G�̓������~�߂�
		DrawGraph(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
		EnemyAttackY -= Attackheight;//�U������ɓ�����
		EnemyAttackX -= AttackSpeed;//�U�������ɓ�������
		Attackheight -= Gravity;//�d�͂�����
	}

	//�U���̒n�ʂ�ǂ̓����蔻��
	if (Hitcheck(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.direction) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD + sx, EnemyAttackY, Enemy.direction) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY + 20, Enemy.direction) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD + sx, EnemyAttackY + 20, Enemy.direction) == 1 &&
		Enemy.Attck == true) {
		Enemy.Attck = false;//�t���O��off�ɂ���
		EnemyAttackX = Enemy.x;//�U�����W������������
		EnemyAttackY = Enemy.y;//�U���̍��W������������
		Attackheight = 25;//�U���̈ړ��ʂ�����������
	}

	////�v���C���[�����͈͂ɓ����Ă����瓮�����~�߂�
	//if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
	//	&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
	//	 ) {
	//	if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
	//		&& Enemy.drawf == 1) {
	//		for (int i = 0; i < AttackAmount; i++)
	//		{
	//			Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//�U���̍��W
	//		}
	//		Enemy.Attck = true;//�U����`�悷�邽�߂̃t���O
	//		Enemy.speed = 0;//�G�̈ړ��ʂ��O�ɂ���
	//		//Enemy.MoveFlg = true;//�G�l�~�[�̓������~�߂�
	//		//count++;
	//	}
	//}
	//else 
	//{
	//	Enemy.speed = 1;//�G�̈ړ��ʂ�߂�
	//	//Enemy.MoveFlg = false;//�G�l�~�[�𓮂���
	//}
	//
	////�v���C���[���G�̍U���͈͓��ɓ�������U��
	//if (Enemy.Attck == true) {
	//	//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//�G�̍U�����ǂɓ����������������
	//		if (count < 60 * AttackAmount) {
	//			count++;
	//			if (count % 60 == 0) {
	//				j++;
	//			}
	//		}
	//		for (int i = 0; i < j; i++)
	//		{
	//			DrawGraph(Enemy.ax[i] - Enemy.MoveD + sx, Enemy.y, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
	//			Enemy.ax[i] -= (AttackSpeed);//�U�����ړ�����
	//		}
	//	//}
	//	//else {
	//		//Enemy.Attck = false;//�U�����Ȃ���
	//	//}
	//}
	////�G�̍U������ʊO�ɍs�������������
	//for (int i = 0; i < AttackAmount; i++)
	//{
	//	if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
	//		Enemy.ax[i] = 0;
	//		//Enemy.Attck = false;//�U�����Ȃ���
	//	}
	//	if (Enemy.ax[i] >= WIDTH || Enemy.ax[i] + 40 <= 0 - sx)
	//	{
	//		Enemy.ax[i] = 0;
	//		//DeleteGraph(Enemy.Attackimage[0]);
	//		//Enemy.Attck = false;
	//	}
	//	if (Enemy.ax[AttackAmount - 1] == 0)
	//	{
	//		j = 0;
	//		count = 0;//�G�̍U��������������
	//		Enemy.Attck = false;//�G�̍U�������߂�����
	//	}
	//}
}