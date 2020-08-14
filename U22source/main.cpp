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

/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/

void DrawGameTitle(void);
void GameMain(void);		//�Q�[�����C������
void DrawGameOver(void);		//�Q�[���I�[�o�[��ʏ���
void BossStage(void);		//�{�X�X�e�[�W�ւ̈ړ�
void FpsTimeFanction(void);

int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
double Fps = 0.0;

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

	fopen_s(&fp,"time.txt", "rb");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	fclose(fp);

	double dNextTime = GetNowCount();
	int RefreshTime = 0;

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		key();

		/*//Q�L�[����������G�ƃv���C���[������(�f�o�b�O�p)
		if (g_NowKey & PAD_INPUT_L) {
			player.hp = 100;
			Enemy.drawf = 1;
			for (int y = 0; y < MAPHEIGHT; y++) {
				for (int x = 0; x < MAPWIDTH; x++) {
					if (g_StageData[0][y][x] == 3) {
						Enemy.MapX = x;//�G�̃}�b�v��̂����W������
						Enemy.MapY = y;//�G�̃}�b�v���y���W������
						Enemy.x = (x * 40);//�G�̏���x���W
						Enemy.y = (y * 40);//�G�̏���y���W
					}
				}
			}
		}*/

		ClearDrawScreen();		// ��ʂ̏�����
		switch (g_GameState) {
		case 0 :
			DrawGameTitle();
			break;
		case 1:
			GameInit();         //������
			break;
		case 2:
			GameMain();			//�Q�[�����C������
			break;
		case 3:
			DrawGameOver();			//�Q�[���I�[�o�[����
			break;
		case 4:
			BossStage();
			break;
		}
		//�ŏI�X�V���̕\��
		SetFontSize(32);
		DrawFormatString(50, 5, 0x000000, "�X�V�����@%d�� %d�� %d���@%d��", Data.month, Data.day, Data.hour, Data.min);
		DrawFormatString(1000, 5, 0x000000, "ESC:�I��");
		SetFontSize(16);

		//RefreshTime = GetNowCount();            //���̎��Ԃ��擾

		FpsTimeFanction();	//�t���[�����[�g�\��

		counter++;
		while (GetNowCount() - RefreshTime < 17);//1���̏�����17�~���b�ɂȂ�܂ő҂�

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
		dNextTime += 16.66;
		if (dNextTime > GetNowCount()) {
			WaitTimer((int)dNextTime - GetNowCount());
		}

	}
	/*//�X�V������������
	Data = { imanojikan.tm_mon + 1, imanojikan.tm_mday,imanojikan.tm_hour,imanojikan.tm_min };

	fopen_s(&fp, "time.txt", "wb");//�t�@�C�����J��
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
	EnemyMove();
	EnemyAttck();
	//BackScrool();
	PlayerMove();
	//DrawMap();
	notesjudge();
	notes();
	PlayerAttack();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", player.p_x);
	//DrawBox(39 * player.p_x, 39 * p_y, 39 * player.p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
	//4810 4860 7380 7420
	if (g_KeyFlg & PAD_INPUT_3 && player.px > 7380 && player.px < 7420) {
		g_stage = 1;	//�}�b�v�`�b�v
		StopSoundMem(rockBGM);
		PlayerInit();
		ScroolInit();

		//�m�[�c�̏�����
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}
		g_GameState = 4;
	}
}

void FpsTimeFanction() {
	if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1���ڂ̎��Ԏ擾
	if (FpsTime_i == 49) {
		FpsTime[1] = GetNowCount();               //50���ڂ̎��Ԏ擾
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
		FpsTime_i = 0;//�J�E���g��������
	}
	else
		FpsTime_i++;//���݉����ڂ��J�E���g
	if (Fps != 0)
		SetFontSize(32);
		DrawFormatString(565, 460, 0x000000, "FPS %.1f", Fps); //fps��\��
	return;
}
