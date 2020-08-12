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
int k;
ENEMY Enemy[MAXEnemy];
//Airman airman;

/***************
*Airman‚ÌUŒ‚
***************/
void Airman::AirmanAttack() {

	DrawFormatString(50, 130, 0xffffff, "%d", sx);//“G‚Ì‚˜À•W
	for (int i = 0; i < Air_MAX; i++)
	{
		DrawFormatString(50, 160+30*i, 0xffffff, "%d", Airman::AttackX[i]);//“G‚Ì‚˜À•W
	}

	for (int i = 0; i < Air_MAX; i++) {
		if (Air.DispFlg[i] == true) {//ƒtƒ‰ƒO‚ªtrue‚È‚ç“ü‚é
			DrawGraph(Airman::AttackX[i] - Airman::MoveD + sx, Airman::AttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
			Airman::AttackX[i] -= 3;//“G‚ÌUŒ‚‚ğˆÚ“®

			//UŒ‚‚Ì’n–Ê‚â•Ç‚Ì“–‚½‚è”»’è
			if (Hitcheck(Airman::AttackX[i] - Airman::MoveD , Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 10 - Airman::MoveD , Airman::AttackY[i], Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] - Airman::MoveD , Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Airman::MoveD , Airman::AttackY[i] + 20, Airman::direction, false) == 1 ||
				0-sx > Airman::AttackX[i] || Airman::AttackX[i] > 1280-sx && Air.DispFlg[i] == true) {
				//Airman::AttackX[i] = Airman::x;//UŒ‚À•W‚ğ‰Šú‰»‚·‚é
				//Airman::AttackY[i] = Airman::y;//UŒ‚‚ÌÀ•W‚ğ‰Šú‰»‚·‚é
				Air.DispFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
			}
		}
	}
}
/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {

	airman.AirmanAttack();

	for (int i = 0; i < MAXEnemy; i++) {
		//Enemy.MoveFlg;

		DrawFormatString(150, 200, 0x000000, "%d", Enemy[0].x);
		DrawFormatString(150, 230, 0x000000, "%d", AttackFlg[0]);
		DrawFormatString(150, 260, 0x000000, "%d", AttackFlg[1]);
		DrawFormatString(150, 290, 0x000000, "%d", player.px);

		//Enemy[i].speed = 1;
		if (Enemy[i].type == 0) {
			Enemy[i].MoveFlg = true;
		}

		//“G‚ÌË’ö”ÍˆÍ“à‚É‚¢‚½‚ç(¶)
		if (Enemy[i].x - Enemy[i].Perception < player.px + 40
			&& Enemy[i].x + 40 > player.px
			&& Enemy[i].direction == false) {
			//Enemy[i].speed = 0;//“G‚Ì“®‚«‚ğ~‚ß‚é
			Enemy[i].MoveFlg = false;//“G‚Ì“®‚«‚ğ~‚ß‚é
			for (int a = 0; a < MAXAttack; a++) {
				if (AttackFlg[a] == false && Enemy[i].AttackInterval == 0) {
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

		//“G‚ÌUŒ‚ŠÔŠu
		if (Enemy[i].AttackInterval > 0) {
			Enemy[i].AttackInterval--;
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
}
int EnemyAttackType(int i) {
	if (AttackType[i] == 0) {	//•ú•¨ü‚ÌUŒ‚
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		EnemyAttackY[i] -= Attackheight[i];//UŒ‚‚ğã‚É“®‚©‚·
		if (AttackDir[i] == false) {
			EnemyAttackX[i] -= AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
		}
		else {
			EnemyAttackX[i] += AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
		}

		Attackheight[i] -= Gravity;//d—Í‚ğ“ü‚ê‚é
	}

	if (AttackType[i] == 1) {	//ƒvƒŒƒCƒ„[‚ÉŒü‚©‚Á‚Ä‚­‚éUŒ‚
		DrawGraph((int)EnemyAttackX[i] + sx, (int)EnemyAttackY[i], EnemyAttackImg, TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ

		//ˆÚ“®—ÊŒvZ
		EnemyAttackX[i] += cos(EnemyAttackRot[i]) * RotAttackSpd;
		EnemyAttackY[i] += sin(EnemyAttackRot[i]) * RotAttackSpd;
	}

	return 0;
}