#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"

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

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				Enemy.MapX = x;//敵のマップ上のｘ座標を入れる
				Enemy.MapY = y;//敵のマップ上のy座標を入れる
				Enemy.x = (x * 40);//敵の初期x座標
				Enemy.y = (y * 40);//敵の初期y座標
				Enemy.HP = Enemy.MaxHP;
				Enemy.direction = 0;
				Enemy.Attck = false;//攻撃するためのフラグ:0なら範囲外：１なら範囲内
				Enemy.drawf = 1;	//0非表示　１表示
				Enemy.HPdrawf = false;	//敵のHP表示フラグ
			}
		}
	}
	airman.Airmaninit();//エアーマンの初期化
	Air.AirInit();//エアーマンの攻撃の初期化
}