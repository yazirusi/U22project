#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {
	
	//ƒvƒŒƒCƒ„[‚ªˆê’è”ÍˆÍ‚É“ü‚Á‚Ä‚«‚½‚ç“®‚«‚ğ~‚ß‚é
	if (Enemy.x - Enemy.Move - Enemy.MoveD - Enemy.Perception < px + 40/*&&Enemy.x + Enemy.Perception > px*/
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - Enemy.MoveD - 40;//UŒ‚‚ÌÀ•W
		Enemy.Attck = true;//UŒ‚‚ğ•`‰æ‚·‚é‚½‚ß‚Ìƒtƒ‰ƒO
	}
	if (Enemy.Attck == true) {
		DrawBox(Enemy.ax, Enemy.y, Enemy.ax + 40, Enemy.y + 40, 0xffffff, TRUE);//UŒ‚‚ğ•`‰æ‚·‚é
		Enemy.ax -= (1);//UŒ‚‚ğˆÚ“®‚·‚é
	}
}