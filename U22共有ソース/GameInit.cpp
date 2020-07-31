#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include"EnemyMove.h"

//定義
int	g_GameState = 0;		// ゲームステータス

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		//マップ配列のプレイヤー位置
		player.p_x = 1;
		player.p_y = 17;

		//プレイヤーの座標
		player.px = 40;
		player.py = 680;
		//player.py = 640;
	}
	//プレイヤーのステータスの初期化
	player.hp = 100;

	//ノーツの初期化
	for (int i = 0; i < 100; i++) {
		notesinit(i);
	}
	g_GameState = 2;

	for (int y = 0; y < MAPHEIGHT; y++) {
		for (int x = 0; x < MAPWIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				Enemy.MapX = x;//敵のマップ上のｘ座標を入れる
				Enemy.MapY = y;//敵のマップ上のy座標を入れる
				Enemy.x = (x * 40);//敵の初期x座標
				Enemy.y = (y * 40);//敵の初期y座標
			}
		}
	}
}