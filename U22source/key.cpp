#include "key.h"

/***********************************************
 * �O���[�o���ϐ��̒�`
 ***********************************************/
int g_KeyFlg;
int g_OldKey;
int g_NowKey;
int Pad1;

//Pad1 = GetJoypadInputState(DX_INPUT_PAD1);

void key (){
	//���̓L�[�擾
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;
}