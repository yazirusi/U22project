#include "DxLib.h"
#include "sounds.h"
#include "images.h"
#include "GameInit.h"
#include "notes.h"
#include "player.h"
#include "key.h"
#include "PlayerAttack.h"
#include "GameTitle.h"
#include "GameOver.h"
#include "BossStage.h"
#include "map.h"

void BossStage(void) {
	DrawMap();
	PlayerMove();
	notesjudge();
	notes();
	PlayerAttack();
}