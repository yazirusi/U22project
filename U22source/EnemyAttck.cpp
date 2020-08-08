#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"
#include"images.h"

int Attackheight[MAXAttack]; //= 25;//�U�������W�̈ړ���(GameInit��25���)
const int AttackSpeed = 5;//�U�������W�̈ړ���
//const int AttackAmount = 3;//
const int Gravity = 1;//�d��
int EnemyAttackX[MAXAttack];//�U���̂����W
int EnemyAttackY[MAXAttack];//�U���̂����W
bool AttackFlg[MAXAttack];	//�U���\���t���O
bool AttackDir[MAXAttack];	//�U���̌��� 0�F���@�P:�E
int k;
ENEMY Enemy[MAXEnemy];
//Airman airman;

/***************
*Airman�̍U��
***************/
void Airman::AirmanAttack() {

	//DrawFormatString(50, 130, 0xffffff, "%d", sx);//�G�̂����W
	//DrawFormatString(50, 160, 0xffffff, "%d", k);//�G�̂����W

	for (int i = 0; i < Air_MAX; i++) {
		if (Air.DispFlg[i] == true) {//�t���O��true�Ȃ����
			DrawGraph(Airman::AttackX[i] - Airman::MoveD + sx, Airman::AttackY[i], EnemyAttackImg, TRUE);//�G�̍U���̕`��
			Airman::AttackX[i] -= AttackSpeed;//�G�̍U�����ړ�

			//�U���̒n�ʂ�ǂ̓����蔻��
			if (Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Airman::MoveD - sx, Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Airman::MoveD - sx, Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
				0 > Airman::AttackX[i] || Airman::AttackX[i] > 1280 && Air.DispFlg[i] == true) {
				Airman::AttackX[i] = Airman::x;//�U�����W������������
				Airman::AttackY[i] = Airman::y;//�U���̍��W������������
				Air.DispFlg[i] = false;//�t���O��off�ɂ���
			}
			k = sx;
		}
	}
}
/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {

	airman.AirmanAttack();

	for (int i = 0; i < MAXEnemy; i++) {
		//Enemy.MoveFlg;

		DrawFormatString(150, 200, 0x000000, "%d", Enemy[0].x);
		DrawFormatString(150, 230, 0x000000, "%d", AttackFlg[0]);
		DrawFormatString(150, 260, 0x000000, "%d", AttackFlg[1]);

		Enemy[i].speed = 1;

		//�U�����������邩�m�F���邽�߂̂���(��)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x > player.px
			&& Enemy[i].direction == false) {
			Enemy[i].speed = 0;//�G�̓������~�߂�
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//�G�̂����W������
					EnemyAttackY[a] = Enemy[i].y;//�G�̂����W������
					AttackDir[a] = Enemy[i].direction;	//�G�̍U���̌���
					Enemy[i].AttackInterval = 90;	//�G�̍U���Ԋu
					break;
				}
			}
		}
		//�E
		if (Enemy[i].x + Enemy[i].Perception > player.px
			&& Enemy[i].x < player.px
			&& Enemy[i].direction == true) {
			Enemy[i].speed = 0;//�G�̓������~�߂�
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//�G�̂����W������
					EnemyAttackY[a] = Enemy[i].y;//�G�̂����W������
					AttackDir[a] = Enemy[i].direction;	//�G�̍U���̌���
					Enemy[i].AttackInterval = 90;	//�G�̍U���Ԋu
					break;
				}
			}
		}

		//�G�̍U���Ԋu
		if (Enemy[i].AttackInterval > 0) {
			Enemy[i].AttackInterval--;
		}
		/*//����U���t���O�����������瓮��
		for (int i = 0; i < MAXAttack; i++) {
			if (Enemy.Attack[i] == true) {
				break;
			}
			if (i == MAXAttack - 1) {
				Enemy.speed = 1;
			}
		}*/

		for (int a = 0; a < MAXAttack && i == 29; a++) {
			if (AttackFlg[a] == true) {//�t���O��true�Ȃ����
				DrawGraph(EnemyAttackX[a] + sx, EnemyAttackY[a], EnemyAttackImg, TRUE);//�G�̍U���̕`��
				EnemyAttackY[a] -= Attackheight[a];//�U������ɓ�����
				if (AttackDir[a] == false) {
					EnemyAttackX[a] -= AttackSpeed;//�U�������ɓ�������
				}
				else {
					EnemyAttackX[a] += AttackSpeed;//�U�������ɓ�������
				}

				Attackheight[a] -= Gravity;//�d�͂�����

				//�U���̒n�ʂ�ǂ̓����蔻��
				if (Hitcheck(EnemyAttackX[a], EnemyAttackY[a], AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a], AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a], EnemyAttackY[a] + 20, AttackDir[a], false) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a] + 20, AttackDir[a], false) == 1) {
					AttackFlg[a] = false;//�t���O��off�ɂ���
					Attackheight[a] = 25;//�U���̈ړ��ʂ�����������
				}

				//�U���̃v���C���[�Ƃ̓����蔻��
				if ((Hitcheck(EnemyAttackX[a], EnemyAttackY[a], AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a], AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a], EnemyAttackY[a] + 20, AttackDir[a], true) == 1 ||
					Hitcheck(EnemyAttackX[a] + 20, EnemyAttackY[a] + 20, AttackDir[a], true) == 1)
					&& player.hit == false) {
					//�h�䂵�Ă�����
					if (player.protect == true) {
						//Perfect
						if (player.protecJudge == 1) {
							Enemy[i].drawf = 0;	//�G�����������炤
						}
						player.protect = false;//�h��I��
						AttackFlg[a] = false;//�t���O��off�ɂ���
					}
					else {
						AttackFlg[a] = false;//�t���O��off�ɂ���
						Attackheight[a] = 25;//�U���̈ړ��ʂ�����������
						player.hp -= 20;//�v���C���[��hp������
						player.hit = true;//�U����H������t���O
						if (player.hp <= 0) {
							player.pcnt = 0;	//��񂾂�������
						}
					}
				}
			}
		}
	}

	/*Enemy.Attack = false;
	//�U�����������邩�m�F���邽�߂̂���(��)
	if (Enemy.x - Enemy.Perception < player.px + 40
		&& Enemy.x > player.px
		&& Enemy.direction == false) {
		Enemy.Attack = true;
	}
	//�E
	if (Enemy.x + Enemy.Perception > player.px
		&& Enemy.x < player.px
		&& Enemy.direction == true) {
		Enemy.Attack = true;
	}

	if (Enemy.Attack == true) {//�t���O��true�Ȃ����
		Enemy.speed = 0;//�G�̓������~�߂�
		DrawGraph(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.Attackimage[0], TRUE);//�G�̍U���̕`��
		EnemyAttackY -= Attackheight;//�U������ɓ�����
		if (Enemy.direction == false) {
			EnemyAttackX -= AttackSpeed;//�U�������ɓ�������
		}
		else {
			EnemyAttackX += AttackSpeed;//�U�������ɓ�������
		}

		Attackheight -= Gravity;//�d�͂�����
	}

	//�U���̒n�ʂ�ǂ̓����蔻��
	if (Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1) {
		Enemy.Attack = false;//�t���O��off�ɂ���
		Attackheight = 25;//�U���̈ړ��ʂ�����������
	}

	//�U���̃v���C���[�Ƃ̓����蔻��
	if ((Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1) 
		&& player.hit == false) {
		//�h�䂵�Ă�����
		if (player.protect == true) {
			//Perfect
			if (player.protecJudge == 1) {
				Enemy.drawf = 0;	//�G�����������炤
			}
			player.protect = false;//�h��I��
			Enemy.Attack = false;//�t���O��off�ɂ���
		}
		else {
			Enemy.Attack = false;//�t���O��off�ɂ���
			Attackheight = 25;//�U���̈ړ��ʂ�����������
			player.hp -= 20;//�v���C���[��hp������
			player.hit = true;//�U����H������t���O
			if (player.hp <= 0) {
				player.pcnt = 0;	//��񂾂�������
			}
		}
	}
	*/

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