#pragma once
#include"DxLib.h"

const int MAXAttack = 30;	//�\������U���̍ő��
extern double EnemyAttackX[MAXAttack];//�G�̍U���̂����W
extern double EnemyAttackY[MAXAttack];//�G�̍U����Y���W
extern double EnemyAttackRot[MAXAttack];	//�G�̍U�����i�ފp�x
extern int Attackheight[MAXAttack];
extern bool AttackFlg[MAXAttack];
extern bool AttackDir[MAXAttack];	//�U���̌��� 0�F���@�P:�E
extern int AttackType[MAXAttack];	//�G�̍U���̎��

void EnemyAttck();
int EnemyAttackType(int i);