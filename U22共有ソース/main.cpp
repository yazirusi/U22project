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
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/

void GameMain(void);		//�Q�[�����C������

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("U22");
	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
	//SetGraphMode(1280, 850, 32);
	SetGraphMode(1280, 850, 32, 600);

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return -1;	//�摜�ǂݍ��݊֐����Ăяo

	if (LoadSounds() == -1)return -1;


	//���Ԃ̓ǂݍ���
	time_t jikan = time(NULL);
	struct tm imanojikan;

	errno_t error;

	error = localtime_s(&imanojikan, &jikan);

	//�t�@�C���̓ǂݍ���
	FILE* fp;

	SaveData_t Data;

	fopen_s(&fp,"time.txt", "r");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

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
		//�ŏI�X�V���̕\��
		SetFontSize(32);
		DrawFormatString(50, 5, 0x000000, "�X�V�����@%d�� %d�� %d���@%d��", Data.month, Data.day, Data.hour, Data.min);
		DrawFormatString(1000, 5, 0x000000, "ESC:�I��");
		SetFontSize(16);

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}
	//�X�V������������
	/*Data = { imanojikan.tm_mon + 1, imanojikan.tm_mday,imanojikan.tm_hour,imanojikan.tm_min };

	fopen_s(&fp, "time.txt", "w");//�o�C�i���t�@�C�����J��
	if (fp == NULL) {//�G���[���N������NULL��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
	fclose(fp);//�t�@�C�������*/


	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}
/***********************************************
 * �Q�[�����C��
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
	//DrawBox(39 * player.p_x, 39 * p_y, 39 * player.p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
}
