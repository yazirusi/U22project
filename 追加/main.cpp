#include "DxLib.h"
#include "sounds.h"
#include "images.h"
#include "GameInit.h"
#include "map.h"
#include "notes.h"
#include "player.h"
#include "time.h"
#include "key.h"
#include"EnemyMove.h"
#include"EnemyAttck.h"

/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/

void GameMain(void);		//�Q�[�����C������

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("�}�b�v");
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
	//SetGraphMode(1280, 850, 32);
	SetGraphMode(1280, 850, 32, 600);

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return -1;	//�摜�ǂݍ��݊֐����Ăяo

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		key();

		ClearDrawScreen();		// ��ʂ̏�����
		switch (g_GameState) {
		case 1:
			GameInit();         //������
			break;
		case 2:
			GameMain();			//�Q�[�����C������
			break;
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}
/***********************************************
 * �Q�[�����C��
 ***********************************************/
void GameMain(void)
{
	PlayerMove();
	EnemyMove();
	DrawMap();
	EnemyAttck();
	notesjudge();
	notes();
	TimeDisp();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", p_x);
	//DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
}
