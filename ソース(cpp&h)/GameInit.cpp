#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"

//定義
int	g_GameState = 1;		// ゲームステータス

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		//マップ配列のプレイヤー位置
		p_x = 1;
		p_y = 17;

		//プレイヤーの座標
		px = 40;
		py = 680;
	}

	//ノーツ位置の初期化
	for (int i = 0; i < 10; i++) {
		nx[i] = 200;
	}
	g_GameState = 2;
}