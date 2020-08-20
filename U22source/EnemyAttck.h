#pragma once
#include"DxLib.h"

const int MAXAttack = 30;	//•\¦‚·‚éUŒ‚‚ÌÅ‘åŒÂ”
extern double EnemyAttackX[MAXAttack];//“G‚ÌUŒ‚‚Ì‚˜À•W
extern double EnemyAttackY[MAXAttack];//“G‚ÌUŒ‚‚ÌYÀ•W
extern double EnemyAttackRot[MAXAttack];	//“G‚ÌUŒ‚‚ªi‚ŞŠp“x
extern int Attackheight[MAXAttack];
extern bool AttackFlg[MAXAttack];
extern bool AttackDir[MAXAttack];	//UŒ‚‚ÌŒü‚« 0F¶@‚P:‰E
extern int AttackType[MAXAttack];	//“G‚ÌUŒ‚‚Ìí—Ş
extern int AttackBoss[3];

void EnemyAttck();
int EnemyAttackType(int i);