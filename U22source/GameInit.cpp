#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"
#include "EnemyAttck.h"
#include "sounds.h"

//��`
int	g_GameState = 0;		// �Q�[���X�e�[�^�X

//Airman airman;

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit()
{
	if (g_stage == 0) {
		g_GameState = 2;

		PlayerInit();
		ScroolInit();

		//�m�[�c�̏�����
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}

		EnemyInit();

		for (int i = 0; i < MAXEnemy; i++) {
			airman[i].Airmaninit();//�G�A�[�}���̏�����
			Air[i].AirInit();//�G�A�[�}���̍U���̏�����
		}
	}
	else {
		StopSoundMem(rockBGM);
		PlayerInit();
		ScroolInit();
		EnemyInit();
		for (int i = 0; i < MAXEnemy; i++) {
			airman[i].Airmaninit();//�G�A�[�}���̏�����
		}

		//�m�[�c�̏�����
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}
		g_GameState = 4;
	}
}