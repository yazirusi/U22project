////メニューカーソル移動処理
//if (g_KeyFlg & PAD_INPUT_DOWN) {
//	if (++g_MenuNumber > 2) g_MenuNumber = 0;
//}
//if (g_KeyFlg & PAD_INPUT_UP) {
//	if (--g_MenuNumber < 0) g_MenuNumber = 2;
//}
//
////Ｚキーでメニュー選択
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 0) g_GameState = 2;			//ゲームメイン
//if (g_KeyFlg & PAD_INPUT_A && g_MenuNumber == 1) g_GameState = 6;			//ランキング
////タイトル画像表示
//DrawGraph(0, 0, g_TitleImage, FALSE);
//
////メニューカーソル（三角形）の表示
//g_MenuY = g_MenuNumber * 52;
//DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);

//g_WaitTime++;		//時間の取得
//if (g_WaitTime == 60) {
//	Time++;
//	g_WaitTime = 0;
//	timecnt = Time;
//
//}
//else if (g_stage >= 4) {
//	Time += 0;
//}
//SetFontSize(30);
//DrawFormatString(590, 20, 0xffffff, "%d", Time);
//timecnt += 0;
//Time = 0;
//timecnt = 0;