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
#include "GameTitle.h"
#include "GameOver.h"
#include "pause.h"

/***********************************************
 * 関数のプロトタイプ宣言
 ***********************************************/

void DrawGameTitle(void);
void GameMain(void);		//ゲームメイン処理
void DrawGameOver(void);		//ゲームオーバー画面処理
void BossStage(void);		//ボスステージへの移動
void FpsTimeFanction(void);
void wait_fanc(void);
void Pause(void);

int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
double Fps = 0.0;

double t = 0, ave = 0, f[60];

int count = 0;
bool debug = false;

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

	fopen_s(&fp,"time.txt", "rb");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

	double dNextTime = GetNowCount();
	int RefreshTime = 0;

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		key();

		/*//Qキーを押したら敵とプレイヤーが復活(デバッグ用)
		if (g_NowKey & PAD_INPUT_L) {
			player.hp = 100;
			Enemy.drawf = 1;
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
		}*/

		RefreshTime = GetNowCount();            //今の時間を取得

		ClearDrawScreen();		// 画面の初期化
		if (count > 120) {
			switch (g_GameState) {
			case 0:
				DrawGameTitle();
				break;
			case 1:
				GameInit();         //初期化
				break;
			case 2:
				GameMain();			//ゲームメイン処理
				break;
			case 3:
				DrawGameOver();			//ゲームオーバー処理
				break;
			case 4:
				BossStage();
				break;
			case 5:
				Pause();	//pause画面への移動
				break;
			}
		}
		//最終更新日の表示
		SetFontSize(32);
		DrawFormatString(50, 5, 0x000000, "更新日時　%d月 %d日 %d時　%d分", Data.month, Data.day, Data.hour, Data.min);
		DrawFormatString(1000, 5, 0x000000, "ESC:終了");
		SetFontSize(16);
		if (debug == true) {
			for (int i = 0; i < 10; i++)
			{
				DrawFormatString(100, 100 + i * 30, 0xffffff, "%d", airman[i].x);
			}

			DrawFormatString(200, 130, 0xffffff, "%d", airman[0].x);
			DrawFormatString(200, 160, 0xffffff, "%d", airman[0].y);
			DrawFormatString(200, 190, 0xffffff, "%d", airman[0].Jump);
			DrawFormatString(200, 210, 0xffffff, "%d", airman[0].JumpFlg);
			DrawFormatString(200, 240, 0xffffff, "%d", airman[0].JumpCount);
			DrawFormatString(200, 270, 0xffffff, "%d", Enemy[50].x);

			DrawFormatString(300, 200, 0x000000, "%d", Enemy[0].x);
			DrawFormatString(300, 230, 0x000000, "%d", AttackFlg[0]);
			DrawFormatString(300, 260, 0x000000, "%d", AttackFlg[1]);
			DrawFormatString(300, 290, 0x000000, "%d", player.px);
			DrawFormatString(300, 320, 0x000000, "%d", Air[0].Downx);
			DrawFormatString(300, 350, 0x000000, "%d", Air[0].Upx);
			DrawFormatString(200, 270, 0xffffff, "a[0]%f", EnemyAttackX[0]);
			DrawFormatString(200, 300, 0xffffff, "a[1]%f", EnemyAttackX[1]);

			for (int i = 0; i < 5; i++)
			{
				DrawFormatString(300, 100 + i * 30, 0xff0000, "%d", AttackFlg[i]);
			}

			static int x, y;
			GetMousePoint(&x, &y);
			DrawFormatString(30, 400, 0xffffff, "x%d", x);
			DrawFormatString(30, 430, 0xffffff, "y%d", y);

			if (ave != 0) {
				SetFontSize(32);
				DrawFormatString(565, 460, GetColor(255, 255, 255), "%.1fFPS", 1000.0 / (double)ave);
				DrawFormatString(565, 480, GetColor(255, 255, 255), "%fms", ave);
			}
		}

		/*for (int i = 0; i < 5000000; i++) {//わざと処理を重くするやつ

		}*/

		//RefreshTime = GetNowCount();            //今の時間を取得
		FpsTimeFanction();	//フレームレート表示
		count++;
		ScreenFlip();			// 裏画面の内容を表画面に反映
		//wait_fanc();

		counter++;

		while (GetNowCount() - RefreshTime < 20);//1周の処理が20ミリ秒(50fps)になるまで待つ

		/*dNextTime += 16.66;
		if (dNextTime > GetNowCount()) {
			WaitTimer((int)dNextTime - GetNowCount());
		}*/

	}
	//更新日を書き込む
	Data = { imanojikan.tm_mon + 1, imanojikan.tm_mday,imanojikan.tm_hour,imanojikan.tm_min };

	fopen_s(&fp, "time.txt", "wb");//ファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

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
	EnemyMove();
	EnemyAttck();
	//BackScrool();
	PlayerAttack();
	PlayerMove();
	//DrawMap();
	notesjudge();
	notes();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", player.p_x);
	//DrawBox(39 * player.p_x, 39 * p_y, 39 * player.p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //プレイヤーのbox
	//4810 4860 7380 7420
	if (g_KeyFlg & PAD_INPUT_3 /*&& player.px > 7380 && player.px < 7420*/) {	//ラスボス
		g_stage = 1;	//マップチップ
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
	SetFontSize(27);
	DrawString(995, 780, "Yボタンで、操作説明", 0xffffff);
	if (g_KeyFlg & PAD_INPUT_4) {
		StopSoundMem(rockBGM);
		g_GameState = 5;
	}
}

void FpsTimeFanction() {
	/*if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1周目の時間取得
	if (FpsTime_i == 59) {
		FpsTime[1] = GetNowCount();               //50周目の時間取得
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
		FpsTime_i = 0;//カウントを初期化
	}
	else
		FpsTime_i++;//現在何周目かカウント
	if (Fps != 0)
		SetFontSize(32);
		DrawFormatString(565, 460, 0x000000, "FPS %.1f", Fps); //fpsを表示
	return;*/


	int i;

	f[count % 60] = GetNowCount() - t;
	t = GetNowCount();
	if (count % 60 == 59) {
		ave = 0;
		for (i = 0; i < 60; i++)
			ave += f[i];
		ave /= 60;
	}
	return;
}
void wait_fanc() {
	double term;
	static double t = 0;
	term = GetNowCount() - t;
	if (16 - term > 0)
		Sleep(16 - term);
	t = GetNowCount();
	return;
}
