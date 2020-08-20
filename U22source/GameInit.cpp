#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"
#include "EnemyAttck.h"
#include "sounds.h"

//定義
int	g_GameState = 0;		// ゲームステータス

//Airman airman;

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		g_GameState = 2;

		PlayerInit();
		ScroolInit();

		//ノーツの初期化
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}

		EnemyInit();

		for (int i = 0; i < MAXEnemy; i++) {
			airman[i].Airmaninit();//エアーマンの初期化
			Air[i].AirInit();//エアーマンの攻撃の初期化
		}
	}
	else {
		StopSoundMem(rockBGM);
		PlayerInit();
		ScroolInit();
		EnemyInit();
		for (int i = 0; i < MAXEnemy; i++) {
			airman[i].Airmaninit();//エアーマンの初期化
		}

		//ノーツの初期化
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}
		g_GameState = 4;
	}
}