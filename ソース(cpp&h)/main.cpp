#include "DxLib.h"
#include "sounds.h"
#include "images.h"
#include "GameInit.h"
#include "map.h"
#include "notes.h"
#include "player.h"
#include "time.h"
#include "key.h"

/***********************************************
 * 関数のプロトタイプ宣言
 ***********************************************/

void GameMain(void);		//ゲームメイン処理

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("マップ");
	ChangeWindowMode(TRUE);		// ウィンドウモードで起動
	//SetGraphMode(1280, 850, 32);
	SetGraphMode(1280, 850, 32, 600);

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return -1;	//画像読み込み関数を呼び出

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		key();

		ClearDrawScreen();		// 画面の初期化
		switch (g_GameState) {
		case 1:
			GameInit();         //初期化
			break;
		case 2:
			GameMain();			//ゲームメイン処理
			break;
		}

		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}
/***********************************************
 * ゲームメイン
 ***********************************************/
void GameMain(void)
{
	DrawMap();
	PlayerMove();
	notesjudge();
	notes();
	TimeDisp();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", p_x);
	//DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //プレイヤーのbox
}
