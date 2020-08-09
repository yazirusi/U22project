#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"
#include"images.h"
#include"math.h"
#include"BackgroundMove.h"

int Attackheight[MAXAttack]; //= 25;//�U�������W�̈ړ���(GameInit��25���)
const int AttackSpeed = 5;//�U�������W�̈ړ���
const double RotAttackSpd = 2;	//���L�����Ɍ������Ă���U���̑��x
//const int AttackAmount = 3;//
const int Gravity = 1;//�d��
double EnemyAttackX[MAXAttack];//�U���̂����W
double EnemyAttackY[MAXAttack];//�U���̂����W
double EnemyAttackRot[MAXAttack];	//�G�̍U�����i�ފp�x
bool AttackFlg[MAXAttack];	//�U���\���t���O
bool AttackDir[MAXAttack];	//�U���̌��� 0�F���@�P:�E
int AttackType[MAXAttack];	//�G�̍U���̎��
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
		DrawFormatString(150, 290, 0x000000, "%d", player.px);
		DrawFormatString(150, 320, 0x000000, "%d", scrool);

		Enemy[i].speed = 1;

		//�G�̎˒��͈͓��ɂ�����(��)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			Enemy[i].speed = 0;//�G�̓������~�߂�
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//�G�̂����W������
					EnemyAttackY[a] = Enemy[i].y;//�G�̂����W������
					AttackDir[a] = Enemy[i].direction;	//�G�̍U���̌���
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//�G�̎�ނ��Ƃ̍U���Ԋu
					AttackType[a] = Enemy[i].type;	//�G�̎�ނ��Ƃ̍U���p�^�[��
					double taX = (double)player.px - EnemyAttackX[a];	//���L�����܂ł̋���(X)
					double taY = (double)player.py - EnemyAttackY[a];	//���L�����܂ł̋���(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//���L�����ƓG�̍U���̊p�x
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
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//�G�̎�ނ��Ƃ̍U���Ԋu
					AttackType[a] = Enemy[i].type;	//�G�̎�ނ��Ƃ̍U���p�^�[��
					double taX = (double)player.px - EnemyAttackX[a];	//���L�����܂ł̋���(X)
					double taY = (double)player.py - EnemyAttackY[a];	//���L�����܂ł̋���(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//���L�����ƓG�̍U���̊p�x
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
	}
	for (int i = 0; i < MAXAttack; i++) {
		if (AttackFlg[i] == true) {//�t���O��true�Ȃ����
			//�U���p�^�[�����Ƃ̓���
			EnemyAttackType(i);

			if (AttackType[i] != 1) {	//1�͕Ǌђʂ���U��
				//�U���̒n�ʂ�ǂ̓����蔻��
				if (Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1) {
					AttackFlg[i] = false;//�t���O��off�ɂ���
					Attackheight[i] = 25;//�U���̈ړ��ʂ�����������
					AttackType[i] = 0;	//�U���p�^�[���̏�����
				}
			}

			//�U������ʊO�ɍs�����珉����
			if (-sx > EnemyAttackX[i] + 20 || -sx + WIDTH < EnemyAttackX[i]
				|| EnemyAttackY[i] + 20 < 0 || EnemyAttackY[i] + 20 > HEIGHT - 90) {
				AttackFlg[i] = false;//�t���O��off�ɂ���
				Attackheight[i] = 25;//�U���̈ړ��ʂ�����������
				AttackType[i] = 0;	//�U���p�^�[���̏�����
			}

			//�U���̃v���C���[�Ƃ̓����蔻��
			if ((Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1)
				&& player.hit == false) {
				//�h�䂵�Ă�����
				if (player.protect == true) {
					//Perfect
					if (player.protecJudge == 1) {
						/*for (i = 0; i < MAXEnemy; i++) {
							Enemy[i].drawf = 0;	//�G�����������炤
						}*/
					}
					player.protect = false;//�h��I��
					AttackFlg[i] = false;//�t���O��off�ɂ���
					AttackType[i] = 0;	//�U���p�^�[���̏�����
				}
				else {
					AttackFlg[i] = false;//�t���O��off�ɂ���
					Attackheight[i] = 25;//�U���̈ړ��ʂ�����������
					AttackType[i] = 0;	//�U���p�^�[���̏�����
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
int EnemyAttackType(int i) {
	if (AttackType[i] == 0) {	//�������̍U��
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//�G�̍U���̕`��
		EnemyAttackY[i] -= Attackheight[i];//�U������ɓ�����
		if (AttackDir[i] == false) {
			EnemyAttackX[i] -= AttackSpeed;//�U�������ɓ�������
		}
		else {
			EnemyAttackX[i] += AttackSpeed;//�U�������ɓ�������
		}

		Attackheight[i] -= Gravity;//�d�͂�����
	}

	if (AttackType[i] == 1) {	//�v���C���[�Ɍ������Ă���U��
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//�G�̍U���̕`��

		//�ړ��ʌv�Z
		EnemyAttackX[i] += cos(EnemyAttackRot[i]) * RotAttackSpd;
		EnemyAttackY[i] += sin(EnemyAttackRot[i]) * RotAttackSpd;
	}

	return 0;
}