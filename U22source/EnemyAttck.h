#pragma once
#include"DxLib.h"

const int MAXAttack = 30;	//�\������U���̍ő��
extern int EnemyAttackX[MAXAttack];//�G�̍U���̂����W
extern int EnemyAttackY[MAXAttack];//�G�̍U����Y���W
extern int Attackheight[MAXAttack];
extern bool AttackFlg[MAXAttack];
extern bool AttackDir[MAXAttack];	//�U���̌��� 0�F���@�P:�E

void EnemyAttck();