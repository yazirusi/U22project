
#include "DxLib.h"
//#define   _USE_MATH_DEFINES
//#include     <math.h>


#define HEIGHT  20  //11  縦
#define WIDTH  200  //15  横
#define STAGE  1



//  定数の宣言
const int  ENEMY_KAZU = 8;   //敵の最大数


typedef enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_MAIN,
	GAME_END,
	END = 99
};


//変数の宣言
int mb = 25;  //マップの大きさ
//プレーイヤー関係
int p_x, p_y; //playerの座標
int px, py;   //player描画座標
//int sp_y, spy;

int mx;  //マップ移動表示

int	g_OldKey;				// 前回の入力キー
int	g_NowKey;				// 今回の入力キー
int	g_KeyFlg;				// 入力キー情報

int g_OldKeyM;
int g_NowKeyM;
int g_KeyFlgM;


int g_stage = 0;
int	g_StageData[STAGE][HEIGHT][WIDTH] = {	// ブロック配列
	{	// 0ｽﾃｰｼﾞ
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		}
};

//エネミー関係
int g_WaitTime = 0;
struct ENEMY {
//	int flg; 
	int time;  //敵の移動タイミング
	int x, y; //敵の座標
};
struct ENEMY g_enemy[ENEMY_KAZU];
/*
struct PLAYER {
	int flg;     //使用フラグ
	int x, y;       //座標
	int w, h;       //幅:高さ
	int sp;         //スピード
	int jpf;      //ジャンプフラグ
	int 
};*/





//関数
void EnemyMove(void);     //敵の移動処理


void PlayerMove(void);       //playerの移動処理
void DrawMap(void);         //マップの移動処理
void DrawGameTitle(void);	//ゲームタイトル処理
void GameInit(void);		//ゲーム初期化処理
void GameMain(void);		//ゲームメイン処理
void DrawEnd(void);
int	g_GameState = 0;		// ゲームステータス



/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// タイトルを test に変更
	SetMainWindowText("敵の移動");

	SetGraphMode(1280, 850, 32);        //画面サイズ

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする


	SetFontSize(20);		// 文字サイズを設定

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		g_OldKeyM = g_NowKeyM;
		g_NowKeyM = GetMouseInput();
		g_KeyFlgM = g_NowKeyM & ~g_OldKeyM;


		ClearDrawScreen();		// 画面の初期化


		switch (g_GameState) {
		case GAME_TITLE:
			DrawGameTitle();	//ゲームタイトル処理
			break;
		case GAME_INIT:
			GameInit();		//ゲーム初期処理
			break;
		case GAME_MAIN:
			GameMain();	//ゲームメイン処理
			break;
		case GAME_END:
			DrawEnd();		//エンド画面描画処理
			break;
		}

		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}

