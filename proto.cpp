#include "DxLib.h"
#include <string>
/**************************
*	列挙体の宣言		  *
**************************/
typedef enum GAME_MODE {
	GAME_TITLE,
	GAME_INIT,
	GAME_END,
	GAME_MAIN,
	GAME_OVER,
	GAME_CLEAR,
	STAGE_CLEAR,
	RAKKA,
	LINE,
	MEMO,
	END = 99
};

const int HEIGHT = 5;
const int WIDTH = 8;

//変数の宣言
int MouseX;		//マウスX座標
int MouseY;		//マウスY座標
int gameover;
int SE1, SE2, SE3, SE4, SE5;
int gamestate = GAME_INIT;
int	g_OldKey;				// 前回の入力キー
int	g_NowKey;				// 今回の入力キー
int	g_KeyFlg;				// 入力キー情報
int g_NowKey2;

int nx[10]; //ノーツの座標
int cnt;
int nf[10];//フラグ
int bcnt;	//ブレンドのカウント

//関数の宣言
void GameMain(void);
void notes(void);

void stage(void);
void GameInit(void);
//void playermove(void);
void Stageclear(void);
void animation(void);
void animeInit(void);
void rakka(void);
void pinit(void);
void gameclear(void);
void Gameover(void);

int LoadImages();			//画像読み込み
int LoadSounds();	//音楽読み込み

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	ChangeWindowMode(TRUE);		//ウィンドウモード設定

	//SetDrawScreen(DX_SCREEN_BACK);	//描画先画面を裏にする
	SetBackgroundColor(255,255,255);

	if (DxLib_Init() == -1)	return -1;	//DXライブラリ初期化処理
	SetGraphMode(800, 600, 16);	//画面サイズ

	if (LoadImages() == -1)return -1;	//画像読み込み関数を呼び出し

	if (LoadSounds() == -1)return -1;	//サウンド読み込み関数を呼び出し

	while (ProcessMessage() == 0 && gamestate != 99 && !(g_NowKey& PAD_INPUT_START)) {
		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_NowKey = g_NowKey & ~g_OldKey;

		//マウスの位置を取得
		//GetMousePoint(&MouseX, &MouseY);

		ClearDrawScreen();		// 画面の初期化

		switch (gamestate) {
		case GAME_MAIN:
			GameMain();
			break;
		case GAME_TITLE:
			break;
		case GAME_INIT:
			GameInit();
			break;
		case GAME_OVER:
			Gameover();
			break;
		case STAGE_CLEAR:
			Stageclear();
			break;
		case RAKKA:
			stage();
			rakka();
			break;
		case GAME_CLEAR:
			gameclear();
			break;
		case MEMO:
			break;
		}
	}
	cnt = 0;

	DxLib_End();		//DXライブラリ使用の終了処理

	return 0;			//ソフトの終了
}
/********************
*初期処理
********************/
void GameInit(void) {
	gamestate = GAME_MAIN;	//メインに移動
}
void animeInit(void) {
}
/********************
*メイン
********************/
void GameMain(void) {
	notes();
}

/********************
*ノーツ
********************/
void notes(void) {

	DrawBox(0, 550, 800, 600, 0x000000, TRUE);	//下の枠
	int maxn = 4;	//表示するノーツ数の数
	int widthn = 100; //ノーツとノーツの間隔

	cnt++;
	for (int i = 0; i < maxn; i++) {
		if (cnt / 300 > i*widthn)
			nx[i]++;
	}
	for (int i = 0; i < maxn; i++) {
		if (nx[i]/ 300 != 400 && nx[i] != 0) {	//真ん中に来たら
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i]/300);	//透明度
			if (nf[i] == 0) {
				DrawLine(nx[i]/300, 550, nx[i]/300, 600, 0x99FFFF, 8);
				DrawLine(800 - nx[i]/300, 550, 800 - nx[i]/300 , 600, 0x99FFFF, 8);
			}
			if (g_NowKey & PAD_INPUT_1 && nx[i] / 300 >= 370 && nf[maxn] == 0) {	//Zキーを押したら
				nf[i] = 1;	//フラグ
				nf[maxn] = 1;
				nx[maxn] = nx[i];
			}
		}
		else {
			nx[i] = 0;
			nf[i] = 0;
		}
		if (nf[i] == 1 || nf[maxn] == 1 && bcnt != 255) {
			if (cnt % 300 == 0) {
				bcnt++;
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - bcnt);
			DrawLine(nx[maxn] / 300, 550, nx[maxn] / 300, 600, 0x00FF00, 8);
			DrawLine(800 - nx[maxn] / 300, 550, 800 - nx[maxn] / 300, 600, 0x00FF00, 8);
		}
		else {
			bcnt = 0;
			nf[maxn] = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/********************
*転がるアニメーション
********************/
void animation(void) {
}
/********************
*プレイヤーの出現
********************/
void rakka(void) {
}
/********************
*ステージクリア処理
********************/
void Stageclear(void) {
}
/********************
*ゲームクリア処理
********************/
void gameclear(void) {
}
/********************
*ゲームオーバー
********************/
void Gameover(void) {
}
/********************
*ステージ
********************/
void stage(void) {
}
void pinit(void) {
}
/**********************************************
*  画像読み込み
***********************************************/
int LoadImages()
{
	return 0;
}
/***************************************
* サウンド読み込み
****************************************/
int LoadSounds() {
	return 0;
}