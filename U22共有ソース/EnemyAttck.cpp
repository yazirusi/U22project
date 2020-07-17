#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

const int AttackSpeed = 3;
const int AttackAmount = 3;
int count = 0;
int j = 0;

/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {
	SetFontSize(30);
	DrawFormatString(100, 300, 0xffffff, "%d", count);
	DrawFormatString(100, 330, 0xffffff, "%d", j);
	DrawFormatString(100, 360, 0xffffff, "%d", Enemy.Attck);
	//ƒvƒŒƒCƒ„[‚ªˆê’è”ÍˆÍ‚É“ü‚Á‚Ä‚«‚½‚ç“®‚«‚ğ~‚ß‚é
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		 ) {
		if (Enemy.Attck == false && Hitcheck(Enemy.x, Enemy.y, Enemy.direction) != 1 
			&& Enemy.drawf == 1) {
			for (int i = 0; i < AttackAmount; i++)
			{
				Enemy.ax[i] = Enemy.x - Enemy.Move - 40;//UŒ‚‚ÌÀ•W
			}
			Enemy.Attck = true;//UŒ‚‚ğ•`‰æ‚·‚é‚½‚ß‚Ìƒtƒ‰ƒO
			Enemy.speed = 0;//“G‚ÌˆÚ“®—Ê‚ğ‚O‚É‚·‚é
			//Enemy.MoveFlg = true;//ƒGƒlƒ~[‚Ì“®‚«‚ğ~‚ß‚é
			//count++;
		}
	}
	else 
	{
		Enemy.speed = 1;//“G‚ÌˆÚ“®—Ê‚ğ–ß‚·
		//Enemy.MoveFlg = false;//ƒGƒlƒ~[‚ğ“®‚©‚·
	}
	
	//ƒvƒŒƒCƒ„[‚ª“G‚ÌUŒ‚”ÍˆÍ“à‚É“ü‚Á‚½‚çUŒ‚
	if (Enemy.Attck == true) {
		//if (Hitcheck(Enemy.ax[j], Enemy.y, Enemy.direction) != 1) {//“G‚ÌUŒ‚‚ª•Ç‚É“–‚½‚Á‚½‚çÁ‚·ˆ—
			if (count < 60 * AttackAmount) {
				count++;
				if (count % 60 == 0) {
					j++;
				}
			}
			for (int i = 0; i < j; i++)
			{
				DrawGraph(Enemy.ax[i] - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
				Enemy.ax[i] -= (AttackSpeed);//UŒ‚‚ğˆÚ“®‚·‚é
			}
		//}
		//else {
			//Enemy.Attck = false;//UŒ‚‚ğ‚È‚­‚·
		//}
	}
	//“G‚ÌUŒ‚‚ª‰æ–ÊŠO‚És‚Á‚½‚çÁ‚·ˆ—
	for (int i = 0; i < AttackAmount; i++)
	{
		if (Hitcheck(Enemy.ax[i], Enemy.y, Enemy.direction) == 1) {
			Enemy.ax[i] = 0;
			//Enemy.Attck = false;//UŒ‚‚ğ‚È‚­‚·
		}
		if (Enemy.ax[i] >= WIDTH || Enemy.ax[i] + 40 <= 0 - msx)
		{
			Enemy.ax[i] = 0;
			//DeleteGraph(Enemy.Attackimage[0]);
			//Enemy.Attck = false;
		}
		if (Enemy.ax[AttackAmount - 1] == 0)
		{
			j = 0;
			count = 0;//“G‚ÌUŒ‚‚ğ‰Šú‰»‚·‚é
			Enemy.Attck = false;//“G‚ÌUŒ‚‚ğ«‚ß‚³‚¹‚é
		}
	}
}