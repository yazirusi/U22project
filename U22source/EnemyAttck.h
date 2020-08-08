#pragma once
#include"DxLib.h"

const int MAXAttack = 30;	//•\¦‚·‚éUŒ‚‚ÌÅ‘åŒÂ”
extern int EnemyAttackX[MAXAttack];//“G‚ÌUŒ‚‚Ì‚˜À•W
extern int EnemyAttackY[MAXAttack];//“G‚ÌUŒ‚‚ÌYÀ•W
extern int Attackheight[MAXAttack];
extern bool AttackFlg[MAXAttack];
extern bool AttackDir[MAXAttack];	//UŒ‚‚ÌŒü‚« 0F¶@‚P:‰E

void EnemyAttck();