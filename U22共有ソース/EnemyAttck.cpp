#include"DxLib.h"
#include"EnemyMove.h"
#include"player.h"
#include"EnemyAttck.h"

/***************************************
*ƒGƒlƒ~[‚ÌUŒ‚
***************************************/
void EnemyAttck(void) {

	//ƒvƒŒƒCƒ„[‚ªˆê’è”ÍˆÍ‚É“ü‚Á‚Ä‚«‚½‚ç“®‚«‚ğ~‚ß‚é
	if (Enemy.x - Enemy.Move - Enemy.Perception < player.px + 40
		&& Enemy.Attck == false) {
		Enemy.ax = Enemy.x - Enemy.Move - 40;//UŒ‚‚ÌÀ•W
		Enemy.Attck = true;//UŒ‚‚ğ•`‰æ‚·‚é‚½‚ß‚Ìƒtƒ‰ƒO
	}
	//ƒvƒŒƒCƒ„[‚ª“G‚ÌUŒ‚”ÍˆÍ“à‚É“ü‚Á‚½‚çUŒ‚
	if (Enemy.Attck == true) {
		DrawGraph(Enemy.ax - Enemy.MoveD, Enemy.y, Enemy.Attackimage[0], TRUE);//“G‚ÌUŒ‚‚Ì•`‰æ
		Enemy.ax -= (2);//UŒ‚‚ğˆÚ“®‚·‚é
	}
}