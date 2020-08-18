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
	//�G�A�[�}���̍����̊��m�͈�
	if (x - Perception < player.px + 40 && x>player.px) {
		direction = false;
		for (int i = 0; i < MAXAttack; i++) {
			if (AttackFlg[i] == false) {
				if (airman[Air[1].ReloadCount].Jump == 20 && AttackInterval == 0) {
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				if (airman[Air[1].ReloadCount].Jump == 0) {
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				break;
			}
		}
	}

	//�G�A�[�}���̉E���̊��m�͈�
	if (x + Perception > player.px && x < player.px && x != 0) {
		direction = true;
		for (int i = 0; i < MAXAttack; i++) {
			if (AttackFlg[i] == false) {
				if (airman[Air[1].ReloadCount].Jump == 20 && AttackInterval == 0) {
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				if (airman[Air[1].ReloadCount].Jump == 0) {
					AttackFlg[i] = true;
					EnemyAttackX[i] = x;
					EnemyAttackY[i] = y - 40;
					AttackType[i] = 2;
					AttackInterval = 120;
					AttackDir[i] = direction;
				}
				break;
			}
		}
	}

}
/*************
*
**************/
int AIR::AirMove(int X, int Y) {
	for (int i = 0; i < MAXAttack; i++) {
		if (AttackFlg[i] == true && AttackType[i] == 2) {
			/*if (airman[Air[1].ReloadCount].Jump == 20) {
				EnemyAttackX[i] = X;
				EnemyAttackY[i] = Y;
			}
			if (airman[Air[1].ReloadCount].Jump == 0 ) {
				Upx = X;
				Upy = Y;
				DispFlg[1] = true;
			}*/
			DrawGraph(EnemyAttackX[i] + sx, EnemyAttackY[i], EnemyAttackImg, TRUE);//�G�̍U���̕`��
			if (AttackDir[i] == false) {
				EnemyAttackX[i] -= 3;
			}
			else {
				EnemyAttackX[i] += 3;
			}
			if (Hitcheck(EnemyAttackX[i], EnemyAttackY[i], 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i] + 20, EnemyAttackY[i], 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i], EnemyAttackY[i] + 20, 0, false) == 1 ||
				Hitcheck(EnemyAttackX[i] + 20, EnemyAttackY[i] + 20, 0, false) == 1 ||
				0 - sx >= EnemyAttackX[i] || EnemyAttackX[i] >= 1280 - sx) {
				AttackFlg[i] = false;
				AttackType[i] = 0;
				EnemyAttackX[i] = 0;
				EnemyAttackY[i] = 0;
			}
		}
		//if (/*EnemyAttackX[i] != 0 && EnemyAttackY[i] != 0 && */DispFlg[0] == true) {
		/*DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//�G�̍U���̕`��
		Upx -= 3;
		if (Hitcheck(Upx, Upy, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
			Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
			0 - sx >= Upx || Upx >= 1280 - sx) {
			DispFlg[1] = false;//�t���O��off�ɂ���
			Upx = 0;
			Upy = 0;
		}*/
	}

	//if (AttackFlg[Air[1].ReloadCount] == true)
	//{
	//	if (airman[Air[1].ReloadCount].Jump == 20 && DispFlg[0] == false
	//		/*&& Downx != 0 && Downy != 0*/) {
	//		Downx = X;
	//		Downy = Y;
	//		DispFlg[0] = true;
	//	}
	//	if (airman[Air[1].ReloadCount].Jump == 0 && DispFlg[1] == false
	//		/*&& Upx != 0 && Upy != 0*/) {
	//		Upx = X;
	//		Upy = Y;
	//		DispFlg[1] = true;
	//	}
	//}

	//if (/*Downx != 0 && Downy != 0 && */DispFlg[0] == true) {
	//	DrawGraph(Downx + sx, Downy, EnemyAttackImg, TRUE);//�G�̍U���̕`��
	//	Downx -= 3;
	//	if (Hitcheck(Downx, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx, Downy + 20, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy + 20, 0, false) == 1 ||
	//		0 - sx >= Downx || Downx >= 1280 - sx && DispFlg[0] == true) {
	//		DispFlg[0] = false;//�t���O��off�ɂ���
	//		Downx = 0;
	//		Downy = 0;
	//	}
	//}
	//if (/*Upx != 0 && Upy != 0 &&*/ DispFlg[1] == true) {
	//	DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//�G�̍U���̕`��
	//	Upx -= 3;
	//	if (Hitcheck(Upx, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
	//		0 - sx >= Upx || Upx >= 1280 - sx && DispFlg[1] == true) {
	//		DispFlg[1] = false;//�t���O��off�ɂ���
	//		Upx = 0;
	//		Upy = 0;
	//	}
	//}

	return 0;
}
/***************************************
*�G�l�~�[�̍U��
***************************************/
void EnemyAttck(void) {

	DrawFormatString(300, 200, 0x000000, "%d", Enemy[0].x);
	DrawFormatString(300, 230, 0x000000, "%d", AttackFlg[0]);
	DrawFormatString(300, 260, 0x000000, "%d", AttackFlg[1]);
	DrawFormatString(300, 290, 0x000000, "%d", player.px);
	DrawFormatString(300, 320, 0x000000, "%d", Air[0].Downx);
	DrawFormatString(300, 350, 0x000000, "%d", Air[0].Upx);
	DrawFormatString(200, 270, 0xffffff, "a[0]%f", EnemyAttackX[0]);
	DrawFormatString(200, 300, 0xffffff, "a[1]%f", EnemyAttackX[1]);

	for (int i = 0; i < MAXAttack; i++)
	{
		DrawFormatString(300, 100 + i * 30, 0xff0000, "%d", AttackFlg[i]);
	}

	for (int i = 0; i < MAXEnemy; i++) {
		//Enemy.MoveFlg;

		airman[i].AirmanAttack();

		//Enemy[i].speed = 1;
		if (Enemy[i].type == 0) {
			Enemy[i].MoveFlg = true;
		}

		//�G�̎˒��͈͓��ɂ�����(��)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			//Enemy[i].speed = 0;//�G�̓������~�߂�
			Enemy[i].MoveFlg = false;//�G�̓������~�߂�
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
			//Enemy[i].speed = 0;//�G�̓������~�߂�
			Enemy[i].MoveFlg = false;//�G�̓������~�߂�
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

	Air[Air[1].ReloadCount].AirMove(0, 0);

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