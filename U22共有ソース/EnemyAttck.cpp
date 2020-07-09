#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"
#include"map.h"
#include"main.h"

/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {
	
	//ƒvƒŒƒCƒ„[‚ªˆê’è”ÍˆÍ‚É“ü‚Á‚Ä‚«‚½‚ç“®‚«‚ğ~‚ß‚é
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.x - Enemy.Move + Enemy.Perception + Enemy.size>player.px
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//UŒ‚‚ÌÀ•W
		Enemy.Attck = true;//UŒ‚‚ğ•`‰æ‚·‚é‚½‚ß‚Ìƒtƒ‰ƒO
	}
	
	//ƒvƒŒƒCƒ„[‚ª“G‚ÌUŒ‚”ÍˆÍ“à‚É“ü‚Á‚½‚çUŒ‚
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD + msx, Enemy.y, Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		Enemy.ax -= (4);//UŒ‚‚ğˆÚ“®‚·‚é
	}
	if (Enemy.ax >= WIDTH || Enemy.ax + 40 <= 0 - msx)
	{
		//DeleteGraph(Enemy.Attackimage[0]);
		Enemy.Attck = false;
	}
}