/**************************************
*タイトル表示
***************************************/
void DrawGameTitle(void) {
	g_GameState = GAME_INIT;

}
//GAME初期処理
void GameInit(void)
{
	g_stage = 0;
	if (g_stage == 0) {//
		p_x = 1;
		p_y = 18;
		px = 40;
		py = 680;
	}
 //敵の位置を保存
	int ec = 0;    //敵の数をカウント

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (g_StageData[0][y][x] == 3) {
				g_enemy[ec].y = y;
				g_enemy[ec].x = x;
				g_enemy[ec].time = 0;
				ec += 1;
			}
		}
	}


	g_GameState = GAME_MAIN;

}
/*************************
*ゲームメイン
*************************/
void GameMain(void)
{
	PlayerMove();
	EnemyMove();
	DrawMap();

}
/*********************
*敵の移動処理（プレイヤーを追っかける）
**********************/
void EnemyMove(void) {

	//  60 = 1秒　
	if (++g_WaitTime > 30) {
		for (int i = 0; i < ENEMY_KAZU; i++) {
//			if (++g_enemy[i].time > 30) {
				if (p_x < g_enemy[i].x) {//プレイヤーよりも右にいるとき
					//左に移動する
					if (g_StageData[0][g_enemy[i].y][g_enemy[i].x - 1] == 0 || g_StageData[0][g_enemy[i].y][g_enemy[i].x - 1] == 3) {
						g_StageData[0][g_enemy[i].y][g_enemy[i].x] = 0;
						g_StageData[0][g_enemy[i].y][g_enemy[i].x - 1] = 3;
						g_enemy[i].x -= 1;
					}
				}
				else if (p_x > g_enemy[i].x) {//プレイヤーよりも左にいるとき
					//右に移動する
					if (g_StageData[0][g_enemy[i].y][g_enemy[i].x + 1] == 0 || g_StageData[0][g_enemy[i].y][g_enemy[i].x + 1] == 3) {
						g_StageData[0][g_enemy[i].y][g_enemy[i].x] = 0;
						g_StageData[0][g_enemy[i].y][g_enemy[i].x + 1] = 3;
						g_enemy[i].x += 1;
					}
				}
//				g_enemy[i].time = 0;
//			}
		}
		g_WaitTime = 0;

	}
}
/***************************
//マップ表示
****************************/
void DrawMap(void) {

	for (int y = 0; y < HEIGHT; y++) {   //
		for (int x = 0; x < WIDTH; x++) {
			if (g_StageData[0][y][x + mx] == 1) {
				DrawBox(mb * x,  mb * y, mb * x + mb,  mb * y + mb, 0x2222ff, TRUE);
			}
			else if (g_StageData[0][y][x + mx] == 2) {
				DrawBox(mb * x,  mb * y, mb * x + mb, mb * y + mb, 0xffffff, TRUE);
			}
			else if (g_StageData[0][y][x + mx] == 0) {
				DrawBox(mb * x,  mb * y, mb * x + mb, mb * y + mb, 0x22aa33, TRUE);
			}
			else if (g_StageData[0][y][x + mx] == 3) {
				DrawBox(mb * x,  mb * y, mb * x + mb,  mb * y + mb, 0xff0000, TRUE);
			}
		}
	}

	for (int y = 0; y < HEIGHT; y++) {   //ミニマップ
		for (int x = 0; x < WIDTH; x++) {
			SetFontSize(5);
			if (g_StageData[0][y][x] == 1) {//壁　足場など
				DrawFormatString( 6 * x, 500 + 6 * y, 0x00ffff, "%d", g_StageData[0][y][x]);
			}
			else if (g_StageData[0][y][x] == 2) {//プレイヤー
				DrawFormatString(6 * x, 500 + 6 * y, 0xffff00, "%d", g_StageData[0][y][x]);
			}
			else if (g_StageData[0][y][x] == 3) {//エネミー
				DrawFormatString(6 * x, 500 + 6 * y, 0xff0f00, "%d", g_StageData[0][y][x]);
			}
			else if (g_StageData[0][y][x] == 0) {//背景その他
				DrawFormatString(6 * x, 500 + 6 * y, 0x22aa33, "%d", g_StageData[0][y][x]);
			}
		}
	}
}
//プレイヤーの移動
void PlayerMove(void) {
	//上下左右移動

	if (g_KeyFlg & PAD_INPUT_LEFT) {
		if (g_StageData[0][p_y][p_x - 1] == 0 || g_StageData[0][p_y][p_x - 1] == 2 || g_StageData[0][p_y][p_x - 1] == 3) {
			g_StageData[0][p_y][p_x] = 0;
			g_StageData[0][p_y][p_x - 1] = 2;
			p_x -= 1;
			mx--;
		}
	}
	if (g_KeyFlg & PAD_INPUT_RIGHT) {
		if (g_StageData[0][p_y][p_x + 1] == 0 || g_StageData[0][p_y][p_x + 1] == 2 || g_StageData[0][p_y][p_x + 1] == 3) {
			g_StageData[0][p_y][p_x] = 0;
			g_StageData[0][p_y][p_x + 1] = 2;
			p_x += 1;
			mx++;
		}
	}

	//WaitTimer(300);
}

void DrawEnd(void) {

	g_GameState = END;
}
