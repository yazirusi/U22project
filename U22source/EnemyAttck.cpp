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
#include"sounds.h"

int Attackheight[MAXAttack]; //= 25;//UŒ‚‚™À•W‚ÌˆÚ“®—Ê(GameInit‚Å25‘ã“ü)
const int AttackSpeed = 5;//UŒ‚‚˜À•W‚ÌˆÚ“®—Ê
const double RotAttackSpd = 2;	//©ƒLƒƒƒ‰‚ÉŒü‚©‚Á‚Ä‚­‚éUŒ‚‚Ì‘¬“x
//const int AttackAmount = 3;//
const int Gravity = 1;//d—Í
double EnemyAttackX[MAXAttack];//UŒ‚‚Ì‚˜À•W
double EnemyAttackY[MAXAttack];//UŒ‚‚Ì‚™À•W
double EnemyAttackRot[MAXAttack];	//“G‚ÌUŒ‚‚ªi‚ŞŠp“x
bool AttackFlg[MAXAttack];	//UŒ‚•\¦ƒtƒ‰ƒO
bool AttackDir[MAXAttack];	//UŒ‚‚ÌŒü‚« 0F¶@‚P:‰E
int AttackType[MAXAttack];	//“G‚ÌUŒ‚‚Ìí—Ş
int AttackBoss[3];	//ƒ‰ƒXƒ{ƒX“Á—L‚ÌUŒ‚—p”z—ñ
int k;
ENEMY Enemy[MAXEnemy];
//Airman airman;

