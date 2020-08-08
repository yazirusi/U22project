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

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				for (int i = 0; i < MAXEnemy; i++) {
					if (Enemy[i].x == 0) {	//空きのある配列に代入する
						Enemy[i].MapX = x;//敵のマップ上のｘ座標を入れる
						Enemy[i].MapY = y;//敵のマップ上のy座標を入れる
						Enemy[i].x = (x * 40);//敵の初期x座標
						Enemy[i].y = (y * 40);//敵の初期y座標
						Enemy[i].HP = Enemy[i].MaxHP;
						Enemy[i].direction = 0;
						Enemy[i].drawf = 1;	//0非表示　１表示
						Enemy[i].HPdrawf = false;	//敵のHP表示フラグ
						for (int a = 0; a < MAXAttack; a++) {
							Attackheight[a] = 25;
							AttackFlg[a] = false;//攻撃するためのフラグ:0なら範囲外：１なら範囲内
						}
						break;
					}
				}
			}
		}
	}
	airman.Airmaninit();//エアーマンの初期化
	Air.AirInit();//エアーマンの攻撃の初期化
}