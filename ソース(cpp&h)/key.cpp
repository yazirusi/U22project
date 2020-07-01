#include "key.h"

/***********************************************
 * グローバル変数の定義
 ***********************************************/
int g_KeyFlg;
int g_OldKey;
int g_NowKey;

void key (){
	//入力キー取得
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
}