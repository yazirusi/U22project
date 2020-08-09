#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"
#include "EnemyAttck.h"

//定義
int	g_GameState = 0;		// ゲームステータス

//Airman airman;

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit()
{
	g_GameState = 2;

	PlayerInit();
	ScroolInit();

	//ノーツの初期化
	for (int i = 0; i < 100; i++) {
		notesinit(i);
	}

	EnemyInit();
	
	airman.Airmaninit();//エアーマンの初期化
	Air.AirInit();//エアーマンの攻撃の初期化
}