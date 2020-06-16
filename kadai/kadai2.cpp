///********************************************************************
//**	一筆書きゲーム
//********************************************************************/
//#include "DxLib.h"
//#include <time.h>
//#define STAGE 5
//#define HEIGHT 20
//#define WIDTH 20
//#define RANKING_DATA 5
///***********************************************
// * 変数の宣言
// ***********************************************/
//int g_KeyFlg;  //入力キー情報
//int	g_OldKey;  // 前回の入力キー
//int	g_NowKey;	// 今回の入力キー
//
//int g_MenuNumber = 0;
//int g_MenuY;				// メニューカーソルのＹ座標
//
//int	g_TitleImage;			// 画像用変数
//int g_JIkiImage;			//プレイヤー画像用変数
//int g_KuriahaikeiImage;		//ステージクリア背景
//int g_RankingImage;			//ランキング画像用変数
//
//int ClickSound;				//クリックしたときの音
//int StageSound;			//ステージ内BGM
////	//sougen-d.mp3をメモリへ読み込みサウンドハンドルをTitleSoundに保存します
//int p_x, p_y;  //プレイヤーの座標
//
//int	g_GameState = 0;		// ゲームステータス
//int frame_count = 0;        //フレームカウント
//int disp_flg = 1;
//int RetryCount = 0;      //　　リトライの回数カウント
//int clearstage = 0;
//int g_stage = 0;   //ステージ管理
//int map[HEIGHT][WIDTH];
//int x, y;
//int	g_WaitTime = 0;			// 待ち時間
//int Time = 0;
//int timecnt;
//
//int	g_StageData[STAGE][HEIGHT][WIDTH] = {
//{	//0ステージ
//	{3,3,3,3,3,3,3,3,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,0,3,0,0,0,0,0,3},
//	{3,0,3,0,3,0,3,3,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,3,3,0,3,0,3,0,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,0,3,0,3,0,3,3,3},
//	{3,0,0,0,3,0,0,2,3},
//	{3,3,3,3,3,3,3,3,3},
//},
//{	//1ステージ
//	{3,3,3,3,3,3,3,3,3},
//	{3,3,0,0,0,0,0,0,3},
//	{3,3,0,3,0,3,0,0,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,0,0,3,0,3,0,3,3},
//	{3,0,0,3,0,3,0,3,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,3,0,3,0,0,0,0,3},
//	{3,0,0,0,0,0,0,3,3},
//	{3,0,3,0,0,0,0,0,3},
//	{3,0,0,0,0,3,3,0,3},
//	{3,3,3,3,3,3,3,0,3},
//	{3,2,0,0,0,0,0,0,3},
//	{3,3,3,3,3,3,3,3,3},
//},
//{	//2ステージ
//	{3,3,3,3,3,3,3,3,3,3},
//	{3,0,0,0,3,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,2,3},
//	{3,3,3,0,3,0,3,0,3,3},
//	{3,0,0,0,0,0,0,0,3,3},
//	{3,0,3,0,3,0,3,3,3,3},
//	{3,0,0,0,0,0,0,0,3,3},
//	{3,3,3,0,3,0,3,0,3,3},
//	{3,0,0,0,0,0,0,0,3,3},
//	{3,0,3,0,3,0,3,3,3,3},
//	{3,0,0,0,0,0,0,0,3,3},
//	{3,0,0,0,3,0,0,0,3,3},
//	{3,3,3,3,3,3,3,3,3,3},
//},
//{	//3ステージ
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//	{3,0,0,3,3,0,0,0,0,0,3,3,0,0,3},
//	{3,0,0,0,0,3,0,0,0,0,0,3,0,0,3},
//	{3,3,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,3,0,0,0,3,0,3,0,0,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,3,0,0,0,3,0,3,2,3,0,0,0,0,3},
//	{3,0,0,0,0,0,0,3,3,3,0,0,0,3,3},
//	{3,0,0,0,0,3,0,3,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,3,0,0,3,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,3,0,0,3,0,0,3,0,0,0,3},
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//},
//{	//4ステージ
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//	{3,0,0,3,3,0,0,0,0,0,3,3,0,0,3},
//	{3,0,0,0,0,3,0,0,0,0,0,3,0,0,3},
//	{3,3,0,0,0,0,0,0,3,0,0,0,0,0,3},
//	{3,3,0,0,0,0,0,0,0,0,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,3,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,3,0,3},
//	{3,0,0,3,0,0,0,3,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,3,0,0,0,0,0,0,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,3,0,0,3,2,3,0,0,3,0,0,3},
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//},
//};
////ランキングデータ（構造体）
//struct	RankingData {
//	int		no;
//	char	name[11];
//	long	time;
//};
////ランキングデータ変数宣言
//struct RankingData	g_Ranking[RANKING_DATA];
///***********************************************
// * 関数のプロトタイプ宣言
// ***********************************************/
//void GameInit(void);		//ゲーム初期化処理
//void GameMain(void);		//ゲームメイン処理
//void DrawGameTitle(void);   //タイトル      
//void DrawMap();             //マップ描画
//void PlayerMove();          //プレイヤー移動
//int ClearCheck();           //クリア判定
//void StageClear();			//ステージクリア処理
//void GameClear();			//ゲームクリア処理
//void StageReset();           //Rを押したらステージリセット
//void mapcopy();				//各ステージの初期値を保存する
//void StageClear();			//ステージクリア処理
//void Wtime(void);			//時間計測
//
//void DrawRanking(void);		//ランキング描画処理
//void InputRanking(void);	//ランキング入力
//void SortRanking(void);		//ランキング並べ替え
//int SaveRanking(void);		//ランキングデータの保存
//int ReadRanking(void);		//ランキングデータ読み込み
////int LoadImages();		//画像読み込み
///***********************************************
// * プログラムの開始
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//
//	// タイトルを test に変更
//	SetMainWindowText("ぬりつぶし");
//
//	ChangeWindowMode(TRUE);		// ウィンドウモードで起動
//	SetGraphMode(640, 590, 32);
//
//	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
//
//	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
//
//	SetFontSize(20);		// 文字サイズを設定
//		//タイトル画像データの読み込み
//	if ((g_TitleImage = LoadGraph("images/kadaiTitle.png")) == -1) return -1;
//	//タイトル画像データの読み込み
//	if ((g_JIkiImage = LoadGraph("images/jiki 2.png")) == -1) return -1;
//	if ((g_KuriahaikeiImage = LoadGraph("images/kuriahaikei.png")) == -1) return -1;
//	ClickSound = LoadSoundMem("sounds/switch1.mp3");
//    StageSound = LoadSoundMem("sounds/lovelyflower.mp3");
//	//if (LoadImages() == -1)return-1;	//画像読み込み関数を呼び出し
//
//	// ゲームループ
//	while (ProcessMessage() == 0 && g_GameState != 99) {
//
//		// 入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();		// 画面の初期化
//
//		switch (g_GameState) {
//		case 0:
//			DrawGameTitle();	//タイトル描画処理
//			break;
//		case 1:
//			mapcopy();			//ステージのコピー 
//		case 2:
//			GameInit();         //初期化
//			break;
//		case 3:
//			GameMain();			//ゲームメイン処理
//			break;
//		case 4:
//			StageClear();			//ステージクリア処理
//
//			break;
//		case 5:
//			GameClear();			//ゲームクリア処理
//			break;
//		case 6:
//			DrawRanking();	//ランキング描画処理
//			break;
//		case 7:
//			InputRanking();	//ランキング入力処理
//			break;
//		}
//
//		ScreenFlip();			// 裏画面の内容を表画面に反映
//
//	}
//
//	DxLib_End();	// DXライブラリ使用の終了処理
//
//	return 0;	// ソフトの終了
//}
///***********************************************
// * ゲーム初期処理
// ***********************************************/
//void GameInit(void)
//{
//	if (g_stage == 0) {
//		p_x = 7;
//		p_y = 8;
//	}
//	else if (g_stage == 1) {
//		p_x = 1;
//		p_y = 12;
//	}
//	else if (g_stage == 2) {
//		p_x = 8;
//		p_y = 2;
//	}
//	else if (g_stage == 3) {
//		p_x = 8;
//		p_y = 6;
//	}
//	else if (g_stage == 4) {
//		p_x = 7;
//		p_y = 13;
//	}
//	RetryCount = 0;
//
//	g_GameState = 3;	// ゲームメイン処理へ
//	mapcopy();
//}
///************************************
//*タイトル
//************************************/
//void DrawGameTitle(void) {
//
//	////タイトル画像表示
//	//DrawGraph(0, 0, g_TitleImage, FALSE);
//	//if (g_KeyFlg & PAD_INPUT_M) {
//	//	g_GameState = 1;	// ゲームメイン処理へ
//	//	PlaySoundMem(ClickSound, DX_PLAYTYPE_BACK);
//	//}
//
//
//	//SetFontSize(40);
//	//DrawString(40, 300, "\"ＳＰＡＣＥキー\"を\n              押してください", 0xffffff);
//	//メニューカーソル移動処理
//	
//if (g_KeyFlg & PAD_INPUT_DOWN) {
//	if (++g_MenuNumber > 2) g_MenuNumber = 0;
//	
//}
//if (g_KeyFlg & PAD_INPUT_UP) {
//	if (--g_MenuNumber < 0) g_MenuNumber = 2;
//	
//}
//
////Ｚキーでメニュー選択
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 0) g_GameState = 2;			//ゲームメイン
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 1) g_GameState = 6;			//ランキング
////タイトル画像表示
//DrawGraph(0, 0, g_TitleImage, FALSE);
////メニューカーソル（三角形）の表示
//g_MenuY = g_MenuNumber * 52;
//DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);
//SetFontSize(20);
//DrawString(120, 400, "スタート""ランキング", 0xffffff);
//}
//
///***********************************************
// * ゲームメイン
// ***********************************************/
//void GameMain(void)
//{
//	PlaySoundMem(StageSound, DX_PLAYTYPE_LOOP,FALSE);
//	Wtime();
//	StageReset();
//	PlayerMove();
//	DrawMap();
//	//SetFontSize(30);
//	//DrawFormatString(590, 20, 0xffffff, "%d", Time);
//	if (ClearCheck() == 1) {
//		g_GameState = 4;       //ステージクリア
//
//	}
//	if (g_stage == 4) {
//		if (ClearCheck() == 1) {
//			g_GameState = 5;    //ゲームクリア
//		}
//	}
//	DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage,TRUE);
//	//DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, g_JIkiImage, TRUE); //プレイヤーのbox
//
//}
///***********************************
//*マップ表示
//***********************************/
//void DrawMap() {
//
//	for (int y = 0; y < HEIGHT; y++) {   //
//		for (int x = 0; x < WIDTH; x++) {
//			if (map[y][x] == 1) {
//				DrawBox(39 * x, 39 * y, 39 * x + 39, 39 * y + 39, 0x2222ff, TRUE);
//			}
//			else if (map[y][x] == 2) {
//
//				DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage,TRUE);
//			}
//			else if (map[y][x] == 3) {
//				DrawBox(39 * x, 39 * y, 39 * x + 39, 39 * y + 39, 0x22aa33, TRUE);
//			}
//		}
//	}
//}
///*******************************
//*プレイヤーの移動処理
//********************************/
//void PlayerMove() {
//	//上下左右移動
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		while (map[p_y - 1][p_x] != 3) {
//			ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_y -= 1;
//			DrawMap();
//			DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage,TRUE);
//			Wtime();
//			ScreenFlip();
//			WaitTimer(25);
//		}
//	}
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		while (map[p_y + 1][p_x] != 3) {
//			ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_y += 1;
//			DrawMap();
//			DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage, TRUE);		
//			Wtime();
//			ScreenFlip();
//			WaitTimer(25);
//		}
//	}
//	if (g_KeyFlg & PAD_INPUT_LEFT) {
//		while (map[p_y][p_x - 1] != 3) {
//			ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_x -= 1;
//			DrawMap();
//			DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage, TRUE);
//			Wtime();
//			ScreenFlip();
//			WaitTimer(25);
//		}
//	}
//	if (g_KeyFlg & PAD_INPUT_RIGHT) {
//		while (map[p_y][p_x + 1] != 3) {
//			ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_x += 1;
//			DrawMap();
//			DrawGraph(39 * p_x, 39 * p_y, g_JIkiImage, TRUE);
//			Wtime();
//			ScreenFlip();
//			WaitTimer(25);
//		}
//	}
//
//	//WaitTimer(300);
//}
//
///***********************************
//*クリア判定
//***********************************/
//int ClearCheck() {
//	int cnt = 0;
//
//	for (y = 0; y < HEIGHT; y++) {   //
//		for (x = 0; x < WIDTH; x++) {
//			if (map[y][x] != 0) {
//				cnt++;
//			}
//		}
//	}
//	if (cnt == 90 && g_stage == 0) {
//		return 1;   //１で全て埋まったとき
//	}
//	else if (cnt == 126 && g_stage == 1) {
//		return 1;
//	}
//	else if (cnt == 130 && g_stage == 2) {
//		return 1;
//	}
//	else if (cnt == 225 && g_stage == 3) {
//		return 1;
//	}
//	else if (cnt == 225 && g_stage == 4) {
//		return 1;
//	}
//	return 0;
//}
///*********************************
//*ゲームクリア処理
//*********************************/
//void GameClear() {
//	DrawGraph(0, 0, g_KuriahaikeiImage, FALSE);
//	//再生を止める			
//	StopSoundMem(StageSound);
//	frame_count++;
//	if (frame_count % 30 == 0) {
//		disp_flg = !disp_flg;
//	}
//	if (disp_flg == 1) {
//		timecnt += 0;
//		SetFontSize(20);
//		DrawString(150, 400, "\"Z\"を押したらタイトルへ", 0xffffff);
//		SetFontSize(30);
//		DrawFormatString(590, 20, 0xffffff, "%d", timecnt);
//	}
//	SetFontSize(64);                             //サイズを64に変更
//	SetFontThickness(8);                         //太さを8に変更
//	DrawString(170, 200, "Game Clear!", 0xffffff);
//	SetFontSize(30);
//	DrawFormatString(120, 300, 0xffffff, "あなたのクリアタイムは%d秒です。", timecnt);
//	if (g_KeyFlg & PAD_INPUT_1) {
//		PlaySoundMem(ClickSound, DX_PLAYTYPE_BACK);
//		g_GameState = 0;
//		g_stage = 0;
//		Time = 0;
//		timecnt = 0;
//	}
//
//}
///***************************************
//*Rキーを押したらステージの状態リセット
//***************************************/
//void StageReset(void) {
//	if (CheckHitKey(KEY_INPUT_R)) {
//		for (int i = 0; i < 7; i++) {
//			for (int j = 0; j < 7; j++) {
//				map[i][j] = g_StageData[g_stage][i][j];
//			}
//		}
//		GameInit();
//	}
//}
///***************************************
//*マップコピー
//***************************************/
//void mapcopy() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			map[i][j] = g_StageData[g_stage][i][j];
//		}
//	}
//}
//
///**************************************
//*ステージクリア処理
//**************************************/
//void StageClear() {
//	StopSoundMem(StageSound); //bgmを止める
//	DrawGraph(0, 0, g_KuriahaikeiImage, FALSE);
//	frame_count++;
//	if (frame_count % 30 == 0) {
//		disp_flg = !disp_flg;
//	}
//	if (disp_flg == 1) {
//		SetFontSize(20);
//		DrawString(150, 300, "\"ＳＰＡＣＥキー\"を押したら次のステージへ", 0xffffff);
//	}
//	SetFontSize(64);                             //サイズを64に変更
//	SetFontThickness(8);                         //太さを8に変更
//	DrawString(170, 200, "StageClear!", 0xffffff);
//
//
//	if (g_KeyFlg & PAD_INPUT_M) {
//		PlaySoundMem(ClickSound, DX_PLAYTYPE_BACK);
//		g_GameState = 2;
//		if (++g_stage > 4);
//
//	}
//}
///*********************************************************************
//*時間計測
//*********************************************************************/
//void Wtime(void) {
//	g_WaitTime++;		//時間の取得
//	if (g_WaitTime == 60) {
//		Time++;
//		g_WaitTime = 0;
//		timecnt = Time;
//
//	}
//	else if (g_stage >= 4) {
//		Time += 0;
//	}
//	SetFontSize(30);
//	DrawFormatString(590, 20, 0xffffff, "%d", Time);
//}
///**************************************************************
//*ゲームランキング描画表示
//**************************************************************/
//void DrawRanking(void) {
//	//スペースキーでメニューに戻る
//	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;
//
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//ランキング一覧表示
//	SetFontSize(18);
//	for (int i = 0; i < RANKING_DATA; i++) {
//		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-10s %10d",
//			g_Ranking[i].no,
//			g_Ranking[i].name,
//			g_Ranking[i].time);
//	}
//	DrawString(100, 450, "---- スペースキーを押してタイトルへ戻る　----", 0xffffff, 0);
//}
///**********************************************************
//*ランキング入力処理
//***********************************************************/
//void InputRanking(void) {
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//フォントサイズの設定
//	SetFontSize(20);
//
//	//名前入力指示文字列の描画
//	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
//	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);
//
//	//名前の入力
//	DrawString(150, 310, "> ", 0xFFFFFF);
//	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[4].name, FALSE) == 1) {
//		g_Ranking[4].time = timecnt;	// ランキングデータの１０番目にスコアを登録
//		SortRanking();		// ランキング並べ替え
//		SaveRanking();		// ランキングデータの保存
//		g_GameState = 2;		// ゲームモードの変更
//	}
//}
///*************************************************************
//*ランキング並べ替え
//**************************************************************/
//void SortRanking(void) {
//	int i, j;
//	RankingData work;
//
//	//選択法ソート
//	for (i = 0; i < 9; i++) {
//		for (j = i + 1; j < 10; j++) {
//			if (g_Ranking[i].time <= g_Ranking[j].time) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//
//	//順位付け
//	for (i = 0; i < 5; i++) {
//		g_Ranking[i].no = 1;
//	}
//	// 得点が同じ場合は、同じ順位とする
//	 //同順位があった場合の次の順位はデータ個数が加算された順位とする
//	for (i = 0; i < 9; i++) {
//		for (j = i + 1; j < 10; j++) {
//			if (g_Ranking[i].time > g_Ranking[j].time) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
///************************************************************
//*ランキングデータの保存
//************************************************************/
//int SaveRanking(void) {
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL) {
//		/* エラー処理 */
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ分配列データを書き込む
//	for (int i = 0; i < 5; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].time);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
///*************************************************************
//*ランキングデータ読み込み
//*************************************************************/
//int ReadRanking(void) {
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL) {
//		//エラー処理
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ配分列データを読み込む
//	for (int i = 0; i < 5; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].time);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//	//ランキングデータの読み込み
//	if (ReadRanking() == -1)return -1;
//}
//
