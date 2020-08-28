#include "DxLib.h"
#include "GameInit.h"
#include "player.h"
#include "notes.h"
#include "map.h"
#include "EnemyMove.h"
#include "BackgroundMove.h"
#include "EnemyAttck.h"
#include "sounds.h"
#include "PlayerAttack.h"

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
		PlayerAttackInit();
		StopSoundMem(rockBGM);

		//�m�[�c�̏�����
		for (int i = 0; i < 100; i++) {
			notesinit(i);
		}

		EnemyInit();
		intt = 0;
		innt = 0;
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
		PlayerAttackInit();
		intt = 0;
		innt = 0;
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