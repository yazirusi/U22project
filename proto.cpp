#include "DxLib.h"
#include <string>
/**************************
*	�񋓑̂̐錾		  *
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

//�ϐ��̐錾
int MouseX;		//�}�E�XX���W
int MouseY;		//�}�E�XY���W
int gameover;
int SE1, SE2, SE3, SE4, SE5;
int gamestate = GAME_INIT;
int	g_OldKey;				// �O��̓��̓L�[
int	g_NowKey;				// ����̓��̓L�[
int	g_KeyFlg;				// ���̓L�[���
int g_NowKey2;

int nx[10]; //�m�[�c�̍��W
int cnt;
int nf[10];//�t���O
int bcnt;	//�u�����h�̃J�E���g

//�֐��̐錾
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

int LoadImages();			//�摜�ǂݍ���
int LoadSounds();	//���y�ǂݍ���

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	ChangeWindowMode(TRUE);		//�E�B���h�E���[�h�ݒ�

	//SetDrawScreen(DX_SCREEN_BACK);	//�`����ʂ𗠂ɂ���
	SetBackgroundColor(255,255,255);

	if (DxLib_Init() == -1)	return -1;	//DX���C�u��������������
	SetGraphMode(800, 600, 16);	//��ʃT�C�Y

	if (LoadImages() == -1)return -1;	//�摜�ǂݍ��݊֐����Ăяo��

	if (LoadSounds() == -1)return -1;	//�T�E���h�ǂݍ��݊֐����Ăяo��

	while (ProcessMessage() == 0 && gamestate != 99 && !(g_NowKey& PAD_INPUT_START)) {
		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_NowKey = g_NowKey & ~g_OldKey;

		//�}�E�X�̈ʒu���擾
		//GetMousePoint(&MouseX, &MouseY);

		ClearDrawScreen();		// ��ʂ̏�����

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

	DxLib_End();		//DX���C�u�����g�p�̏I������

	return 0;			//�\�t�g�̏I��
}
/********************
*��������
********************/
void GameInit(void) {
	gamestate = GAME_MAIN;	//���C���Ɉړ�
}
void animeInit(void) {
}
/********************
*���C��
********************/
void GameMain(void) {
	notes();
}

/********************
*�m�[�c
********************/
void notes(void) {

	DrawBox(0, 550, 800, 600, 0x000000, TRUE);	//���̘g
	int maxn = 4;	//�\������m�[�c���̐�
	int widthn = 100; //�m�[�c�ƃm�[�c�̊Ԋu

	cnt++;
	for (int i = 0; i < maxn; i++) {
		if (cnt / 300 > i*widthn)
			nx[i]++;
	}
	for (int i = 0; i < maxn; i++) {
		if (nx[i]/ 300 != 400 && nx[i] != 0) {	//�^�񒆂ɗ�����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, nx[i]/300);	//�����x
			if (nf[i] == 0) {
				DrawLine(nx[i]/300, 550, nx[i]/300, 600, 0x99FFFF, 8);
				DrawLine(800 - nx[i]/300, 550, 800 - nx[i]/300 , 600, 0x99FFFF, 8);
			}
			if (g_NowKey & PAD_INPUT_1 && nx[i] / 300 >= 370 && nf[maxn] == 0) {	//Z�L�[����������
				nf[i] = 1;	//�t���O
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
*�]����A�j���[�V����
********************/
void animation(void) {
}
/********************
*�v���C���[�̏o��
********************/
void rakka(void) {
}
/********************
*�X�e�[�W�N���A����
********************/
void Stageclear(void) {
}
/********************
*�Q�[���N���A����
********************/
void gameclear(void) {
}
/********************
*�Q�[���I�[�o�[
********************/
void Gameover(void) {
}
/********************
*�X�e�[�W
********************/
void stage(void) {
}
void pinit(void) {
}
/**********************************************
*  �摜�ǂݍ���
***********************************************/
int LoadImages()
{
	return 0;
}
/***************************************
* �T�E���h�ǂݍ���
****************************************/
int LoadSounds() {
	return 0;
}