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
#include "Ending.h"
#include "sousa.h"

/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/

void DrawGameTitle(void);
void GameMain(void);		//�Q�[�����C������
void DrawGameOver(void);		//�Q�[���I�[�o�[��ʏ���
void BossStage(void);		//�{�X�X�e�[�W�ւ̈ړ�
void FpsTimeFanction(void);
void wait_fanc(void);
void Pause(void);
void Sousa(void);

int counter = 0, FpsTime[2] = { 0, }, FpsTime_i = 0;
double Fps = 0.0;

double t = 0, ave = 0, f[60];
bool soundsf = false;

int count = 0;
bool debug = false;

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

		RefreshTime = GetNowCount();            //���̎��Ԃ��擾
		if (g_GameState != 5) {
			ClearDrawScreen();		// ��ʂ̏�����
		}
		if (count > 120) {
			switch (g_GameState) {
			case 0:
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
			case 5:
				Pause();	//pause��ʂւ̈ړ�
				break;
			case 6:
				DrawEnding(); //�G���f�B���O����
				break;
			case 7:
				Sousa(); //�������
				break;
			}
		}
		//�ŏI�X�V���̕\��
		SetFontSize(32);
		DrawFormatString(50, 5, 0x000000, "�X�V�����@%d�� %d�� %d���@%d��", Data.month, Data.day, Data.hour, Data.min);
		DrawFormatString(1000, 5, 0x000000, "ESC:�I��");
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
			//DrawFormatString(200, 270, 0xffffff, "%d", Enemy[50].x);

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
			DrawFormatString(30, 460, 0xffffff, "px%d", player.px);

			if (ave != 0) {
				SetFontSize(32);
				DrawFormatString(565, 460, GetColor(255, 255, 255), "%.1fFPS", 1000.0 / (double)ave);
				DrawFormatString(565, 480, GetColor(255, 255, 255), "%fms", ave);
			}
		}

		/*for (int i = 0; i < 5000000; i++) {//�킴�Ə������d��������

		}*/

		//RefreshTime = GetNowCount();            //���̎��Ԃ��擾
		FpsTimeFanction();	//�t���[�����[�g�\��
		count++;
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
		//wait_fanc();

		counter++;

		while (GetNowCount() - RefreshTime < 20);//1���̏�����20�~���b(50fps)�ɂȂ�܂ő҂�

		/*dNextTime += 16.66;
		if (dNextTime > GetNowCount()) {
			WaitTimer((int)dNextTime - GetNowCount());
		}*/

	}
	//�X�V������������
	Data = { imanojikan.tm_mon + 1, imanojikan.tm_mday,imanojikan.tm_hour,imanojikan.tm_min };

	fopen_s(&fp, "time.txt", "wb");//�t�@�C�����J��
	if (fp == NULL) {//�G���[���N������NULL��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
	fclose(fp);//�t�@�C�������

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
	PlayerAttack();
	PlayerMove();
	//DrawMap();
	notesjudge();
	notes();
	//DrawFormatString(50, 100, 0xffffff, "%d", p_y);
	//DrawFormatString(50, 150, 0xffffff, "%d", player.p_x);
	//DrawBox(39 * player.p_x, 39 * p_y, 39 * player.p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
	//4810 4860 7380 7420
	if (g_KeyFlg & PAD_INPUT_3 && player.px > 7380 && player.px < 7420) {	//���X�{�X
		PlaySoundMem(doorse, DX_PLAYTYPE_BACK, TRUE);
		g_stage = 1;	//�}�b�v�`�b�v
		StopSoundMem(rockBGM);
		PlayerInit();
		ScroolInit();
		EnemyInit();
		PlayerAttackInit();
		for (int i = 0; i < MAXEnemy; i++) {
			airman[i].Airmaninit();//�G�A�[�}���̏�����
		}

		//�m�[�c�̏�����
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}
		g_GameState = 4;
	}
	//SetFontSize(27);
	//DrawString(995, 780, "Y�{�^���ŁA�������", 0xffffff);
	//if (g_KeyFlg & PAD_INPUT_4) {
	//StopSoundMem(rockBGM);
	//g_GameState = 5;
	//}
	if (g_KeyFlg & PAD_INPUT_8) {
		if (CheckSoundMem(rockBGM) == 1) {
			soundsf = true;
		}
		else {
			soundsf = false;
		}
		StopSoundMem(rockBGM);
		g_GameState = 5;
	}
}

void FpsTimeFanction() {
	/*if (FpsTime_i == 0)
		FpsTime[0] = GetNowCount();               //1���ڂ̎��Ԏ擾
	if (FpsTime_i == 59) {
		FpsTime[1] = GetNowCount();               //50���ڂ̎��Ԏ擾
		Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//���肵���l����fps���v�Z
		FpsTime_i = 0;//�J�E���g��������
	}
	else
		FpsTime_i++;//���݉����ڂ��J�E���g
	if (Fps != 0)
		SetFontSize(32);
		DrawFormatString(565, 460, 0x000000, "FPS %.1f", Fps); //fps��\��
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
