#include "DxLib.h"
#include "sounds.h"
#include "images.h"
#include "GameInit.h"
#include "map.h"
#include "notes.h"
#include "player.h"
#include "time.h"
#include "key.h"
#include "EnemyMove.h"
#include "EnemyAttck.h"
#include "PlayerAttack.h"
#include "BackgroundMove.h"
#include "main.h"
#include <time.h>
#include <stdio.h>

/***********************************************
 * 関数のプロトタイプ宣言
 ***********************************************/

void GameMain(void);		//ゲームメイン処理

/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("U22");
	ChangeWindowMode(TRUE);		// ウィンドウモードで起動
	//SetGraphMode(1280, 850, 32);
	SetGraphMode(1280, 850, 32, 600);

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return -1;	//画像読み込み関数を呼び出

	if (LoadSounds() == -1)return -1;


	//時間の読み込み
	time_t jikan = time(NULL);
	struct tm imanojikan;

	errno_t error;

	error = localtime_s(&imanojikan, &jikan);

	//ファイルの読み込み
	FILE* fp;

	SaveData_t Data;

	fopen_s(&fp,"time.txt", "r");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

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
		//最終更新日の表示
		SetFontSize(32);
		DrawFormatString(50, 5, 0x000000, "更新日時　%d月 %d日 %d時　%d分", Data.month, Data.day, Data.hour, Data.min);
		DrawFormatString(1000, 5, 0x000000, "ESC:終了");
		SetFontSize(16);

		ScreenFlip();			// 裏画面の内容を表画面に反映

	}
	/*//更新日を書き込む
	Data = { imanojikan.tm_mon + 1, imanojikan.tm_mday,imanojikan.tm_hour,imanojikan.tm_min };

	fopen_s(&fp, "time.txt", "w");//ファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる*/


	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}
/***********************************************
 * ゲームメイン
 ***********************************************/
void GameMain(void)
{
	BackScrool();
	DrawMap();
	//BackScrool();
	PlayerMove();
	EnemyMove();
	//DrawMap();
	EnemyAttck();
	notesjudge();
	notes();
	PlayerAttack();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", player.p_x);
	//DrawBox(39 * player.p_x, 39 * p_y, 39 * player.p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //プレイヤーのbox
}