/***************
*Airman‚ÌUŒ‚
***************/
void Airman::AirmanAttack() {
	//ƒGƒA[ƒ}ƒ“‚Ì¶‘¤‚ÌŠ´’m”ÍˆÍ
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

	//ƒGƒA[ƒ}ƒ“‚Ì‰E‘¤‚ÌŠ´’m”ÍˆÍ
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
			DrawGraph(EnemyAttackX[i] + sx, EnemyAttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
			if (AttackDir[i] == false) {
				if (Enemy[0].type == 2) {//ƒ‰ƒXƒ{ƒX‚¾‚Á‚½‚ç
					EnemyAttackX[i] -= 5;
				}
				EnemyAttackX[i] -= 3;
			}
			else {
				if (Enemy[0].type == 2) {//ƒ‰ƒXƒ{ƒX‚¾‚Á‚½‚ç
					EnemyAttackX[i] += 5;
				}
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
		/*DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		Upx -= 3;
		if (Hitcheck(Upx, Upy, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
			Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
			Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
			0 - sx >= Upx || Upx >= 1280 - sx) {
			DispFlg[1] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
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
	//	DrawGraph(Downx + sx, Downy, EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
	//	Downx -= 3;
	//	if (Hitcheck(Downx, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy, 0, false) == 1 ||
	//		Hitcheck(Downx, Downy + 20, 0, false) == 1 ||
	//		Hitcheck(Downx + 20, Downy + 20, 0, false) == 1 ||
	//		0 - sx >= Downx || Downx >= 1280 - sx && DispFlg[0] == true) {
	//		DispFlg[0] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
	//		Downx = 0;
	//		Downy = 0;
	//	}
	//}
	//if (/*Upx != 0 && Upy != 0 &&*/ DispFlg[1] == true) {
	//	DrawGraph(Upx + sx, Upy, EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
	//	Upx -= 3;
	//	if (Hitcheck(Upx, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy, 0, false) == 1 ||
	//		Hitcheck(Upx, Upy + 20, 0, false) == 1 ||
	//		Hitcheck(Upx + 20, Upy + 20, 0, false) == 1 ||
	//		0 - sx >= Upx || Upx >= 1280 - sx && DispFlg[1] == true) {
	//		DispFlg[1] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
	//		Upx = 0;
	//		Upy = 0;
	//	}
	//}

	return 0;
}
/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {

	for (int i = 0; i < MAXEnemy; i++) {
		airman[i].AirmanAttack();

		//Enemy.MoveFlg;
		//“G‚ª€‚Ê‚©A•\¦ƒtƒ‰ƒO‚ª”ñ•\¦‚È‚ç
		if (Enemy[i].HP <= 0 || Enemy[i].drawf == false) {
			continue;	//‚±‚±‚©‚ç‰º‚Ìˆ—‚ğ‚µ‚È‚¢
		}
		if (CheckSoundMem(rockBGM) == 0) {//‹È‚ª—¬‚ê‚Ä‚¢‚È‚©‚Á‚½‚çˆ—‚ğ‚µ‚È‚¢
			continue;
		}

		//“G‚ÌUŒ‚ŠÔŠu
		if (Enemy[i].AttackInterval > 0) {
			Enemy[i].AttackInterval--;
		}

		//Enemy[i].speed = 1;
		if (Enemy[i].type == 0) {
			Enemy[i].MoveFlg = true;
		}

		//ƒ‰ƒXƒ{ƒX‚ÌUŒ‚(ƒ‰ƒ“ƒ_ƒ€‚ÅG‹›“G‚ÌUŒ‚‚ğ‚·‚é)
		if (Enemy[i].type == 2) {
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//“G‚Ì‚˜À•W‚ğ“ü‚ê‚é
					EnemyAttackY[a] = Enemy[i].y;//“G‚Ì‚™À•W‚ğ“ü‚ê‚é
					AttackDir[a] = Enemy[i].direction;	//“G‚ÌUŒ‚‚ÌŒü‚«
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ŠÔŠu
					AttackType[a] = GetRand(2);	//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ƒpƒ^[ƒ“
					if (AttackType[a] == 0) {	//•ú•¨ü‚ÌUŒ‚‚È‚ç‚R‚Â“¯‚É”ò‚Î‚·
						for (int j = 1; j < 3; j++) {
							AttackFlg[a + j] = true;
							EnemyAttackX[a + j] = Enemy[i].x;//“G‚Ì‚˜À•W‚ğ“ü‚ê‚é
							EnemyAttackY[a + j] = Enemy[i].y;//“G‚Ì‚™À•W‚ğ“ü‚ê‚é
							AttackDir[a + j] = Enemy[i].direction;	//“G‚ÌUŒ‚‚ÌŒü‚«
							AttackType[a + j] = 0;
							AttackBoss[j - 1] = a + j;
						}
					}
					if (AttackType[a] == 2) {
						if (GetRand(1) == 0) {
							EnemyAttackY[a] -= 80;//ƒGƒA[ƒ}ƒ“‚ÌUŒ‚‚Ì‰º‚ÌUŒ‚
						}
						else {
							EnemyAttackY[a] += 80;//ƒGƒA[ƒ}ƒ“‚ÌUŒ‚‚Ìã‚ÌUŒ‚
						}
					}
					double taX = (double)player.px - EnemyAttackX[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(X)
					double taY = (double)player.py - EnemyAttackY[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//©ƒLƒƒƒ‰‚Æ“G‚ÌUŒ‚‚ÌŠp“x
					break;
				}
			}
		}

		if (g_stage == 1) {
			continue;	//ƒ‰ƒXƒ{ƒXí‚È‚ç‰º‚Ìˆ—‚ğ‚µ‚È‚¢
		}

		//“G‚ÌË’ö”ÍˆÍ“à‚É‚¢‚½‚ç(¶)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			//Enemy[i].speed = 0;//“G‚Ì“®‚«‚ğ~‚ß‚é
			Enemy[i].MoveFlg = false;//“G‚Ì“®‚«‚ğ~‚ß‚é
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//“G‚Ì‚˜À•W‚ğ“ü‚ê‚é
					EnemyAttackY[a] = Enemy[i].y;//“G‚Ì‚™À•W‚ğ“ü‚ê‚é
					AttackDir[a] = Enemy[i].direction;	//“G‚ÌUŒ‚‚ÌŒü‚«
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ŠÔŠu
					AttackType[a] = Enemy[i].type;	//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ƒpƒ^[ƒ“
					double taX = (double)player.px - EnemyAttackX[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(X)
					double taY = (double)player.py - EnemyAttackY[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//©ƒLƒƒƒ‰‚Æ“G‚ÌUŒ‚‚ÌŠp“x
					break;
				}
			}
		}
		//‰E
		if (Enemy[i].x + Enemy[i].Perception > player.px
			&& Enemy[i].x < player.px
			&& Enemy[i].direction == true) {
			//Enemy[i].speed = 0;//“G‚Ì“®‚«‚ğ~‚ß‚é
			Enemy[i].MoveFlg = false;//“G‚Ì“®‚«‚ğ~‚ß‚é
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
					PlaySoundMem(attackse, DX_PLAYTYPE_BACK, TRUE);
					AttackFlg[a] = true;
					EnemyAttackX[a] = Enemy[i].x;//“G‚Ì‚˜À•W‚ğ“ü‚ê‚é
					EnemyAttackY[a] = Enemy[i].y;//“G‚Ì‚™À•W‚ğ“ü‚ê‚é
					AttackDir[a] = Enemy[i].direction;	//“G‚ÌUŒ‚‚ÌŒü‚«
					Enemy[i].AttackInterval = Enemy[i].MAXAttackInterval[Enemy[i].type];//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ŠÔŠu
					AttackType[a] = Enemy[i].type;	//“G‚Ìí—Ş‚²‚Æ‚ÌUŒ‚ƒpƒ^[ƒ“
					double taX = (double)player.px - EnemyAttackX[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(X)
					double taY = (double)player.py - EnemyAttackY[a];	//©ƒLƒƒƒ‰‚Ü‚Å‚Ì‹——£(Y)
					EnemyAttackRot[a] = atan2(taY, taX);	//©ƒLƒƒƒ‰‚Æ“G‚ÌUŒ‚‚ÌŠp“x
					break;
				}
			}
		}
		/*//ˆêŒÂ‚àUŒ‚ƒtƒ‰ƒO‚ª–³‚©‚Á‚½‚ç“®‚­
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
		if (AttackFlg[i] == true) {//ƒtƒ‰ƒO‚ªtrue‚È‚ç“ü‚é
			//UŒ‚ƒpƒ^[ƒ“‚²‚Æ‚Ì“®‚«
			EnemyAttackType(i);

			if (AttackType[i] != 1) {	//1‚Í•ÇŠÑ’Ê‚·‚éUŒ‚
				//UŒ‚‚Ì’n–Ê‚â•Ç‚Ì“–‚½‚è”»’è
				if (Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1 ||
					Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], false) == 1) {
					AttackFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
					Attackheight[i] = 25;//UŒ‚‚ÌˆÚ“®—Ê‚ğ‰Šú‰»‚·‚é
					AttackType[i] = 0;	//UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
				}
			}

			//UŒ‚‚ª‰æ–ÊŠO‚És‚Á‚½‚ç‰Šú‰»
			if (-sx > EnemyAttackX[i] + 20 || -sx + WIDTH < EnemyAttackX[i]
				|| EnemyAttackY[i] + 20 < 0 || EnemyAttackY[i] + 20 > HEIGHT - 90) {
				AttackFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
				Attackheight[i] = 25;//UŒ‚‚ÌˆÚ“®—Ê‚ğ‰Šú‰»‚·‚é
				AttackType[i] = 0;	//UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
			}

			//UŒ‚‚ÌƒvƒŒƒCƒ„[‚Æ‚Ì“–‚½‚è”»’è
			if ((Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i], AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i], (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1 ||
				Hitcheck((int)EnemyAttackX[i] + 20, (int)EnemyAttackY[i] + 20, AttackDir[i], true) == 1)
				&& player.hit == false) {
				PlaySoundMem(attackse2, DX_PLAYTYPE_BACK, TRUE);
				//–hŒä‚µ‚Ä‚¢‚½‚ç
				if (player.protect == true) {
					//Perfect
					if (player.protecJudge == 1) {
						/*for (i = 0; i < MAXEnemy; i++) {
							Enemy[i].drawf = 0;	//“G‚ª”½Œ‚‚ğ‚à‚ç‚¤
						}*/
					}
					player.protect = false;//–hŒäI—¹
					AttackFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
					AttackType[i] = 0;	//UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
				}
				else {
					AttackFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
					Attackheight[i] = 25;//UŒ‚‚ÌˆÚ“®—Ê‚ğ‰Šú‰»‚·‚é
					AttackType[i] = 0;	//UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
					player.hp -= 20;//ƒvƒŒƒCƒ„[‚Ìhp‚ªŒ¸‚é
					player.hit = true;//UŒ‚‚ğH‚ç‚Á‚½ƒtƒ‰ƒO
					if (player.hp <= 0) {
						player.pcnt = 0;	//ˆê‰ñ‚¾‚¯‰Šú‰»
					}
				}
			}
		}
	}

	Air[Air[1].ReloadCount].AirMove(0, 0);

}
int EnemyAttackType(int i) {
	if (AttackType[i] == 0) {	//•ú•¨ü‚ÌUŒ‚
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		if (Enemy[0].type == 2) {//ƒ‰ƒXƒ{ƒX‚¾‚Á‚½‚ç

			EnemyAttackY[i] -= Attackheight[i];//UŒ‚‚ğã‚É“®‚©‚·
			if (AttackDir[i] == false) {
				if (AttackBoss[0] == i) {
					EnemyAttackX[i] -= AttackSpeed + 5;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
				}
				if (AttackBoss[1] == i) {
					EnemyAttackX[i] -= AttackSpeed + 10;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
				}
				if (AttackBoss[0] != i && AttackBoss[1] != i) {
					EnemyAttackX[i] -= AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
				}
			}
			/*else {
				EnemyAttackX[i] += AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
			}*/

			Attackheight[i] -= Gravity;//d—Í‚ğ“ü‚ê‚é
		}
		else {
			EnemyAttackY[i] -= Attackheight[i];//UŒ‚‚ğã‚É“®‚©‚·
			if (AttackDir[i] == false) {
				EnemyAttackX[i] -= AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
			}
			else {
				EnemyAttackX[i] += AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
			}

			Attackheight[i] -= Gravity;//d—Í‚ğ“ü‚ê‚é
		}
	}

	if (AttackType[i] == 1) {	//ƒvƒŒƒCƒ„[‚ÉŒü‚©‚Á‚Ä‚­‚éUŒ‚
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ

		if (Enemy[0].type == 2) {//ƒ‰ƒXƒ{ƒX‚¾‚Á‚½‚ç
			//ˆÚ“®—ÊŒvZ
			EnemyAttackX[i] += cos(EnemyAttackRot[i]) * (RotAttackSpd + 3.0);
			EnemyAttackY[i] += sin(EnemyAttackRot[i]) * (RotAttackSpd + 3.0);
		}
		else {
			//ˆÚ“®—ÊŒvZ
			EnemyAttackX[i] += cos(EnemyAttackRot[i]) * RotAttackSpd;
			EnemyAttackY[i] += sin(EnemyAttackRot[i]) * RotAttackSpd;
		}
	}

	return 0;
}