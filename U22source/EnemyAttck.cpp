#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"
#include"notes.h"

int Attackheight = 25;//UŒ‚‚™À•W‚ÌˆÚ“®—Ê
const int AttackSpeed = 5;//UŒ‚‚˜À•W‚ÌˆÚ“®—Ê
//const int AttackAmount = 3;//
const int Gravity = 1;//d—Í
int EnemyAttackX;//UŒ‚‚Ì‚˜À•W
int EnemyAttackY;//UŒ‚‚Ì‚™À•W
int k;
ENEMY Enemy;
//Airman airman;

/***************
*Airman‚ÌUŒ‚
***************/
void Airman::AirmanAttack() {

	//DrawFormatString(50, 130, 0xffffff, "%d", sx);//“G‚Ì‚˜À•W
	//DrawFormatString(50, 160, 0xffffff, "%d", k);//“G‚Ì‚˜À•W

	for (int i = 0; i < Air_MAX; i++) {
		if (Air.DispFlg[i] == true) {//ƒtƒ‰ƒO‚ªtrue‚È‚ç“ü‚é
			DrawGraph(Airman::AttackX[i] - Airman::MoveD + sx, Airman::AttackY[i], Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
			Airman::AttackX[i] -= AttackSpeed;//“G‚ÌUŒ‚‚ğˆÚ“®

			//UŒ‚‚Ì’n–Ê‚â•Ç‚Ì“–‚½‚è”»’è
			if (Hitcheck(Airman::AttackX[i] - Airman::MoveD - sx, Airman::AttackY[i], Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Enemy.MoveD - sx, Airman::AttackY[i], Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] - Enemy.MoveD - sx, Airman::AttackY[i] + 20, Enemy.direction, false) == 1 ||
				Hitcheck(Airman::AttackX[i] + 20 - Enemy.MoveD - sx, Airman::AttackY[i] + 20, Enemy.direction, false) == 1 ||
				0 > Airman::AttackX[i] || Airman::AttackX[i] > 1280 && Air.DispFlg[i] == true) {
				Airman::AttackX[i] = Airman::x;//UŒ‚À•W‚ğ‰Šú‰»‚·‚é
				Airman::AttackY[i] = Airman::y;//UŒ‚‚ÌÀ•W‚ğ‰Šú‰»‚·‚é
				Air.DispFlg[i] = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
			}
			k = sx;
		}
	}
}
/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {
	//“G‚Ì€–S”»’è	0:€–S@1:•\¦
	if (Enemy.drawf == 0) {
		return;
	}
	Enemy.Moveflg;
	airman.AirmanAttack();

	//ƒRƒƒ“ƒg‰»‚µ‚Ä‚¢‚¢‚©‚ài‚²‚ß‚ñg‚í‚¹‚Ä‚à‚ç‚¢‚Ü‚·j
	if (Enemy.Attck == false) {//ƒtƒ‰ƒO‚ªfalse‚ÌƒvƒŒƒCƒ„[‚ÌÀ•W‚ğ‚¢‚ê‚é
		EnemyAttackX = Enemy.x;//“G‚Ì‚˜À•W‚ğ“ü‚ê‚é
		EnemyAttackY = Enemy.y;//“G‚Ì‚™À•W‚ğ“ü‚ê‚é
		Enemy.speed = 1;//“G‚ÌˆÚ“®—Ê‚ğ‰Šú‰»
	}

	//UŒ‚‚ª”­“®‚·‚é‚©Šm”F‚·‚é‚½‚ß‚Ì‚à‚Ì
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px) {
		Enemy.Attck = true;
	}
	else {
		Enemy.Attck = false;
	}

	if (Enemy.Attck == true) {//ƒtƒ‰ƒO‚ªtrue‚È‚ç“ü‚é
		Enemy.speed = 0;//“G‚Ì“®‚«‚ğ~‚ß‚é
		DrawGraph(EnemyAttackX - Enemy.MoveD + sx, EnemyAttackY, Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		EnemyAttackY -= Attackheight;//UŒ‚‚ğã‚É“®‚©‚·
		EnemyAttackX -= AttackSpeed;//UŒ‚‚ğ¶‚É“®‚©‚¹‚é
		Attackheight -= Gravity;//d—Í‚ğ“ü‚ê‚é
	}

	//UŒ‚‚Ì’n–Ê‚â•Ç‚Ì“–‚½‚è”»’è
	if (Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, false) == 1) {
		Enemy.Attck = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
		Attackheight = 25;//UŒ‚‚ÌˆÚ“®—Ê‚ğ‰Šú‰»‚·‚é
	}

	//UŒ‚‚ÌƒvƒŒƒCƒ„[‚Æ‚Ì“–‚½‚è”»’è
	if ((Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1 ||
		Hitcheck(EnemyAttackX + 20 - Enemy.MoveD, EnemyAttackY + 20, Enemy.direction, true) == 1) 
		&& player.hit == false) {
		//–hŒä‚µ‚Ä‚¢‚½‚ç
		if (player.protect == true) {
			//Perfect
			if (player.protecJudge == 1) {
				Enemy.drawf = 0;	//“G‚ª”½Œ‚‚ğ‚à‚ç‚¤
			}
			player.protect = false;//–hŒäI—¹
			Enemy.Attck = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
		}
		else {
			Enemy.Attck = false;//ƒtƒ‰ƒO‚ğoff‚É‚·‚é
			Attackheight = 25;//UŒ‚‚ÌˆÚ“®—Ê‚ğ‰Šú‰»‚·‚é
			player.hp -= 20;//ƒvƒŒƒCƒ„[‚Ìhp‚ªŒ¸‚é
			player.hit = true;//UŒ‚‚ğH‚ç‚Á‚½ƒtƒ‰ƒO
			if (player.hp <= 0) {
				player.pcnt = 0;	//ˆê‰ñ‚¾‚¯‰Šú‰»
			}
		}
	}

	////ƒvƒŒƒCƒ„[‚ªˆê’è”ÍˆÍ‚É“ü‚Á‚Ä‚«‚½‚ç“®‚«‚ğ~‚ß‚é
	//if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
	//	&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
	//	 ) {
	//	if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
	//		&& Enemy.drawf == 1) {
	//		for (int i = 0; i < AttackAmount; i++)
	//		{
	//			Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//UŒ‚‚ÌÀ•W
	//		}
	//		Enemy.Attck = true;//UŒ‚‚ğ•`‰æ‚·‚é‚½‚ß‚Ìƒtƒ‰ƒO
	//		Enemy.speed = 0;//“G‚ÌˆÚ“®—Ê‚ğ‚O‚É‚·‚é
	//		//Enemy.MoveFlg = true;//ƒGƒlƒ~[‚Ì“®‚«‚ğ~‚ß‚é
	//		//count++;
	//	}
	//}
	//else 
	//{
	//	Enemy.speed = 1;//“G‚ÌˆÚ“®—Ê‚ğ–ß‚·
	//	//Enemy.MoveFlg = false;//ƒGƒlƒ~[‚ğ“®‚©‚·
	//}
	//
	////ƒvƒŒƒCƒ„[‚ª“G‚ÌUŒ‚”ÍˆÍ“à‚É“ü‚Á‚½‚çUŒ‚
	//if (Enemy.Attck == true) {
	//	//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//“G‚ÌUŒ‚‚ª•Ç‚É“–‚½‚Á‚½‚çÁ‚·ˆ—
	//		if (count < 60 * AttackAmount) {
	//			count++;
	//			if (count % 60 == 0) {
	//				j++;
	//			}
	//		}
	//		for (int i = 0; i < j; i++)
	//		{
	//			DrawGraph(Enemy.ax[i] - Enemy.MoveD + sx, Enemy.y, Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
	//			Enemy.ax[i] -= (AttackSpeed);//UŒ‚‚ğˆÚ“®‚·‚é
	//		}
	//	//}
	//	//else {
	//		//Enemy.Attck = false;//UŒ‚‚ğ‚È‚­‚·
	//	//}
	//}
	////“G‚ÌUŒ‚‚ª‰æ–ÊŠO‚És‚Á‚½‚çÁ‚·ˆ—
	//for (int i = 0; i < AttackAmount; i++)
	//{
	//	if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
	//		Enemy.ax[i] = 0;
	//		//Enemy.Attck = false;//UŒ‚‚ğ‚È‚­‚·
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
	//		count = 0;//“G‚ÌUŒ‚‚ğ‰Šú‰»‚·‚é
	//		Enemy.Attck = false;//“G‚ÌUŒ‚‚ğ«‚ß‚³‚¹‚é
	//	}
	//}
}