///********************************************************************
//**	��M�����Q�[��
//********************************************************************/
//#include "DxLib.h"
//#include <time.h>
//#define STAGE 5
//#define HEIGHT 20
//#define WIDTH 20
///***********************************************
// * �ϐ��̐錾
// ***********************************************/
//int g_KeyFlg;  //���̓L�[���
//int	g_OldKey;  // �O��̓��̓L�[
//int	g_NowKey;	// ����̓��̓L�[
//
//int	g_TitleImage;			// �摜�p�ϐ�
//int p_x, p_y;  //�v���C���[�̍��W
//
//int	g_GameState = 0;		// �Q�[���X�e�[�^�X
//int frame_count = 0;        //�t���[���J�E���g
//int disp_flg = 1;
//int RetryCount = 0;      //�@�@���g���C�̉񐔃J�E���g
//int clearstage = 0;
//int g_stage = 0;   //�X�e�[�W�Ǘ�
//int map[HEIGHT][WIDTH];
//int x, y;
//int	g_WaitTime = 0;			// �҂�����
//int Time = 0;
//int timecnt;
//
//int	g_StageData[STAGE][HEIGHT][WIDTH] = {
//{	//0�X�e�[�W
//	{3,3,3,3,3,3,3,3,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,0,3,0,0,0,0,0,3},
//	{3,0,3,0,3,0,3,3,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,3,3,0,3,0,3,0,3},
//	{3,0,0,0,0,0,0,0,3},
//	{3,0,3,0,3,0,3,3,3},
//	{3,0,0,0,3,0,0,0,3},
//	{3,3,3,3,3,3,3,3,3},
//},
//{	//1�X�e�[�W
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
//	{3,0,0,0,0,0,0,0,3},
//	{3,3,3,3,3,3,3,3,3},
//},
//{	//2�X�e�[�W
//	{3,3,3,3,3,3,3,3,3,3},
//	{3,0,0,0,3,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,0,3},
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
//{	//3�X�e�[�W
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//	{3,0,0,3,3,0,0,0,0,0,3,3,0,0,3},
//	{3,0,0,0,0,3,0,0,0,0,0,3,0,0,3},
//	{3,3,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,3,0,0,0,3,0,3,0,0,0,0,0,3,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,3,0,0,0,3,0,3,0,3,0,0,0,0,3},
//	{3,0,0,0,0,0,0,3,3,3,0,0,0,3,3},
//	{3,0,0,0,0,3,0,3,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,3,0,0,3,0,0,0,0,0,0,3},
//	{3,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
//	{3,0,0,0,3,0,0,3,0,0,3,0,0,0,3},
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//},
//{	//4�X�e�[�W
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
//	{3,0,0,3,0,0,3,1,3,0,0,3,0,0,3},
//	{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
//},
//};
//
///***********************************************
// * �֐��̃v���g�^�C�v�錾
// ***********************************************/
//void GameInit(void);		//�Q�[������������
//void GameMain(void);		//�Q�[�����C������
//void DrawGameTitle(void);   //�^�C�g��      
//void DrawMap();             //�}�b�v�`��
//void PlayerMove();          //�v���C���[�ړ�
//int ClearCheck();           //�N���A����
//void StageClear();			//�X�e�[�W�N���A����
//void GameClear();			//�Q�[���N���A����
//void GameOver();            //�Q�[���I�[�o�[����
//void StageReset();           //R����������X�e�[�W���Z�b�g
//void mapcopy();				//�e�X�e�[�W�̏����l��ۑ�����
//void StageClear();			//�X�e�[�W�N���A����
//void Wtime(void);			//���Ԍv��
//
///***********************************************
// * �v���O�����̊J�n
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//
//	// �^�C�g���� test �ɕύX
//	SetMainWindowText("�ʂ�Ԃ�");
//
//	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��
//	SetGraphMode(640, 590, 32);
//
//	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������
//
//	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���
//
//	SetFontSize(20);		// �����T�C�Y��ݒ�
//		//�^�C�g���摜�f�[�^�̓ǂݍ���
//	if ((g_TitleImage = LoadGraph("images/kadaiTitle.png")) == -1) return -1;
//
//	// �Q�[�����[�v
//	while (ProcessMessage() == 0 && g_GameState != 99) {
//
//		// ���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();		// ��ʂ̏�����
//
//		switch (g_GameState) {
//		case 0:
//			DrawGameTitle();	//�^�C�g���`�揈��
//			break;
//		case 1:
//			mapcopy();			//�X�e�[�W�̃R�s�[ 
//		case 2:
//			GameInit();         //������
//			break;
//		case 3:
//			GameMain();			//�Q�[�����C������
//			break;
//		case 4:
//			StageClear();			//�X�e�[�W�N���A����
//
//			break;
//		case 5:
//			GameClear();			//�Q�[���N���A����
//			break;
//		}
//
//		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
//
//	}
//
//	DxLib_End();	// DX���C�u�����g�p�̏I������
//
//	return 0;	// �\�t�g�̏I��
//}
///***********************************************
// * �Q�[����������
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
//	g_GameState = 3;	// �Q�[�����C��������
//	mapcopy();
//}
///************************************
//*�^�C�g��
//************************************/
//void DrawGameTitle(void) {
//
//	//�^�C�g���摜�\��
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//	if (g_KeyFlg & PAD_INPUT_M) {
//		g_GameState = 1;	// �Q�[�����C��������
//
//	}
//	
//	SetFontSize(40);
//		DrawString(40, 300, "\"�r�o�`�b�d�L�[\"��\n              �����Ă�������", 0xffffff);
//
//		
//}
//
///***********************************************
// * �Q�[�����C��
// ***********************************************/
//void GameMain(void)
//{
//	
//	Wtime();
//	StageReset();
//	PlayerMove();
//	DrawMap();
////SetFontSize(30);
////DrawFormatString(590, 20, 0xffffff, "%d", Time);
//
//	if (ClearCheck() == 1) {
//		g_GameState = 4;       //�X�e�[�W�N���A
//
//	}
//	if (g_stage == 4) {
//		if (ClearCheck() == 1) {
//			g_GameState = 5;    //�Q�[���N���A
//		}
//	}
//	DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
//
//}
///***********************************
//*�}�b�v�\��
//***********************************/
//void DrawMap() {
//	for (int y = 0; y < HEIGHT; y++) {   //
//		for (int x = 0; x < WIDTH; x++) {
//			if (map[y][x] == 1) {
//				DrawBox(39 * x, 39 * y, 39 * x + 39, 39 * y + 39, 0x2222ff, TRUE);
//			}
//			else if (map[y][x] == 2) {
//				DrawBox(39 * x, 39 * y, 39 * x + 39, 39 * y + 39, 0xaa2255, TRUE);
//			}
//			else if (map[y][x] == 3) {
//				DrawBox(39 * x, 39 * y, 39 * x + 39, 39 * y + 39, 0x22aa33, TRUE);
//			}
//		}
//	}
//}
///*******************************
//*�v���C���[�̈ړ�����
//********************************/
//void PlayerMove() {
//	//�㉺���E�ړ�
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		while (map[p_y - 1][p_x] != 3) {
//			ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_y -= 1;
//			DrawMap();
//			DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
//			Wtime();
//			ScreenFlip();
//			WaitTimer(25);
//		}
//	}
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		while (map[p_y + 1][p_x] != 3) {
//		ClearDrawScreen();
//			map[p_y][p_x] = 1;
//			p_y += 1;
//			DrawMap();
//			DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
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
//			DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
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
//			DrawBox(39 * p_x, 39 * p_y, 39 * p_x + 39, 39 * p_y + 39, 0xffffff, TRUE); //�v���C���[��box
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
//*�N���A����
//***********************************/
//int ClearCheck() {
//	int cnt = 0;
//
//		for ( y = 0; y < HEIGHT; y++) {   //
//			for ( x = 0; x < WIDTH; x++) {
//				if (map[y][x] != 0) {
//					cnt++;
//				}
//
//			}
//		}if (cnt == 90 && g_stage == 0) {
//			return 1;   //�P�őS�Ė��܂����Ƃ�
//		}
//		else if (cnt == 126 && g_stage == 1) {
//			return 1;
//		}
//		else if (cnt == 130 && g_stage == 2) {
//			return 1;
//		}
//		else if (cnt == 225 && g_stage == 3) {
//			return 1;
//		}
//		else if (cnt == 225 && g_stage == 4) {
//			return 1;
//		}
//	return 0;
//}
///*********************************
//*�Q�[���N���A����
//*********************************/
//void GameClear() {
//	frame_count++;
//	if (frame_count % 30 == 0) {
//		disp_flg = !disp_flg;
//	}
//	if (disp_flg == 1) {
//		timecnt += 0;
//		SetFontSize(20);
//		DrawString(150, 400, "\"Z\"����������^�C�g����", 0xffffff);
//		SetFontSize(30);
//		DrawFormatString(590, 20, 0xffffff, "%d", timecnt);
//	}
//	SetFontSize(64);                             //�T�C�Y��64�ɕύX
//	SetFontThickness(8);                         //������8�ɕύX
//	DrawString(170, 200, "Game Clear!", 0xffffff);
//	SetFontSize(30);
//	DrawFormatString(120, 300, 0xffffff, "���Ȃ��̃N���A�^�C����%d�b�ł��B", timecnt);
//	if (g_KeyFlg & PAD_INPUT_1) {
//		g_GameState = 0;
//		g_stage = 0;
//		Time = 0;
//		timecnt = 0;
//	}
//}
///***************************************
//*R�L�[����������X�e�[�W�̏�ԃ��Z�b�g
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
//*�}�b�v�R�s�[
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
//*�X�e�[�W�N���A����
//**************************************/
//void StageClear() {
//	frame_count++;
//	if (frame_count % 30 == 0) {
//		disp_flg = !disp_flg;
//	}
//	if (disp_flg == 1) {
//		SetFontSize(20);
//		DrawString(150, 300, "\"�r�o�`�b�d�L�[\"���������玟�̃X�e�[�W��", 0xffffff);
//	}
//	SetFontSize(64);                             //�T�C�Y��64�ɕύX
//	SetFontThickness(8);                         //������8�ɕύX
//	DrawString(170, 200, "StageClear!", 0xffffff);
//
//
//	if (g_KeyFlg & PAD_INPUT_M) {
//		g_GameState = 2;
//		if (++g_stage > 4);
//
//	}
//}
///*********************************************************************
//*���Ԍv��
//*********************************************************************/
//void Wtime(void) {
//	g_WaitTime++;		//���Ԃ̎擾
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
//
//
